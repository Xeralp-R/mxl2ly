//
//  print_lilypond.cpp
//  mxl2ly
//
//  Created by Reventar on 15/12/2021.
//

#include "music_tree.hpp"

#include <vector>
#include <string_view>
#include <memory>
#include <iostream>
#include <fstream>

#include "header_and_paper.hpp"

using namespace lmt;

constexpr char newline = '\n';
constexpr auto tab = "    ";

static void print_staff_size(std::ofstream& out, const Statement<Length>* staff_width);
static void print_paper(std::ofstream& out, const Paper* paper_ptr);

void MusicTree::print_lilypond(std::string filename) {
    std::cout << "Printing to: " << filename << '\n';
    std::ofstream lilypond_file (filename);
    lilypond_file << "% Automatically generated from a musicxml file.\n\n";
    
    print_staff_size(lilypond_file, dynamic_cast<Statement<Length>*>(statements.at(1).get()));
    
}

static void print_staff_size(std::ofstream& out, const Statement<Length>* staff_width) {
    out << "#(set-global-staff-size ";
    out << staff_width->get_content().get_points();
    out << ")\n\n";
}

static void print_paper(std::ofstream& out, const Paper* paper_ptr) {
    
    // Output the actual paper thing
    out << R"(\paper {)" << newline;
    out << tab << "";
}
