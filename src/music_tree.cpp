//
//  music_tree.cpp
//  mxl2ly
//
//  Created by Reventar on 11/11/2021.
//

#include "music_tree.hpp"

#include <vector>
#include <string_view>
#include <memory>
#include <iostream>
#include <fstream>

#include "header_and_paper.hpp"
#include "part.hpp"

using namespace lmt;

// Main execution

void MusicTree::accept_musicxml(std::string filename) {
    this->xml_document.LoadFile(filename.c_str());
    this->root_element = this->xml_document.FirstChildElement("score-partwise");
    
    this->extract_staff_info();
    this->extract_paper_block();
    this->extract_header_block();
    this->extract_part_list();
    this->extract_music();
    
    std::cout << "Loaded file in class!" << std::endl;
}

void MusicTree::print_lilypond(std::string filename) {
    std::cout << "Printing to: " << filename << '\n';
    std::ofstream lilypond_file (filename);
    lilypond_file << "% Automatically generated from a musicxml file.\n\n";
    
    this->print_staff_info();
    this->print_paper_block();
    this->print_header_block();
}
