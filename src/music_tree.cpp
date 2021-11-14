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
    
    this->extract_first_layer();
    
    std::cout << "Loaded file in class!" << std::endl;
}

void MusicTree::extract_first_layer() { 
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
    
    auto margin_pointer_one = page_layout_pointer->FirstChildElement("page-margins");
    
    if (margin_pointer_one == nullptr) {
        paper_pointer->set_odd_margins(default_margins[0],
                                       default_margins[1],
                                       default_margins[2],
                                       default_margins[3]
                                       );
    }
    else if (std::string_view(margin_pointer_one->Attribute("type")) != "") {
        
    }
    
    this->statements.emplace_back(std::move(paper_pointer));
}


