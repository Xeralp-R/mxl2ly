//
//  part.cpp
//  mxl2ly
//
//  Created by Reventar on 17/11/2021.
//

#include "part.hpp"

#include <algorithm>
#include <numeric>
#include <utility>

#include "fmt/format.h"

using namespace lmt;
namespace tx2 = tinyxml2;

PartList::PartList(
    std::initializer_list<std::pair<std::string, std::string>> parts) {
    for (auto& pair : parts) {
        this->parts.insert(pair);
    }
}

void PartList::add_part(std::string part_id, std::string part_name) {
    this->parts.insert({part_id, part_name});
}

Part::Part(std::string id) : id(id) {}

Part::Part(tinyxml2::XMLElement* part_elem, const MusicTree* tree_ptr) {
    id = tx2::attribute_value(part_elem, "id");

    using namespace std::string_literals;

    // prepare all the staves we need
    int num_of_staves =
        tx2::exists(part_elem, "measure/attributes/staves")
            ? tx2::int_text(part_elem, "measure/attributes/staves")
            : 1;
    for (int i = 0; i < num_of_staves; ++i) {
        this->staves.push_back(std::make_unique<Staff>(i));
    }

    for (auto* meas_elem : tx2::selection(part_elem, "measure")) {
        int id_number        = meas_elem->IntAttribute("number");
        int current_staff_no = tx2::int_text(meas_elem, "note/staff");
        std::vector<tx2::XMLElement*> holder;

        auto holder_document = std::make_unique<tx2::XMLDocument>();
        holder_document->Parse("<root></root>");
        auto full_distributor = tx2::append_element(
            holder_document->FirstChildElement(), "attributes");
        std::unordered_map<int, tx2::XMLElement*> directed_distributor;

        for (auto* meas_object : meas_elem) {
            // If the object is an attribute, then distribute it to the staves.
            if (meas_object->Name() == "attributes"s) {
                // Distribute it to the distributors
                for (auto attr_elem : meas_object) {
                    // If it is to be distributed to all staves
                    if (tx2::attribute_value(attr_elem, "number") == ""s) {
                        // make a deep copy into the new document
                        auto attr_ptr =
                            attr_elem->DeepClone(holder_document.get());
                        // place it into the right location
                        full_distributor->InsertEndChild(attr_ptr);
                        continue;
                    }

                    // if it has to go to one staff in particular
                    auto staff_num =
                        std::stoi(tx2::attribute_value(attr_elem, "number"));

                    // if the current director doesn't exist
                    if (directed_distributor.find(staff_num) ==
                        directed_distributor.end()) {
                        directed_distributor.insert(
                            {staff_num,
                             tx2::append_element(holder_document->RootElement(),
                                                 "attributes")});
                    }
                    // append the element
                    auto attr_ptr = attr_elem->DeepClone(holder_document.get());
                    directed_distributor.at(staff_num)->InsertEndChild(
                        attr_ptr);
                }

                // fill out the distributors
                holder.push_back(full_distributor);
                if (directed_distributor.find(current_staff_no) !=
                    directed_distributor.end()) {
                    holder.push_back(directed_distributor.at(current_staff_no));
                }
                continue;
            }

            // If the object is still not a note, allow it to go into the
            // current holder.
            if (meas_object->Name() != "note"s) {
                holder.push_back(meas_object);
                continue;
            }

            // The measure object is a note. If it is in the current staff,
            // allow it to go into the current holder.
            if (tx2::int_text(meas_object, "staff") == current_staff_no) {
                holder.push_back(meas_object);
                continue;
            }

            // The measure object is a note in a different staff.
            // Push the holder into the staff, then regenerate the thing.

            // note: pop-back the last element of the vector, an unnecessary
            // backup
            holder.pop_back();
            auto new_measure =
                std::make_unique<Measure>(holder, id_number, tree_ptr);
            this->staves.at(current_staff_no - 1)
                ->measures.push_back(std::move(new_measure));
            holder.clear();

            current_staff_no = tx2::int_text(meas_object, "staff");
            holder.push_back(full_distributor);
            if (directed_distributor.find(current_staff_no) !=
                directed_distributor.end()) {
                holder.push_back(directed_distributor.at(current_staff_no));
            }
            holder.push_back(meas_object);
        }
        // last set of holders
        auto new_measure =
            std::make_unique<Measure>(holder, id_number, tree_ptr);
        this->staves.at(current_staff_no - 1)
            ->measures.push_back(std::move(new_measure));
    }
}

