//
//  music_tree.cpp
//  mxl2ly
//
//  Created by Reventar on 11/11/2021.
//

#include "music_tree.hpp"

#include <string_view>

#include "header_and_paper.hpp"

MusicTree::MusicTree(std::string filename) { 
    this->xml_document.LoadFile(filename.c_str());
    
    this->extract_staff_info();
    this->extract_paper_block();
    
    std::cout << "Loaded file in class!" << std::endl;
}

void MusicTree::extract_staff_info() {
    double staff_width = atof(this->xml_document
                              .FirstChildElement("score-partwise")
                              ->FirstChildElement("defaults")
                              ->FirstChildElement("scaling")
                              ->FirstChildElement("millimeters")
                              ->GetText()
                              );
    double tenths_in_staff = atof(this->xml_document
                                  .FirstChildElement("score-partwise")
                                  ->FirstChildElement("defaults")
                                  ->FirstChildElement("scaling")
                                  ->FirstChildElement("millimeters")
                                  ->GetText()
                                  );
    this->tenths_to_mm_conversion = staff_width/tenths_in_staff;
    
    this->statements.emplace_back(std::make_unique<Statement<double>>
                                  ("tenths_to_mm", this->tenths_to_mm_conversion));
    this->statements.emplace_back(std::make_unique<Statement<Length>>
                                  ("staff_size", millimeters(staff_width)));
}

static void assign_paper_margins(Paper* assignee,
                                 tinyxml2::XMLElement* xml_element,
                                 double tenths_to_mm_conversion,
                                 int odd_or_even) {
    if (std::string_view(xml_element->Name()) == "page-layout") {
        throw std::logic_error("Unexpected element passed to function 'assign_paper_margins'");
    }
    
    if (odd_or_even % 2 == 0) {
        assignee->set_even_margins(tenths(xml_element->FirstChildElement("left-margin")->FloatText(),
                                          tenths_to_mm_conversion),
                                   tenths(xml_element->FirstChildElement("right-margin")->FloatText(),
                                          tenths_to_mm_conversion),
                                   tenths(xml_element->FirstChildElement("top-margin")->FloatText(),
                                          tenths_to_mm_conversion),
                                   tenths(xml_element->FirstChildElement("bottom-margin")->FloatText(),
                                          tenths_to_mm_conversion)
                                   );
    } else {
        assignee->set_odd_margins(tenths(xml_element->FirstChildElement("left-margin")->FloatText(),
                                        tenths_to_mm_conversion),
                                  tenths(xml_element->FirstChildElement("right-margin")->FloatText(),
                                         tenths_to_mm_conversion),
                                  tenths(xml_element->FirstChildElement("top-margin")->FloatText(),
                                         tenths_to_mm_conversion),
                                  tenths(xml_element->FirstChildElement("bottom-margin")->FloatText(),
                                         tenths_to_mm_conversion)
                                  );
    }
}

void MusicTree::extract_paper_block() { 
    auto page_layout_pointer = this->xml_document.FirstChildElement("score-partwise")
                                                 ->FirstChildElement("defaults")
                                                 ->FirstChildElement("page-layout");
    
    double height_in_tenths = atof(page_layout_pointer
                                   ->FirstChildElement("page-height")
                                   ->GetText()
                                   );
    
    double width_in_tenths = atof(page_layout_pointer
                                  ->FirstChildElement("page-width")
                                  ->GetText()
                                  );
    
    auto paper_pointer = std::make_unique<Paper>(tenths(height_in_tenths,
                                                        this->tenths_to_mm_conversion),
                                                 tenths(width_in_tenths,
                                                        this->tenths_to_mm_conversion));
    
    tinyxml2::XMLElement* margin_pointer_one = page_layout_pointer->FirstChildElement("page-margins");
    
    // Case 0: margin_pointer is null, meaning that we set default.
    if (margin_pointer_one == nullptr) {
        paper_pointer->set_odd_margins(default_margins[0],
                                       default_margins[1],
                                       default_margins[2],
                                       default_margins[3]
                                       );
    }
    // Case 1: there is only 1 margin pointer, meaning it has to be assigned twice.
    else if (std::string_view(margin_pointer_one->Attribute("type")) == "" ||
             std::string_view(margin_pointer_one->Attribute("type")) == "both" ||
             margin_pointer_one->NextSiblingElement("page-margins") == nullptr) {
        
        assign_paper_margins(paper_pointer.get(),
                             margin_pointer_one,
                             this->tenths_to_mm_conversion,
                             1);
        assign_paper_margins(paper_pointer.get(),
                             margin_pointer_one,
                             this->tenths_to_mm_conversion,
                             2);
    }
    // Case 2: there are 2 margin pointers, meaning we have to separate by odd/even
    else if (std::string_view(margin_pointer_one->Attribute("type")) == "odd") {
        auto margin_pointer_two = margin_pointer_one->NextSiblingElement("page-margins");
        
        assign_paper_margins(paper_pointer.get(),
                             margin_pointer_one,
                             this->tenths_to_mm_conversion,
                             1);
        assign_paper_margins(paper_pointer.get(),
                             margin_pointer_two,
                             this->tenths_to_mm_conversion,
                             2);
    }
    else if (std::string_view(margin_pointer_one->Attribute("type")) == "even") {
        auto margin_pointer_two = margin_pointer_one->NextSiblingElement("page-margins");
        
        assign_paper_margins(paper_pointer.get(),
                             margin_pointer_two,
                             this->tenths_to_mm_conversion,
                             1);
        assign_paper_margins(paper_pointer.get(),
                             margin_pointer_one,
                             this->tenths_to_mm_conversion,
                             2);
    }
    
    this->statements.emplace_back(std::move(paper_pointer));
}
