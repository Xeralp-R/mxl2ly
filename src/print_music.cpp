//
//  print_music.cpp
//  mxl2ly
//
//  Created by Reventar on 24/12/2021.
//

#include "music_tree.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <string_view>
#include <vector>

#include "fmt/format.h"
#include "header_and_paper.hpp"
#include "part.hpp"

using namespace lmt;

// Functions
static void print_measure(std::ostream& out, const Measure* measure_ptr);
static void print_note(std::ostream& out, const Note* note_ptr);

void MusicTree::print_music() const {
    for (int i = 4; i < statements.size(); ++i) {
        // Get the pointer
        auto part_ptr = dynamic_cast<Part*>(this->statements.at(i).get());

        out << R"||(\"part-)||" << part_ptr->get_id() << R"||(" {)||"
            << newline;
        for (int i = 0; i < part_ptr->size(); ++i) {
            print_measure(out, part_ptr->at(i));
        }
        out << "}" << newline;
    }
}

static void print_measure(std::ostream& out, const Measure* measure_ptr) {
    for (int i = 0; i < measure_ptr->size(); ++i) {
        auto subobj_ptr = measure_ptr->at(i);

        std::string_view subobj_iden = subobj_ptr->get_subtype();

        if (subobj_iden == "note") {
            print_note(out, dynamic_cast<Note*>(subobj_ptr));
        }
    }

    out << " |" << MusicTree::newline;
}

static void print_note(std::ostream& out, const Note* note_ptr) {
    std::string alter_text;
    switch (note_ptr->alteration()) {
        case 2:  alter_text = "isis"; break;
        case 1:  alter_text = "is";   break;
        case 0:  alter_text = "";     break;
        case -1: alter_text = "es";   break;
        case -2: alter_text = "eses"; break;
        default:
            std::cerr << fmt::format("Unusual Alteration of {0}. Discarding.\n",
                                     note_ptr->alteration());
            alter_text = "";
            break;
    }
    
    std::string octave_text;
    if (note_ptr->octave() > 3) {
        octave_text = std::string("'", note_ptr->octave() - 3);
    }
    else if (note_ptr->octave() < 3) {
        octave_text = std::string(",", (note_ptr->octave() - 3) * -1);
    }
    
    unsigned int lilypond_dur = note_ptr->duration() / MusicTree::measure_duration;
    
    std::cout << "Note";
}
