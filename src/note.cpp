//
//  note.cpp
//  mxl2ly
//
//  Created by Reventar on 17/11/2021.
//

#include "note.hpp"
#include "music_tree.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>

#include "tinyxml2/tixml2ex.h"

using namespace lmt;
namespace tx2 = tinyxml2;

Note::Pitch::Pitch(char pitch_class, short int octave, short int alteration)
    : pitch_class(pitch_class), octave(octave), alteration(alteration) {
    if (!is_element(valid_pitch_classes.begin(), valid_pitch_classes.end(),
                    pitch_class)) {
        throw std::logic_error("Invalid pitch class");
    }
    if (!is_element(valid_octaves.begin(), valid_octaves.end(), octave)) {
        throw std::logic_error("Invalid octave");
    }
    if (!is_element(valid_alterations.begin(), valid_alterations.end(),
                    alteration)) {
        throw std::logic_error("Invalid alteration (sharp/flat)");
    }

    this->pitch_class = pitch_class;
    this->octave      = octave;
    this->alteration  = alteration;
}

// ==> Constructors and private setters

Note::Note(lmt::Note::Pitch pitch, unsigned lly_dur, short dotted)
    : pitch(pitch), lly_dur(lly_dur), dotted(dotted) {}

Note::Note(const tinyxml2::XMLElement* note_ptr, const MusicTree* tree_ptr) {
    using tx2::find_element;

    // set duration
    if (tx2::exists(note_ptr, "type")) {
        this->lly_dur =
            this->duration_dispatcher.at(tx2::text(note_ptr, "type"))();
    } else if (!tx2::exists(note_ptr, "grace")) {
        auto mxl_dur  = tx2::int_text(note_ptr, "duration");
        this->lly_dur = std::round(tree_ptr->get_measure_duration() / mxl_dur);

    } else {
    }

    for (auto i = tx2::find_element(note_ptr, "dot"); i != nullptr;
         i      = i->NextSiblingElement("dot")) {
        this->dotted += 1;
    }

    // set pitch
    if (tx2::exists(note_ptr, "pitch")) {
        // pitch_elem_ptr->FirstChildElement("step")->GetText()[0]
        // pitch_elem_ptr->FirstChildElement("octave")->IntText();
        // note_ptr->FirstChildElement("alter")->IntText();

        auto pitch_elem_ptr = note_ptr->FirstChildElement("pitch");

        this->pitch.pitch_class =
            std::tolower(tx2::text(pitch_elem_ptr, "step")[0]);
        this->pitch.octave = tx2::int_text(pitch_elem_ptr, "octave");

        if (note_ptr->FirstChildElement("alter") != nullptr) {
            this->pitch.alteration = tx2::int_text(note_ptr, "alter");
        }
    }

    // handle articulation, ornaments, etc.

    // handle grace note
    if (tx2::exists(note_ptr, "grace")) {
        auto grace_before =
            tx2::exists(note_ptr->PreviousSiblingElement(), "grace");
        auto grace_after = tx2::exists(note_ptr->NextSiblingElement(), "grace");
        auto function    = [&](StartStopType type) {
            auto grace_elem = tx2::find_element(note_ptr, "grace");
            bool is_slashed = false;
            if (tx2::attribute_value(grace_elem, "slash") == "yes") {
                is_slashed = true;
            }
            auto i = std::make_unique<aux::GraceNote>(type, is_slashed);
            this->add_attribute(std::move(i));
        };

        if (!grace_before && !grace_after) {
            function(StartStopType::Both);
        } else if (!grace_before && grace_after) {
            function(StartStopType::Start);
        } else if (grace_before && !grace_after) {
            function(StartStopType::Stop);
        } else {
            // Don't do anything.
        }
    }

    // handle tuplet
    if (tx2::exists(note_ptr, "notations/tuplet")) {
        StartStopType type = StartStopType::Start;
        if (tx2::attribute_value(
                tx2::find_element(note_ptr, "notations/tuplet"), "type") ==
            "stop") {
            type = StartStopType::Stop;
        }
        unsigned short int actual_notes = tx2::int_text(
            tx2::find_element(note_ptr, "time-modification/actual-notes"));
        unsigned short int normal_notes = tx2::int_text(
            tx2::find_element(note_ptr, "time-modification/normal-notes"));
        this->add_attribute(
            std::make_unique<aux::Tuplet>(type, actual_notes, normal_notes));
    }

    // handle chord
    // The start of a chord is usually not indicated as <chord>. Thus,
    // we have to compare against the next element rather than comparing against
    // the previous one.
    if (!tx2::exists(note_ptr, "chord") &&
        tx2::exists(note_ptr->NextSiblingElement(), "chord")) {
        this->add_attribute(std::make_unique<aux::Chord>(StartStopType::Start));
    }
    if (tx2::exists(note_ptr, "chord") &&
        !tx2::exists(note_ptr->NextSiblingElement(), "chord")) {
        this->add_attribute(std::make_unique<aux::Chord>(StartStopType::Stop));
    }

    // get notations
    for (auto notation_ptr : tx2::selection(note_ptr, "notations")) {
        for (auto object_ptr : notation_ptr) {
            auto temp = notation_factory(object_ptr);
            for (auto& i : temp) {
                this->notations.push_back(std::move(i));
            }
        }
    }
}

void Note::add_notation(std::unique_ptr<lmt::aux::AbstractNotation> notation) {
    this->notations.push_back(std::move(notation));
}

void Note::add_attribute(
    std::unique_ptr<aux::AbstractNoteAttribute> attribute) {
    auto attr_subtype = attribute->get_subtype();

    int i            = attribute_dispatcher.at(attr_subtype)();
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

std::vector<aux::AbstractNotation*> Note::get_notations() const {
    std::vector<aux::AbstractNotation*> returner;
    returner.reserve(notations.size());
    for (auto& i : this->notations) {
        returner.push_back(i.get());
    }
    return returner;
}
