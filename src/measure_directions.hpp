//
//  measure_directions.hpp
//  mxl2ly
//
//  Created by Reventar on 04/12/2021.
//

#ifndef measure_directions_hpp
#define measure_directions_hpp

#include <exception>
#include <map>
#include <string>
#include <vector>

#include "measure_objects.hpp"

namespace lmt::aux {
struct AbstractMeasureDirection : public AbstractMeasureObject {
    std::string         get_subtype() { return "direction"; }
    virtual std::string get_subsubtype() = 0;
    virtual ~AbstractMeasureDirection(){};
};

struct Wedge : AbstractMeasureDirection {
    enum { Crescendo, Decrescendo, Stop } type;

    std::string get_subsubtype() { return "wedge"; }
};
} // namespace lmt::aux

#endif /* measure_directions_hpp */
