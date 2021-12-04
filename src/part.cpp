//
//  part.cpp
//  mxl2ly
//
//  Created by Reventar on 17/11/2021.
//

#include "part.hpp"

using namespace lmt;

Part::Part(std::string id) : id(id) {}

void Part::add_measure(std::unique_ptr<Measure> measure_ptr) { 
    this->measures.push_back(std::move(measure_ptr));
}

