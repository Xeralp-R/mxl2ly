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

Note::Note(lmt::Note::Pitch pitch, short duration) : pitch(pitch) {
    // todo later
    this->duration = duration;
}

Note::Note(lmt::Note::Pitch pitch, short duration, short dotted)
: pitch(pitch), dotted(dotted) {
    this->duration = duration;
}

void Note::add_notation(std::unique_ptr<lmt::aux::AbstractNotation> notation) {
    this->notations.push_back(notation);
}
