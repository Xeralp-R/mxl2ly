//
//  measure_objects.hpp
//  mxl2ly
//
//  Created by Reventar on 04/12/2021.
//

#ifndef measure_objects_hpp
#define measure_objects_hpp

#include <string>

#include "statement.hpp"

namespace lmt::aux {
    struct AbstractMeasureObject : public AbstractStatement {
        std::string get_type() { return "measure_object"; }
        virtual std::string get_subtype() = 0;
        virtual ~AbstractMeasureObject(){};
    };
    
    struct Backup : public AbstractMeasureObject {
        short int duration_back;
        
        std::string get_subtype() { return "backup"; };
    };
}

#endif /* measure_objects_hpp */
