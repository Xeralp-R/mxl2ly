//
//  extract_paper_block.cpp
//  mxl2ly
//
//  Created by Reventar on 05/12/2021.
//

#include "music_tree.hpp"

#include "header_and_paper.hpp"
#include "part.hpp"
#include "tinyxml2/tixml2ex.h"

using namespace lmt;
namespace tx2 = tinyxml2;

void MusicTree::extract_staff_info() {
    auto* scaling_ptr = tx2::find_element(this->root_element, "defaults/scaling");
    // this->root_element->FirstChildElement("defaults")
    // ->FirstChildElement("scaling");
    
    double staff_width =
    scaling_ptr->FirstChildElement("millimeters")->FloatText();
    double tenths_in_staff =
    scaling_ptr->FirstChildElement("tenths")->FloatText();
    this->tenths_to_mm_conversion = staff_width / tenths_in_staff;
    
    this->measure_duration =
    root_element->FirstChildElement("part")->FirstChildElement("measure")
    ->FirstChildElement("attributes")->FirstChildElement("divisions")->IntText() * 4;
    
    this->statements.emplace_back(std::make_unique<Statement<Length>>("staff_size",
                                                                      millimeters(staff_width)));
    
    
    this->root_element->FirstChildElement("defaults")->DeleteChild(scaling_ptr);
}

void MusicTree::extract_paper_block() {
    auto* page_layout_pointer =
    this->root_element->FirstChildElement("defaults")
    ->FirstChildElement("page-layout");
    
    double height_in_tenths =
    page_layout_pointer->FirstChildElement("page-height")->FloatText();
    
    double width_in_tenths =
    page_layout_pointer->FirstChildElement("page-width")->FloatText();
    
    auto paper_pointer = std::make_unique<Paper>(tenths(height_in_tenths,
                                                        this->tenths_to_mm_conversion),
                                                 tenths(width_in_tenths,
                                                        this->tenths_to_mm_conversion));
    
    tx2::XMLElement* margin_pointer =
    page_layout_pointer->FirstChildElement("page-margins");
    
    // Case 0: margin_pointer is null, meaning that we set default.
    if (margin_pointer == nullptr) {
        paper_pointer->set_margins(default_margins[0], default_margins[1],
                                   default_margins[2], default_margins[3]);
    } else {
        // Just set using the first paper pointer.
        paper_pointer->set_margins(
                                   tenths(margin_pointer->FirstChildElement("left-margin")
                                          ->FloatText(),
                                          this->tenths_to_mm_conversion),
                                   tenths(margin_pointer->FirstChildElement("right-margin")
                                          ->FloatText(),
                                          this->tenths_to_mm_conversion),
                                   tenths(margin_pointer->FirstChildElement("top-margin")
                                          ->FloatText(),
                                          this->tenths_to_mm_conversion),
                                   tenths(margin_pointer->FirstChildElement("bottom-margin")
                                          ->FloatText(),
                                          this->tenths_to_mm_conversion));
    }
    
    this->statements.emplace_back(std::move(paper_pointer));
    
    this->root_element->FirstChildElement("defaults")
    ->DeleteChild(page_layout_pointer);
}

void MusicTree::extract_header_block() {
    auto header_ptr = std::make_unique<Header>();
    
    for (tx2::XMLElement *runner = this->root_element->FirstChildElement("credit");
         runner != nullptr;
         runner = this->root_element->FirstChildElement("credit")) {
        
        std::string credit_type =
        runner->FirstChildElement("credit-type")->GetText();
        std::string credit_words =
        runner->FirstChildElement("credit-words")->GetText();
        
        header_ptr->add_statement({credit_type, credit_words});
        
        this->root_element->DeleteChild(runner);
    }
    
    this->statements.emplace_back(std::move(header_ptr));
}

void MusicTree::extract_part_list() {
    auto* element_ptr = this->root_element->FirstChildElement("part-list");
    
    auto part_list_ptr = std::make_unique<PartList>();
    
    for (auto* score_ptr = element_ptr->FirstChildElement("score-part");
         score_ptr != nullptr;
         score_ptr = score_ptr->NextSiblingElement() ) {
        
        part_list_ptr->add_part(score_ptr->Attribute("id"),
                                score_ptr->FirstChildElement("part-name")->GetText());
        
        this->valid_part_ids.push_back(score_ptr->Attribute("id"));
    }
    
    this->statements.emplace_back(std::move(part_list_ptr));
    
    this->root_element->DeleteChild(element_ptr);
}
