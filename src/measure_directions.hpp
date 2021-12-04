//
//  measure_directions.hpp
//  mxl2ly
//
//  Created by Reventar on 04/12/2021.
//

#ifndef measure_directions_hpp
#define measure_directions_hpp

#include <string>
#include <vector>
#include <map>
#include <exception>

#include "statement.hpp"

namespace lmt::aux {
    struct AbstractMeasureDirection : public AbstractStatement {
        std::string get_type() { return "measure_direction"; }
        virtual std::string get_subtype() = 0;
        virtual ~AbstractMeasureDirection(){};
    };
    
    struct Wedge : AbstractMeasureDirection {
        enum {
            Crescendo,
            Decrescendo,
            Stop
        } type;
        
        std::string get_subtype() { return "wedge"; }
    };
}

#endif /* measure_directions_hpp */
