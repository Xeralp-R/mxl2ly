//
//  print_music.cpp
//  mxl2ly
//
//  Created by Reventar on 24/12/2021.
//

#include "music_tree.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <string_view>
#include <vector>

#include "fmt/format.h"
#include "header_and_paper.hpp"
#include "part.hpp"

using namespace lmt;

void MusicTree::print_music() const {
    for (int i = 4; i < this->statements.size(); ++i) {
        // Get the pointer
        auto part_ptr = dynamic_cast<Part*>(this->statements.at(i).get());

        /*tree_ptr->out << "part-";
        tree_ptr->out << tree_ptr->convert_number_names(part_ptr->get_id());
        tree_ptr->out << " = {" << newline;
        for (int i = 0; i < part_ptr->size(); ++i) {
            tree_ptr->out << part_ptr->at(i)->return_lilypond();
        }
        tree_ptr->out << "}" << newline;*/
        const auto& [entry, music] = part_ptr->return_lilypond();
        out << music;
        print_directory.push_back(entry);
    }
}
/*
void MusicTree::PrintMusicFunctor::print_measure(const Measure* measure_ptr) {
    for (int i = 0; i < measure_ptr->size(); ++i) {
        auto subobj_ptr = measure_ptr->at(i);

        std::string subobj_iden = subobj_ptr->get_subtype();

        if (subobj_iden == "note") {
            print_note(dynamic_cast<Note*>(subobj_ptr));
        } else if (subobj_iden == "attribute") {
            auto printing_ptr =
                dynamic_cast<aux::AbstractMeasureAttribute*>(subobj_ptr);
            tree_ptr->out << printing_ptr->return_lilypond() << newline;
        }
    }

    tree_ptr->out << " |" << MusicTree::newline;
}
*/
/*
void MusicTree::PrintMusicFunctor::print_note(const Note* note_ptr) {
std::string lilypond_duration;
if (!this->in_chord) {
lilypond_duration = std::to_string(note_ptr->duration());
lilypond_duration += std::string(note_ptr->dots(), '.');
}

std::string alter_text;
switch (note_ptr->alteration()) {
case 2:
alter_text = "isis";
break;
case 1:
alter_text = "is";
break;
case 0:
alter_text = "";
break;
case -1:
alter_text = "es";
break;
case -2:
alter_text = "eses";
break;
default:
std::cerr << fmt::format("Unusual Alteration of {0}. Discarding.\n",
                         note_ptr->alteration());
alter_text = "";
break;
}

std::string octave_text;
if (note_ptr->pitch_class() == 'r') {
octave_text = "";
} else if (note_ptr->octave() > 3) {
octave_text = std::string(note_ptr->octave() - 3, '\'');
} else if (note_ptr->octave() < 3) {
octave_text = std::string((note_ptr->octave() - 3) * -1, ',');
}

// Generate any and all text before and after the thing
std::string before_text, after_text;

auto maybe_grace = note_ptr->get_grace_note();
if (maybe_grace) {
switch (maybe_grace->start_stop) {
case StartStopType::Start:
    before_text += R"--(\grace { )--";
    break;
case StartStopType::Stop:
    after_text = "} " + after_text;
    break;
case StartStopType::Both:
    before_text += R"--(\grace { )--";
    after_text = "} " + after_text;
    break;
}
}

auto maybe_tuplet = note_ptr->get_tuplet();
if (maybe_tuplet) {
switch (maybe_tuplet->start_stop) {
case StartStopType::Start:
    before_text += fmt::format(R"--(\tuplet {0}/{1} {2} )--",
                               maybe_tuplet->actual_notes,
                               maybe_tuplet->normal_notes, "{");
    this->note_time_alteration =
        maybe_tuplet->normal_notes / maybe_tuplet->actual_notes;
    break;
case StartStopType::Stop:
    after_text           = "} " + after_text;
    note_time_alteration = 1.00;
    break;
case StartStopType::Both:
    // Should not be reached.
    break;
}
}

auto maybe_chord = note_ptr->get_chord();
if (maybe_chord) {
switch (maybe_chord->start_stop) {
case StartStopType::Start:
    before_text += "< ";

    in_chord          = true;
    lilypond_duration = "";
    break;
case StartStopType::Stop:
    after_text =
        fmt::format(">{0}{1} {2}", note_ptr->duration(),
                    std::string(note_ptr->dots(), '.'), after_text);

    in_chord = false;
    break;
case StartStopType::Both:
    // Should not be reached.
    break;
}
}

auto        nota_vec = note_ptr->get_notations();
std::string notation_string;
for (auto i : nota_vec) {
notation_string += i->return_lilypond();
}

std::string note_text =
fmt::format("{0}{1}{2}{3}{4} ", note_ptr->pitch_class(), alter_text,
            octave_text, lilypond_duration, notation_string);

tree_ptr->out << before_text << note_text << after_text << " ";
}
 */
