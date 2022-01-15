//
//  header_and_paper.cpp
//  mxl2ly
//
//  Created by Reventar on 13/11/2021.
//

#include "header_and_paper.hpp"

#include <exception>

using namespace lmt;

Header::Header(
    std::initializer_list<std::pair<std::string, std::string>> statements) {
    for (auto& pair : statements) {
        this->statements.push_back(
            std::make_unique<Statement<std::string>>(pair.first, pair.second));
    }
}

void Header::add_statement(std::pair<std::string, std::string> pair) {
    this->statements.push_back(
        std::make_unique<Statement<std::string>>(pair.first, pair.second));
}

std::unordered_map<std::string, std::string> Header::get_statements() const {
    std::unordered_map<std::string, std::string> returner;
    for (auto& pointer : this->statements) {
        returner.emplace(pointer->get_type(), pointer->get_content());
    }
    return returner;
}

Paper::Paper(Length height, Length width) {
    this->height = std::make_unique<Statement<Length>>("height", height);
    this->width  = std::make_unique<Statement<Length>>("width", width);
}

void Paper::set_margins(Length left_margin, Length right_margin,
                        Length top_margin, Length bottom_margin) {
    this->margins[0] =
        std::make_unique<Statement<Length>>("l_margin", left_margin);
    this->margins[1] =
        std::make_unique<Statement<Length>>("r_margin", right_margin);
    this->margins[2] =
        std::make_unique<Statement<Length>>("t_margin", top_margin);
    this->margins[3] =
        std::make_unique<Statement<Length>>("b_margin", bottom_margin);
}
Length Paper::get_margin(Paper::Margins margin) const {
    switch (margin) {
    case Margins::LeftMargin:
        return this->margins[0]->get_content();
        break;
    case Margins::RightMargin:
        return this->margins[1]->get_content();
        break;
    case Margins::TopMargin:
        return this->margins[2]->get_content();
        break;
    case Margins::BottomMargin:
        return this->margins[3]->get_content();
        break;
    }
    throw std::logic_error("Impossible margin request");
}
