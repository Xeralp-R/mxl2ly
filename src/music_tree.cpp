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
    this->root_element = this->xml_document.FirstChildElement("score-partwise");
    
    this->extract_staff_info();
    this->extract_paper_block();
    this->extract_header_block();
    this->extract_part_list();
    this->extract_music();
    
    std::cout << "Loaded file in class!" << std::endl;
}

// Function Definitions

void MusicTree::extract_staff_info() {
    auto* scaling_ptr = this->root_element->FirstChildElement("defaults")
    ->FirstChildElement("scaling");
    
    double staff_width =
    atof(scaling_ptr->FirstChildElement("millimeters")->GetText());
    double tenths_in_staff =
    atof(scaling_ptr->FirstChildElement("tenths")->GetText());
    this->tenths_to_mm_conversion = staff_width / tenths_in_staff;
    
    this->statements.emplace_back(std::make_unique<Statement<double>>("tenths_to_mm",
                                                                      this->tenths_to_mm_conversion));
    this->statements.emplace_back(std::make_unique<Statement<Length>>("staff_size",
                                                                      millimeters(staff_width)));
    
    
    this->root_element->FirstChildElement("defaults")->DeleteChild(scaling_ptr);
}

// extract_paper_block has been moved elsewhere,
// because it was too long. sorry!

void MusicTree::extract_header_block() {
    auto header_ptr = std::make_unique<Header>();
    
    for (tinyxml2::XMLElement *runner = this->root_element->FirstChildElement("credit");
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

