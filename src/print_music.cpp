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

void MusicTree::PrintMusicFunctor::operator()() {
    for (int i = 4; i < tree_ptr->statements.size(); ++i) {
        // Get the pointer
        auto part_ptr = dynamic_cast<Part*>(tree_ptr->statements.at(i).get());

        tree_ptr->out << R"||(part-)||"
        << tree_ptr->convert_number_names(part_ptr->get_id()) << " = {"
        << newline;
        for (int i = 0; i < part_ptr->size(); ++i) {
            print_measure(part_ptr->at(i));
        }
        tree_ptr->out << "}" << newline;
    }
}

void MusicTree::PrintMusicFunctor::print_measure(const Measure* measure_ptr) {
    for (int i = 0; i < measure_ptr->size(); ++i) {
        auto subobj_ptr = measure_ptr->at(i);

        std::string subobj_iden = subobj_ptr->get_subtype();

        if (subobj_iden == "note") {
            print_note(dynamic_cast<Note*>(subobj_ptr));
        }
        /*
        else if (subobj_iden == "tuplet") {
            print_tuplets(dynamic_cast<aux::Tuplet*>(subobj_ptr));
        }
         */
    }

    tree_ptr->out << " |" << MusicTree::newline;
}

        /*
void MusicTree::PrintMusicFunctor::print_tuplets(const aux::Tuplet* tuplet_ptr) {
    tree_ptr->out << fmt::format(R"||(\tuplet {0}/{1} {2})||",
                                 tuplet_ptr->actual_notes(),
                                 tuplet_ptr->normal_notes(),
                                 "{");

    for (int i = 0; i < tuplet_ptr->size(); ++i) {
        auto subobj_ptr = tuplet_ptr->at(i);

        std::string subobj_iden = subobj_ptr->get_subtype();

        if (subobj_iden == "note") {
            auto note_ptr = dynamic_cast<Note*>(subobj_ptr);
            print_note(note_ptr,
                       (tree_ptr->measure_duration / note_ptr->duration()) *
                           tuplet_ptr->normal_notes() /
                           tuplet_ptr->actual_notes());
        }
    }

    tree_ptr->out << " }";
}
        */

void MusicTree::PrintMusicFunctor::print_note(const Note* note_ptr) {
    unsigned int lilypond_duration = tree_ptr->measure_duration / note_ptr->duration();
    this->print_note(note_ptr, lilypond_duration);
}

void MusicTree::PrintMusicFunctor::print_note(const Note* note_ptr,
                                              unsigned int lilypond_duration) {
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
    if (note_ptr->pitch_class() == 'r') {
        octave_text = "";
    }
    else if (note_ptr->octave() > 3) {
        octave_text = std::string(note_ptr->octave() - 3, '\'');
    }
    else if (note_ptr->octave() < 3) {
        octave_text = std::string((note_ptr->octave() - 3) * -1, ',');
    }
    
    tree_ptr->out << note_ptr->pitch_class() << alter_text << octave_text << lilypond_duration << " ";
}
