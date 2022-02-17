//
//  part.cpp
//  mxl2ly
//
//  Created by Reventar on 17/11/2021.
//

#include "part.hpp"

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

    bool has_many_staves =
        tx2::exists(part_elem, "measure/attribute/staves")
            ? tx2::int_text(part_elem, "measure/attribute/staves") > 1
            : false;
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

    if (!has_many_staves) {
        // deal with the entire, "flat" part.
        for (auto* measure_reader : tx2::selection(part_elem, "measure")) {
            measures_flat.push_back(
                std::make_unique<Measure>(measure_reader, tree_ptr));
        }
    } else {
        // profile the first measure.
        std::vector<int> permitted_staff_nums(
            tx2::int_text(part_elem, "measure/attribute/staves"));
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
                    int turn_back_amount =
                        tx2::int_text(last_backup_element, "duration");
                    int staff_forward = current_count - turn_back_amount;
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
}

std::string Part::return_lilypond() const {
    std::string part_string;

    part_string +=
        fmt::format("part-{0} = {1}\n", convert_number_names(id), "{");
    for (auto& measure : measures_flat) {
        part_string += measure->return_lilypond();
    }
    part_string += fmt::format("{0}\n", "}");

    return part_string;
}

void Part::add_measure(std::unique_ptr<Measure> measure_ptr) {
    this->measures_flat.push_back(std::move(measure_ptr));
}

std::string Part::convert_number_names(const std::string test) const {
    std::string returner;
    for (auto ch : test) {
        // if ch is any number from 0 to 9
        if (ch - '0' >= 0 && ch - '9' <= 0) {
            returner += number_names.at(ch - '0');
        } else {
            returner += ch;
        }
    }
    return returner;
}