std::pair<std::string, std::string> Part::return_lilypond() const {
    using namespace std::string_literals;
    std::string directory;
    if (staves.size() == 1) {
        directory +=
            fmt::format(R"__(\new Staff \part-{0}-{1})__",
                        helper::convert_number_names(id),
                        helper::convert_number_names(staves.at(0)->id + 1)) +
            "\n";
    } else {
        directory += R"__(\new GrandStaff <<)__"s + "\n";
        for (auto& staff : staves) {
            directory +=
                fmt::format(R"__(\new Staff \part-{0}-{1})__",
                            helper::convert_number_names(id),
                            helper::convert_number_names(staff->id + 1)) +
                "\n";
        }
        directory += ">>\n";
    }

    std::string part_string;
    for (auto& staff : staves) {
        part_string += fmt::format(
            "part-{0}-{1} = {2}\n", helper::convert_number_names(id),
            helper::convert_number_names(staff->id + 1), "{");

        for (auto iter = staff->measures.begin(); iter != staff->measures.end();
             ++iter) {
            // part_string += measure->return_lilypond();
            auto meas_vec = (*iter)->return_lilypond();

            // if it only has 1 voice, let it be part of the thing without edit
            if (meas_vec.size() == 1) {
                part_string += meas_vec.at(0) + " |\n";
                if (((*iter)->id() % 5) == 0) {
                    part_string += fmt::format("% {0}{1}", (*iter)->id(), '\n');
                }
                continue;
            }

            // else, if it is alone in having 1 voice, make it unique
            auto temp_iter = iter;
            ++temp_iter;
            if (temp_iter != staff->measures.end() &&
                (*temp_iter)->return_lilypond().size() != meas_vec.size()) {
                part_string += "<< "s;
                for (const auto& line_str : meas_vec) {
                    part_string += " { "s + line_str + R"( } \\)"s;
                }
                part_string.pop_back();
                part_string.pop_back();
                part_string += " >> |\n"s;
                if (((*iter)->id() % 5) == 0) {
                    part_string += fmt::format("% {0}{1}", (*iter)->id(), '\n');
                }
                continue;
            }

            // Otherwise, determine how long the polyphony lasts
            // and make it multi-voice until that point

            // get the ending point
            auto end_iter = iter;
            do {
                ++end_iter;
            } while (end_iter != staff->measures.end() &&
                     (*end_iter)->return_lilypond().size() == meas_vec.size());

            // get the full length of voices
            std::vector<std::string> polyphony =
                std::vector<std::string>(meas_vec.size(), "");
            for (auto temp_iter = iter; temp_iter != end_iter; ++temp_iter) {
                auto temp_vec    = (*temp_iter)->return_lilypond();
                bool has_comment = (((*temp_iter)->id() % 5) == 0);

                for (int i = 0; i < polyphony.size(); ++i) {
                    polyphony.at(i) += temp_vec.at(i) + " |\n";
                    polyphony.at(i) +=
                        has_comment ? fmt::format("% {0}\n", (*temp_iter)->id())
                                    : "";
                }
            }

            auto capitalize_first = [](std::string s) {
                s[0] = toupper(s[0]);
                return s;
            };

            // print
            part_string += "<<\n";
            for (int i = 0; i < polyphony.size(); ++i) {
                part_string += fmt::format(
                    R"__(\context Voice = "voice{0}" {1} \voice{2} {3})__",
                    helper::convert_number_names(i + 1), "{",
                    capitalize_first(helper::convert_number_names(i + 1)),
                    "\n");
                part_string += polyphony.at(i);
                part_string += "}\n";
            }
            part_string += ">>\n";
            iter = --end_iter;
        }

        part_string += fmt::format("{0}\n\n", "}");
    }

    return {directory, part_string};
}

void Part::add_measure(std::unique_ptr<Measure> measure_ptr) {
    // Add later
    // this->measures_flat.push_back(std::move(measure_ptr));
}
