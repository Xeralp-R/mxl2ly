//
//  music_tree.cpp
//  mxl2ly
//
//  Created by Reventar on 11/11/2021.
//

#include "music_tree.hpp"

#include <string_view>

#include "header_and_paper.hpp"
#include "part.hpp"

using namespace lmt;

// Main execution

MusicTree::MusicTree(std::string filename) {
    this->xml_document.LoadFile(filename.c_str());
    
    this->extract_staff_info();
    this->extract_paper_block();
    this->extract_header_block();
    
    std::cout << "Loaded file in class!" << std::endl;
}

// Function Definitions

void MusicTree::extract_staff_info() {
    double staff_width =
    atof(this->xml_document.FirstChildElement("score-partwise")
         ->FirstChildElement("defaults")
         ->FirstChildElement("scaling")
         ->FirstChildElement("millimeters")
         ->GetText());
    double tenths_in_staff =
    atof(this->xml_document.FirstChildElement("score-partwise")
         ->FirstChildElement("defaults")
         ->FirstChildElement("scaling")
         ->FirstChildElement("millimeters")
         ->GetText());
    this->tenths_to_mm_conversion = staff_width / tenths_in_staff;
    
    this->statements.emplace_back(std::make_unique<Statement<double>>("tenths_to_mm",
                                                                      this->tenths_to_mm_conversion));
    this->statements.emplace_back(std::make_unique<Statement<Length>>("staff_size",
                                                                      millimeters(staff_width)));
}

// extract_paper_block has been moved elsewhere,
// because it was too long. sorry!

void MusicTree::extract_header_block() {
    auto *root_elem = this->xml_document.FirstChildElement("score-partwise");
    auto header_ptr = std::make_unique<Header>();
    
    for (tinyxml2::XMLElement *runner = root_elem->FirstChildElement("credit");
         std::string_view(runner->Name()) != "credit";
         runner = runner->NextSiblingElement()) {
        
        std::string credit_type =
        runner->FirstChildElement("credit-type")->GetText();
        std::string credit_words =
        runner->FirstChildElement("credit-words")->GetText();
        
        header_ptr->add_statement({credit_type, credit_words});
    }
    
    this->statements.emplace_back(std::move(header_ptr));
}
