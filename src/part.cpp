//
//  part.cpp
//  mxl2ly
//
//  Created by Reventar on 17/11/2021.
//

#include "part.hpp"

#include <algorithm>
#include <numeric>

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

    /*
    bool has_many_staves =
        tx2::exists(part_elem, "measure/attribute/staves")
            ? tx2::int_text(part_elem, "measure/attribute/staves") > 1
            : false;
     */
    /*
    bool has_many_voices =
        tx2::exists(part_elem, "measure/note/voice")
            ? tx2::int_text(part_elem->FirstChildElement("measure")
                                ->LastChildElement("note")
                                ->FirstChildElement("voice")) > 1
            : false;

     std::vector<int> permitted_voice_nums;
            for (auto voice_elem :
    tx2::selection(tx2::first_child_element(part_elem), "note/voice")) { auto i
    = tx2::int_text(voice_elem); if (is_element(permitted_voice_nums.begin(),
                               permitted_voice_nums.end(),
                               i)) {
                    permitted_voice_nums.push_back(i);
                }
            }
     */
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

        for (auto* meas_object : meas_elem) {
            // If the object is not a note, allow it to go into the current
            // holder.
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

            holder.push_back(meas_object);
            current_staff_no = tx2::int_text(meas_object, "staff");
        }
        // last set of holders
        auto new_measure =
            std::make_unique<Measure>(holder, id_number, tree_ptr);
        this->staves.at(current_staff_no - 1)
            ->measures.push_back(std::move(new_measure));
    }

    /*
if (!has_many_staves) {
    // deal with the entire, "flat" part.
    for (auto* measure_reader : tx2::selection(part_elem, "measure")) {
        measures_flat.push_back(
            std::make_unique<Measure>(measure_reader, tree_ptr));
    }
} else {
    // profile the first measure.
    std::vector<int> permitted_staff_nums(
        tx2::int_text(part_elem, "measure/attribute/staves"), -1);
    std::iota(permitted_staff_nums.begin(), permitted_staff_nums.end(), 1);

    for (auto* meas_elem : tx2::selection(part_elem, "measure")) {
        int id_number = meas_elem->IntAttribute("number");

        int current_staff_num = tx2::int_text(meas_elem, "note/staff");
        std::vector<tx2::XMLElement*> holder;
        tx2::XMLElement*              last_backup_element;
        unsigned long int             current_count;

        for (auto* note_elem : meas_elem) {
            if (note_elem->Name() == std::string("backup")) {
                last_backup_element = note_elem;
            }

            if (note_elem->Name() != std::string("note")) {
                holder.push_back(note_elem);

            } else if (tx2::int_text(note_elem, "staff") ==
                       current_staff_num) {
                current_count += tx2::int_text(note_elem, "duration");
                holder.push_back(note_elem);

            } else {
                // guaranteed: tx2::int_text(note_elem, "staff") !=
current_staff_num int turn_back_amount = tx2::int_text(last_backup_element,
"duration"); int staff_forward = current_count - turn_back_amount; if
(staff_forward != 0) {std::cerr << "Error: half-filled bar in staff;
continuing...\n";}
                // find a way to input this later...

                measures_dimen.at(current_staff_num)
                    .push_back(std::make_unique<Measure>(holder, id_number,
                                                         tree_ptr));
                holder.clear();
                holder.push_back(note_elem);
            }
        }
    }
}
     */
}

std::pair<std::string, std::string> Part::return_lilypond() const {
    using namespace std::string_literals;
    std::string directory;
    if (staves.size() == 1) {
        directory += fmt::format(R"__(\new Staff \part-{0}-{1})__",
                                 convert_number_names(id),
                                 convert_number_names(staves.at(0)->id + 1)) +
                     "\n";
    } else {
        directory += R"__(\new GrandStaff <<)__"s + "\n";
        for (auto& staff : staves) {
            directory += fmt::format(R"__(\new Staff \part-{0}-{1})__",
                                     convert_number_names(id),
                                     convert_number_names(staff->id + 1)) +
                         "\n";
        }
        directory += ">>\n";
    }

    std::string part_string;
    for (auto& staff : staves) {
        part_string +=
            fmt::format("part-{0}-{1} = {2}\n", convert_number_names(id),
                        convert_number_names(staff->id + 1), "{");

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
                    part_string += "{ "s + line_str + R"( } \\)"s;
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
                bool has_comment = (((*iter)->id() % 5) == 0);

                for (int i = 0; i < polyphony.size(); ++i) {
                    polyphony.at(i) += temp_vec.at(i) + " |\n";
                    polyphony.at(i) +=
                        has_comment ? fmt::format("% {0}\n", (*iter)->id())
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
                    convert_number_names(i + 1), "{",
                    capitalize_first(convert_number_names(i + 1)), "\n");
                part_string += polyphony.at(i);
                part_string += "\n}\n";
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
