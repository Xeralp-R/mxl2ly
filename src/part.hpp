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
#include <iterator>

#include "statement.hpp"
#include "measure.hpp"

namespace lmt {
    class PartList : public AbstractStatement {
    public:
        PartList() = default;
        PartList(std::initializer_list<std::pair<std::string, std::string>> parts);
        
        void add_part(std::string part_id, std::string part_name);
        
        std::string get_type() override { return "part_list"; }
        std::map<std::string, std::string> get_parts() const { return this->parts; }
    private:
        std::map<std::string, std::string> parts;
    };
    
    class Part : public AbstractStatement {
    public:
        Part(std::string id);
        
        void add_measure(std::unique_ptr<Measure> measure_ptr);
        
        std::string get_type() override { return "part"; }
        std::string get_id() const { return this->id; }
        int size() const { return this->measures.size(); }
        Measure* at(int index) const { return this->measures.at(index).get(); }
    private:
        std::string id;
        std::vector<std::unique_ptr<Measure>> measures;
    };
} // namespace lmt

#endif /* part_hpp */
