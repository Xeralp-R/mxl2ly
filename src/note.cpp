//
//  note.cpp
//  mxl2ly
//
//  Created by Reventar on 17/11/2021.
//

#include "note.hpp"

#include <iostream>
#include <algorithm>

using namespace lmt;

Note::Pitch::Pitch(char pitch_class, short int octave, short int alteration) {
    if (!is_element(valid_pitch_classes.begin(),
                    valid_pitch_classes.end(),
                    pitch_class)) {
        throw std::logic_error("Invalid pitch class");
    }
    if (!is_element(valid_octaves.begin(),
                    valid_octaves.end(),
                    octave)) {
        throw std::logic_error("Invalid octave");
    }
    if (!is_element(valid_alterations.begin(),
                    valid_alterations.end(),
                    alteration)) {
        throw std::logic_error("Invalid alteration (sharp/flat)");
    }
    
    this->pitch_class = pitch_class;
    this->octave = octave;
    this->alteration = alteration;
}

// ==> Constructors and private setters

Note::Note(lmt::Note::Pitch pitch, unsigned duration, short dotted)
: pitch(pitch), mxl_dur(duration), dotted(dotted) {}

Note::Note(Note::Rest rest, unsigned duration, short dotted)
: pitch(Pitch('r', 0, 0)), mxl_dur(duration), dotted(dotted) {}

void Note::add_notation(std::unique_ptr<lmt::aux::AbstractNotation> notation) {
    this->notations.push_back(std::move(notation));
}

void Note::add_attribute(std::unique_ptr<aux::AbstractNoteAttribute> attribute) {
    auto attr_subtype = attribute->get_subtype();
    
    int i = attribute_dispatcher.at(attr_subtype)();
    attributes.at(i) = std::move(attribute);
}

std::optional<aux::GraceNote> Note::get_grace_note() const {
    if (!attributes.at(0)) {
        return std::nullopt;
    }
    return *(dynamic_cast<aux::GraceNote*>(attributes.at(0).get()));
}

std::optional<aux::Chord> Note::get_chord() const { 
    if (!attributes.at(1)) {
        return std::nullopt;
    }
    return *(dynamic_cast<aux::Chord*>(attributes.at(1).get()));
}

std::optional<aux::Tuplet> Note::get_tuplet() const {
    if (!attributes.at(2)) {
        return std::nullopt;
    }
    return *(dynamic_cast<aux::Tuplet*>(attributes.at(2).get()));
}
