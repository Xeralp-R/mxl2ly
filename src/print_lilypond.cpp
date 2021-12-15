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

using namespace lmt;

void MusicTree::print_lilypond(std::string filename) {
    std::cout << "Printing to: " << filename;
    //std::ofstream lilypond_file (filename);
    //lilypond_file << "% Automatically generated from musicxml file.";
}
