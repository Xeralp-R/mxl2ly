//
//  measure.hpp
//  mxl2ly
//
//  Created by Reventar on 04/12/2021.
//

#ifndef measure_hpp
#define measure_hpp

#include <iostream>
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "measure_attributes.hpp"
#include "measure_directions.hpp"
#include "measure_objects.hpp"
#include "note.hpp"
#include "tinyxml2/tixml2ex.h"

// ==> Proper declarations
namespace lmt {
class MusicTree;

class Measure {
  public:
    Measure(int id_number);
    Measure(tinyxml2::XMLElement* meas_elem, const MusicTree* tree_ptr);
    Measure(std::vector<tinyxml2::XMLElement*> elem_vec, int id_number,
            const MusicTree* tree_ptr);

    std::string return_lilypond() const;

    void add_measure_object(
        std::unique_ptr<lmt::aux::AbstractMeasureObject> abstract_ptr);
    int size() const { return this->objects.size(); }
    lmt::aux::AbstractMeasureObject* at(int i) const {
        return this->objects.at(i).get();
    }

  private:
    // ==> Variables
    int                                                           id_number;
    std::vector<std::unique_ptr<lmt::aux::AbstractMeasureObject>> objects;
    int number_of_voices = 0;

    // ==> Helper Functions
    aux::MeasureAttributeFactory measure_attribute_factory;
};
} // namespace lmt

#endif /* measure_hpp */
