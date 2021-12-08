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

static void assign_paper_margins(Paper *assignee,
                                 tinyxml2::XMLElement *xml_element,
                                 double tenths_to_mm_conversion,
                                 int odd_or_even) {
    if (std::string_view(xml_element->Name()) == "page-layout") {
        throw std::logic_error(
                               "Unexpected element passed to function 'assign_paper_margins'");
    }
    
    if (odd_or_even % 2 == 0) {
        assignee->set_even_margins(
                                   tenths(xml_element->FirstChildElement("left-margin")->FloatText(),
                                          tenths_to_mm_conversion),
                                   tenths(xml_element->FirstChildElement("right-margin")->FloatText(),
                                          tenths_to_mm_conversion),
                                   tenths(xml_element->FirstChildElement("top-margin")->FloatText(),
                                          tenths_to_mm_conversion),
                                   tenths(xml_element->FirstChildElement("bottom-margin")->FloatText(),
                                          tenths_to_mm_conversion));
    } else {
        assignee->set_odd_margins(
                                  tenths(xml_element->FirstChildElement("left-margin")->FloatText(),
                                         tenths_to_mm_conversion),
                                  tenths(xml_element->FirstChildElement("right-margin")->FloatText(),
                                         tenths_to_mm_conversion),
                                  tenths(xml_element->FirstChildElement("top-margin")->FloatText(),
                                         tenths_to_mm_conversion),
                                  tenths(xml_element->FirstChildElement("bottom-margin")->FloatText(),
                                         tenths_to_mm_conversion));
    }
}

void MusicTree::extract_paper_block() {
    auto* page_layout_pointer =
    this->root_element->FirstChildElement("defaults")->FirstChildElement("page-layout");
    
    double height_in_tenths =
    page_layout_pointer->FirstChildElement("page-height")->FloatText();
    
    double width_in_tenths =
    page_layout_pointer->FirstChildElement("page-width")->FloatText();
    
    auto paper_pointer = std::make_unique<Paper>(tenths(height_in_tenths, this->tenths_to_mm_conversion),
                                                 tenths(width_in_tenths, this->tenths_to_mm_conversion));
    
    tinyxml2::XMLElement *margin_pointer_one =
    page_layout_pointer->FirstChildElement("page-margins");
    
    // Case 0: margin_pointer is null, meaning that we set default.
    if (margin_pointer_one == nullptr) {
        paper_pointer->set_odd_margins(default_margins[0], default_margins[1],
                                       default_margins[2], default_margins[3]);
        paper_pointer->set_even_margins(default_margins[0], default_margins[1],
                                        default_margins[2], default_margins[3]);
    }
    
    // Case 1: there is only 1 margin pointer, meaning it has to be assigned
    // twice.
    else if (std::string_view(margin_pointer_one->Attribute("type")) == "" ||
             std::string_view(margin_pointer_one->Attribute("type")) == "both" ||
             margin_pointer_one->NextSiblingElement("page-margins") == nullptr) {
        
        assign_paper_margins(paper_pointer.get(), margin_pointer_one,
                             this->tenths_to_mm_conversion, 1);
        assign_paper_margins(paper_pointer.get(), margin_pointer_one,
                             this->tenths_to_mm_conversion, 2);
    }
    
    // Case 2: there are 2 margin pointers, meaning we have to separate by
    // odd/even
    else if (std::string_view(margin_pointer_one->Attribute("type")) == "odd") {
        auto margin_pointer_two =
        margin_pointer_one->NextSiblingElement("page-margins");
        
        assign_paper_margins(paper_pointer.get(), margin_pointer_one,
                             this->tenths_to_mm_conversion, 1);
        assign_paper_margins(paper_pointer.get(), margin_pointer_two,
                             this->tenths_to_mm_conversion, 2);
    } else if (std::string_view(margin_pointer_one->Attribute("type")) ==
               "even") {
        auto margin_pointer_two =
        margin_pointer_one->NextSiblingElement("page-margins");
        
        assign_paper_margins(paper_pointer.get(), margin_pointer_two,
                             this->tenths_to_mm_conversion, 1);
        assign_paper_margins(paper_pointer.get(), margin_pointer_one,
                             this->tenths_to_mm_conversion, 2);
    }
    
    this->statements.emplace_back(std::move(paper_pointer));
    
    this->root_element->FirstChildElement("defaults")->DeleteChild(page_layout_pointer);
}
