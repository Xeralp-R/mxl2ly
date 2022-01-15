//
//  measure.cpp
//  mxl2ly
//
//  Created by Reventar on 04/12/2021.
//

#include "measure.hpp"

#include <algorithm>
#include <exception>

using namespace lmt;

Measure::Measure(int id_number) : id_number(id_number) {}

void Measure::add_measure_object(
    std::unique_ptr<lmt::aux::AbstractMeasureObject> abstract_ptr) {
    if (abstract_ptr->get_subtype() == "backup") {
        this->number_of_voices += 1;
    };

    this->objects.push_back(std::move(abstract_ptr));
}
