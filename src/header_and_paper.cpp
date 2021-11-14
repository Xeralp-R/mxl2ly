//
//  header_and_paper.cpp
//  mxl2ly
//
//  Created by Reventar on 13/11/2021.
//

#include "header_and_paper.hpp"

#include <exception>

Header::Header(std::initializer_list<std::pair<std::string, std::string>> statements) { 
    for (auto& pair : statements) {
        this->statements.push_back(std::make_unique<Statement<std::string>>(pair.first, pair.second));
    }
}

std::vector<Statement<std::string>*> Header::get_statements() {
    std::vector<Statement<std::string>*> returner;
    for (auto& pointer : this->statements) {
        returner.push_back(pointer.get());
    }
    return returner;
}



Paper::Paper(Length height, Length width) { 
    this->height = std::make_unique<Statement<Length>>("height", height);
    this->width = std::make_unique<Statement<Length>>("width", width);
}

void Paper::set_even_margins(Length left_margin,
                             Length right_margin,
                             Length top_margin,
                             Length bottom_margin) {
    this->even_margins[0] = std::make_unique<Statement<Length>>("el_margin", left_margin);
    this->even_margins[1] = std::make_unique<Statement<Length>>("er_margin", right_margin);
    this->even_margins[2] = std::make_unique<Statement<Length>>("et_margin",top_margin);
    this->even_margins[3] = std::make_unique<Statement<Length>>("eb_margin",bottom_margin);
}

void Paper::set_odd_margins(Length left_margin,
                            Length right_margin,
                            Length top_margin,
                            Length bottom_margin) {
    this->odd_margins[0] = std::make_unique<Statement<Length>>("ol_margin", left_margin);
    this->odd_margins[1] = std::make_unique<Statement<Length>>("or_margin", right_margin);
    this->odd_margins[2] = std::make_unique<Statement<Length>>("ot_margin", top_margin);
    this->odd_margins[3] = std::make_unique<Statement<Length>>("ob_margin", bottom_margin);
}

Statement<Length>* Paper::get_margin(Paper::Margins margin) {
    switch (margin) {
        case Margins::EvenLeftMargin:
            return this->even_margins[0].get();
            break;
        case Margins::EvenRightMargin:
            return this->even_margins[1].get();
            break;
        case Margins::EvenTopMargin:
            return this->even_margins[2].get();
            break;
        case Margins::EvenBottomMargin:
            return this->even_margins[3].get();
            break;
        case Margins::OddLeftMargin:
            return this->odd_margins[0].get();
            break;
        case Margins::OddRightMargin:
            return this->odd_margins[1].get();
            break;
        case Margins::OddTopMargin:
            return this->odd_margins[2].get();
            break;
        case Margins::OddBottomMargin:
            return this->odd_margins[3].get();
            break;
    }
    throw std::logic_error("Impossible margin request");
}


