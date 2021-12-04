//
//  part_and_measure.hpp
//  mxl2ly
//
//  Created by Reventar on 17/11/2021.
//

#ifndef part_and_measure_hpp
#define part_and_measure_hpp

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "statement.hpp"
#include "measure_attributes.hpp"
#include "measure_directions.hpp"

namespace lmt {
    class Measure : public AbstractStatement {
    public:
        Measure();
    private:
    };
    
    class Part : public AbstractStatement {
    public:
        Part(std::string long_name, std::string short_name)
        : long_name(long_name), short_name(short_name) {};
        
        void add_statement(std::unique_ptr<AbstractStatement> new_statement);
        
        std::string get_type() override { return "part"; }
        std::vector<AbstractStatement *> get_statements();
        
    private:
        std::string long_name;
        std::string short_name;
        std::vector<std::unique_ptr<AbstractStatement>> statements;
    };
} // namespace lmt

#endif /* part_and_measure_hpp */
