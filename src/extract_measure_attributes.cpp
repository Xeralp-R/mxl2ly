//
//  extract_measure_attributes.cpp
//  mxl2ly
//
//  Created by Reventar on 08/01/2022.
//

#include "music_tree.hpp"

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

#include "tinyxml2/tixml2ex.h"
#include "measure_attributes.hpp"

using namespace lmt;
using namespace lmt::aux;
namespace tx2 = tinyxml2;

using std::unordered_map, std::string, std::function, std::vector;
using std::unique_ptr, aux::AbstractMeasureAttribute, tinyxml2::XMLElement;
using std::make_unique, std::move, tx2::find_element;

// Note to the reader: this only returns unique ptrs, not vectors of uniq ptrs
// notations need to return vectors because you can specify many notations,
// but not attributes.
static const unordered_map<string,
function<unique_ptr<AbstractMeasureAttribute>(tx2::XMLElement*)>>
attribute_factory {
    {"clef", [](tx2::XMLElement* attr_ptr)
        -> unique_ptr<AbstractMeasureAttribute> {
            int line_num = tx2::int_text(find_element(attr_ptr, "line"));
            char type = std::tolower(tx2::text(find_element(attr_ptr, "sign")).at(0));
            return make_unique<Clef>(type, line_num);
        }
    },
    {"key", [](tx2::XMLElement* attr_ptr)
        -> unique_ptr<AbstractMeasureAttribute> {
            int fifths = tx2::int_text(find_element(attr_ptr, "fifths"));
            return make_unique<KeySignature>(fifths);
        }
    },
    {"time", [](tx2::XMLElement* attr_ptr)
        -> unique_ptr<AbstractMeasureAttribute> {
            int upper = tx2::int_text(find_element(attr_ptr, "beats"));
            int lower = tx2::int_text(find_element(attr_ptr, "beat-type"));
            return make_unique<TimeSignature>(upper, lower);
        }
    }
};

vector<unique_ptr<AbstractMeasureAttribute>>
MusicTree::ExtractMusicFunctor::extract_measure_attributes
(tx2::XMLElement* meas_ptr) {
    vector<unique_ptr<AbstractMeasureAttribute>> returner;
    
    if (!tx2::exists(meas_ptr, "attributes")) { return {}; }
    for (auto spec_ptr : tx2::find_element(meas_ptr, "attributes")) {
        // ignore exceptions
        unique_ptr<AbstractMeasureAttribute> temp;
        try {
            temp = move(attribute_factory.at(spec_ptr->Name())(spec_ptr));
            returner.push_back(move(temp));
        } catch (...) {}
    }
    return returner;
}
