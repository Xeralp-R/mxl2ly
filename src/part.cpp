//
//  part.cpp
//  mxl2ly
//
//  Created by Reventar on 17/11/2021.
//

#include "part.hpp"

using namespace lmt;

Part::Part(std::string id) : id(id) {}

PartList::PartList(std::initializer_list<std::pair<std::string, std::string> > parts) {
    for (auto& pair : parts) {
        this->parts.insert(pair);
    }
}

void PartList::add_part(std::string part_id, std::string part_name) { 
    this->parts.insert(part_id, part_name);
}

void Part::add_measure(std::unique_ptr<Measure> measure_ptr) { 
    this->measures.push_back(std::move(measure_ptr));
}
