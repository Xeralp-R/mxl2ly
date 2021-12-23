//
//  extract_paper_block.cpp
//  mxl2ly
//
//  Created by Reventar on 05/12/2021.
//

#include "music_tree.hpp"

#include "header_and_paper.hpp"
#include "part.hpp"

using namespace lmt;

void MusicTree::extract_paper_block() {
    auto* page_layout_pointer =
    this->root_element->FirstChildElement("defaults")
    ->FirstChildElement("page-layout");
    
    double height_in_tenths =
    page_layout_pointer->FirstChildElement("page-height")->FloatText();
    
    double width_in_tenths =
    page_layout_pointer->FirstChildElement("page-width")->FloatText();
    
    auto paper_pointer = std::make_unique<Paper>(
                                                 tenths(height_in_tenths, this->tenths_to_mm_conversion),
                                                 tenths(width_in_tenths, this->tenths_to_mm_conversion));
    
    tinyxml2::XMLElement* margin_pointer =
    page_layout_pointer->FirstChildElement("page-margins");
    
    // Case 0: margin_pointer is null, meaning that we set default.
    if (margin_pointer == nullptr) {
        paper_pointer->set_margins(default_margins[0], default_margins[1],
                                   default_margins[2], default_margins[3]);
    } else {
        // Just set using the first paper pointer.
        paper_pointer->set_margins(
                                   tenths(
                                          margin_pointer->FirstChildElement("left-margin")->FloatText(),
                                          this->tenths_to_mm_conversion),
                                   tenths(
                                          margin_pointer->FirstChildElement("right-margin")->FloatText(),
                                          this->tenths_to_mm_conversion),
                                   tenths(margin_pointer->FirstChildElement("top-margin")->FloatText(),
                                          this->tenths_to_mm_conversion),
                                   tenths(
                                          margin_pointer->FirstChildElement("bottom-margin")->FloatText(),
                                          this->tenths_to_mm_conversion));
    }
    
    this->statements.emplace_back(std::move(paper_pointer));
    
    this->root_element->FirstChildElement("defaults")
    ->DeleteChild(page_layout_pointer);
}
