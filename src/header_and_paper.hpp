//
//  header_and_paper.hpp
//  mxl2ly
//
//  Created by Reventar on 11/11/2021.
//

#ifndef header_and_paper_hpp
#define header_and_paper_hpp

#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include <initializer_list>
#include <string>
#include <array>

#include "statement.hpp"

namespace lmt {

class Header : public AbstractStatement {
public:
    Header() = default;
    Header(std::initializer_list<std::pair<std::string, std::string>> statements);
    
    void add_statement(std::pair<std::string, std::string>);
    
    std::string get_type() override { return "header"; }
    std::vector<Statement<std::string>*> get_statements();
private:
    std::vector<std::unique_ptr<Statement<std::string>>> statements;
};

class Paper : public AbstractStatement {
public:
    enum class Margins {
        EvenLeftMargin,
        EvenRightMargin,
        EvenTopMargin,
        EvenBottomMargin,
        OddLeftMargin,
        OddRightMargin,
        OddTopMargin,
        OddBottomMargin
    };
    
    Paper(Length height, Length width);
    
    void set_even_margins(Length left_margin,
                          Length right_margin,
                          Length top_margin,
                          Length bottom_margin);
    
    void set_odd_margins(Length left_margin,
                         Length right_margin,
                         Length top_margin,
                         Length bottom_margin);
    
    std::string get_type() override { return "paper"; }
    
    Statement<Length>* get_margin(Paper::Margins margin);
private:
    std::unique_ptr<Statement<Length>> height;
    std::unique_ptr<Statement<Length>> width;
    
    using margin_array = std::array<std::unique_ptr<Statement<Length>>, 4>;
    
    margin_array even_margins;
    margin_array odd_margins;
};
    
}

#endif /* header_and_paper_hpp */
