//
//  measure.hpp
//  mxl2ly
//
//  Created by Reventar on 04/12/2021.
//

#ifndef measure_hpp
#define measure_hpp

#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <variant>
#include <utility>

#include "measure_objects.hpp"
#include "note.hpp"
#include "measure_attributes.hpp"
#include "measure_directions.hpp"

// ==> Proper declarations
namespace lmt {
    class Measure {
    public:
        Measure(int id_number);
        
        void add_measure_object(std::unique_ptr<lmt::aux::AbstractMeasureObject> abstract_ptr);
    private:
        // ==> Variables
        int id_number;
        std::vector<std::unique_ptr<lmt::aux::AbstractMeasureObject>> objects;
        int number_of_voices;
    };
}


#endif /* measure_hpp */
