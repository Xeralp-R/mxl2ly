//
//  extract_measure_attributes.cpp
//  mxl2ly
//
//  Created by Reventar on 08/01/2022.
//

#include "music_tree.hpp"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "measure_attributes.hpp"
#include "tinyxml2/tixml2ex.h"

using namespace lmt;
namespace tx2 = tinyxml2;

static const lmt::aux::MeasureAttributeFactory measure_attribute_factory;

std::vector<std::unique_ptr<aux::AbstractMeasureAttribute>>
MusicTree::ExtractMusicFunctor::extract_measure_attributes(
    tx2::XMLElement* meas_ptr) {
    std::vector<std::unique_ptr<aux::AbstractMeasureAttribute>> returner;

    if (!tx2::exists(meas_ptr, "attributes")) {
        return {};
    }
    for (const auto spec_ptr : tx2::find_element(meas_ptr, "attributes")) {
        auto temp = move(measure_attribute_factory(spec_ptr));
        if (temp == nullptr) {
            continue;
        }
        returner.push_back(move(temp));
    }
    return returner;
}
