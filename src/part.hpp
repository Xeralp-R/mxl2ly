//
//  part_.hpp
//  mxl2ly
//
//  Created by Reventar on 17/11/2021.
//

#ifndef part_hpp
#define part_hpp

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>

#include "statement.hpp"
#include "measure.hpp"

namespace lmt {
    class PartList : public AbstractStatement {
    public:
        PartList(std::initializer_list<std::pair<std::string, std::string>> parts);
        
        void add_part(std::string part_id, std::string part_name);
    private:
        std::map<std::string, std::string> parts;
    };
    
    class Part : public AbstractStatement {
    public:
        Part(std::string id);
        
        void add_measure(std::unique_ptr<Measure> measure_ptr);
        
        std::string get_type() override { return "part"; }
    private:
        std::string id;
        std::vector<std::unique_ptr<Measure>> measures;
    };
} // namespace lmt

#endif /* part_hpp */
