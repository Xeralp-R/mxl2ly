//
//  music_tree.cpp
//  mxl2ly
//
//  Created by Reventar on 11/11/2021.
//

#include "music_tree.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <string_view>
#include <vector>

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
    this->out.open(filename);
    this->out << "% Automatically generated from a musicxml file." << newline;
    this->out << R"-(\version "2.24.0")-" << newline << newline;

    this->print_staff_info();
    this->print_paper_block();
    this->print_header_block();
    this->print_music();
    this->print_part_list();
}
