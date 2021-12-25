//
//  print_music.cpp
//  mxl2ly
//
//  Created by Reventar on 24/12/2021.
//

#include "music_tree.hpp"

#include <vector>
#include <string_view>
#include <memory>
#include <iostream>
#include <fstream>

#include "header_and_paper.hpp"
#include "part.hpp"
#include "fmt/format.h"

using namespace lmt;

// Functions
static void print_measure(std::ostream& out, const Measure* measure_ptr);
static void print_note(std::ostream& out, const Note* note_ptr);

void MusicTree::print_music() const {
    for (int i = 5; i < statements.size(); ++i) {
        // Get the pointer
        auto part_ptr = dynamic_cast<Part*>(this->statements.at(i).get());
        
        out << R"||(\"part-)||" << part_ptr->get_id() << R"||(" {)||" << newline;
        for (int i = 0; i < part_ptr->size(); ++i) {
            print_measure(out, part_ptr->at(i));
        }
        out << "}" << newline;
    }
}

static void print_measure(std::ofstream& out, const Measure* measure_ptr) {
    
    out << " |" << MusicTree::newline;
}
