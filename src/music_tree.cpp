//
//  music_tree.cpp
//  mxl2ly
//
//  Created by Reventar on 11/11/2021.
//

#include "music_tree.hpp"


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
    
    this->statements.emplace_back(std::make_unique<AbstractStatement>
                                  (Statement("tenths_to_mm", this->tenths_to_mm_conversion))
                                  );
    this->statements.emplace_back(std::make_unique<AbstractStatement>
                                  (Statement("staff_size", millimeters(staff_width)))
                                  );
}

