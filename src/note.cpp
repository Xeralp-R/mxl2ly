//
//  note.cpp
//  mxl2ly
//
//  Created by Reventar on 17/11/2021.
//

#include "note.hpp"

#include <iostream>
#include <algorithm>

//#include "exceptions.hpp"
#include "genexceptions.hpp"
#include "auxiliary.hpp"

using namespace lly;

// ==> Constructors and private setters

Note::Note(char pitch_class,
           lly::aux::Accidental accidental,
           short octave,
           short duration) {
    // Not using an initializer list, because the things have to be checked:
    // I'll just use the setter functions
    set_pitch_class(pitch_class);
    set_accidental(accidental);
    set_octave(octave);
    set_duration(duration);
}

Note::Note(char pitch_class,
           lly::aux::Accidental accidental,
           short octave,
           short duration,
           short dotted) {
    // also includes stem direction
    set_pitch_class(pitch_class);
    set_accidental(accidental);
    set_octave(octave);
    set_duration(duration);
    this->dotted = dotted;
}

void Note::set_pitch_class(char c) {
    // find if c is inside the valid_pitch_classes thing
    bool b = std::any_of(valid_pitch_classes.begin(),
                         valid_pitch_classes.end(),
                         [&](auto i){return i == c;});
    // if not
    if (!b) {
        // throw an invalid input exception
        exp::InvalidInputException iie ("pitch class",
                                        lly::aux::stringify(valid_pitch_classes),
                                        std::string(1,c));
        throw iie;
    }
    // assign
    this->pitch_class = c;
}

void Note::set_accidental(lly::aux::Accidental acc) {
    // add future validation here, if necessary
    this->accidental = acc;
}

void Note::set_octave(short int si) {
    // find if si is inside the valid_octaves thing
    bool b = std::any_of(valid_octaves.begin(),
                         valid_octaves.end(),
                         [&](auto i){return i == si;});
    // if it isn't
    if (!b) {
        // throw an invalid input exception
        exp::InvalidInputException iie ("note octave",
                                        lly::aux::stringify(valid_octaves),
                                        std::to_string(si));
        throw iie;
    }
    // assign
    this->octave = si;
}

void Note::set_duration(short int si) {
    // find if si is inside the valid_durations thing
    bool b = std::any_of(valid_durations.begin(),
                         valid_durations.end(),
                         [&](auto i){return i == si;});
    // if it isn't
    if (!b) {
        // throw an invalid input exception
        exp::InvalidInputException iie ("note duration",
                                        lly::aux::stringify(valid_durations),
                                        std::to_string(si));
        throw iie;
    }
    // assign
    this->duration = si;
}

void Note::set_stem_direction(bool b) {
    // add future validation here, if necessary
    stem_direction = b;
}

// ==> public setters

void Note::add_note_object(lly::aux::Dynamic dym) {
    notations.push_back(dym);
}

void Note::add_note_object(lly::aux::Articulation art) {
    notations.push_back(art);
}

void Note::add_note_object(lly::aux::Ornament orn) {
    notations.push_back(orn);
}

void Note::add_note_object(lly::aux::Spanner span) {
    switch (span.type) {
            // for some very odd reason,
            // musicxml lists slurs as notations and not directions.
            // this is followed.
        case lly::aux::Spanner::Slur:
            notations.push_back(span);
            break;
        default:
            directions.push_back(span);
            break;
    }
}

void Note::add_note_object(lly::aux::Markup mark) {
    directions.push_back(mark);
}

// ==> getters

char Note::get_pitch_class() {
    return pitch_class;
}

lly::aux::Accidental Note::get_accidental() {
    return accidental;
}

short int Note::get_octave() {
    return octave;
}

lly::aux::Duration Note::get_duration() {
    lly::aux::Duration temp;
    temp.time = duration;
    temp.dotted = dotted;
    return temp;
}

// ==> functions

std::ostream& operator<<(std::ostream& os, const lly::Note& nt) {
    os << "NOTE: \nPitch Class: " << nt.pitch_class << ";\nAccidental: " << nt.accidental << ";\n";
    os << "Octave: " << nt.octave << ";\nDuration: " << nt.duration << ";\n";
    // Add more here later...
    return os;
}
