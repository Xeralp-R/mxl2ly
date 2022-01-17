//
//  part.cpp
//  mxl2ly
//
//  Created by Reventar on 17/11/2021.
//

#include "part.hpp"

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

    for (auto* measure_reader : tx2::selection(part_elem, "measure")) {
        measures.push_back(std::make_unique<Measure>(measure_reader, tree_ptr));
    }
}

std::string Part::return_lilypond() const {
    std::string part_string;

    part_string +=
        fmt::format("part-{0} = {1}\n", convert_number_names(id), "{");
    for (auto& measure : measures) {
        part_string += measure->return_lilypond();
    }
    part_string += fmt::format("{0}\n", "}");

    return part_string;
}

void Part::add_measure(std::unique_ptr<Measure> measure_ptr) {
    this->measures.push_back(std::move(measure_ptr));
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
