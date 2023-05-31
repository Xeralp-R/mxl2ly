//
//  chord.cpp
//  mxl2ly
//
//  Created by Reventar on 16/01/2022.
//

#include "chord.hpp"
#include "music_tree.hpp"

#include <iterator>

#include "fmt/format.h"

using namespace lmt;
namespace tx2 = tinyxml2;

Chord::Chord(std::vector<tinyxml2::XMLElement*> elements,
             const MusicTree*                   tree_ptr) {
    auto first_elem = elements.front();
    auto last_elem  = elements.back();

    // get the duration of the first note
    if (tx2::exists(first_elem, "type")) {
        lly_dur = duration_dispatcher.at(tx2::text(first_elem, "type"));
    } else if (!tx2::exists(first_elem, "grace")) {
        auto mxl_dur = tx2::int_text(first_elem, "duration");
        lly_dur      = std::round(tree_ptr->get_measure_duration() / mxl_dur);
    } else {
        lly_dur = 16;
    }
    dotted = std::distance(tx2::selection(first_elem, "dot").begin(),
                           tx2::selection(first_elem, "dot").end());
    /* Alt code:
    for (auto i = tx2::find_element(first_elem, "dot"); i != nullptr;
         i      = i->NextSiblingElement("dot")) {
        dotted += 1;
    }*/

    // get the pitches of the notes
    for (auto elem_ptr : elements) {
        if (!tx2::exists(elem_ptr, "pitch")) {
            pitches.push_back(Note::Pitch('r', 0, 0));
        }

        auto pitch_class = std::tolower(tx2::text(elem_ptr, "pitch/step")[0]);
        auto octave      = tx2::int_text(elem_ptr, "pitch/octave");
        auto alteration  = int(0);
        if (tx2::exists(elem_ptr, "pitch/alter")) {
            alteration = tx2::int_text(elem_ptr, "pitch/alter");
        }
        pitches.push_back(Note::Pitch(pitch_class, octave, alteration));
    }

    // handle grace note
    if (tx2::exists(first_elem, "grace")) {
        auto grace_before =
            tx2::exists(first_elem->PreviousSiblingElement(), "grace");
        auto grace_after =
            tx2::exists(last_elem->NextSiblingElement(), "grace");

        // if neither the element before and after have a grace note
        // AKA it's not the middle note of a 3-note grace
        if (!grace_before || !grace_after) {
            StartStopType start_stop;
            if (!grace_before && !grace_after) {
                start_stop = StartStopType::Both;
            } else if (!grace_before && grace_after) {
                start_stop = StartStopType::Start;
            } else if (grace_before && !grace_after) {
                start_stop = StartStopType::Stop;
            }

            auto grace_elem = tx2::find_element(first_elem, "grace");
            bool is_slashed = false;
            if (tx2::attribute_value(grace_elem, "slash") == "yes") {
                is_slashed = true;
            }
            attributes.at(0) = std::move(
                std::make_unique<aux::GraceNote>(start_stop, is_slashed));
        }
    }

    // handle tuplet
    if (tx2::exists(first_elem, "notations/tuplet")) {
        StartStopType type = StartStopType::Start;
        if (tx2::attribute_value(
                tx2::find_element(first_elem, "notations/tuplet"), "type") ==
            "stop") {
            type = StartStopType::Stop;
        }

        unsigned short int actual_notes = tx2::int_text(
            tx2::find_element(first_elem, "time-modification/actual-notes"));
        unsigned short int normal_notes = tx2::int_text(
            tx2::find_element(first_elem, "time-modification/normal-notes"));

        attributes.at(1) =
            std::make_unique<aux::Tuplet>(type, actual_notes, normal_notes);
    }

    // handle all notations
    for (auto elem_ptr : elements) {
        for (auto notation_ptr : tx2::selection(elem_ptr, "notations")) {
            for (auto object_ptr : notation_ptr) {
                auto temp = notation_factory(object_ptr);
                for (auto& i : temp) {
                    this->note_objects.push_back(std::move(i));
                }
            }
        }
    }
}

std::string Chord::return_lilypond() const {
    std::string lilypond_duration;
    if (lly_dur > 0) {
        lilypond_duration = std::to_string(lly_dur);
        lilypond_duration += std::string(dotted, '.');
    } else if (lly_dur == duration_dispatcher.at("breve")) {
        lilypond_duration = R"__(\breve)__";
    } else if (lly_dur == duration_dispatcher.at("long")) {
        lilypond_duration = R"__(\longa)__";
    }

    std::string pitch_text;
    for (auto pitch : pitches) {
        pitch_text += pitch.return_lilypond() + " ";
    }

    // Generate any and all text before and after the thing
    std::string before_text, after_text;

    auto maybe_grace = dynamic_cast<aux::GraceNote*>(attributes.at(0).get());
    if (maybe_grace) {
        auto pair = maybe_grace->return_lilypond();
        before_text += pair.first;
        after_text = pair.second + after_text;
    }

    auto maybe_tuplet = dynamic_cast<aux::Tuplet*>(attributes.at(1).get());
    if (maybe_tuplet) {
        auto pair = maybe_tuplet->return_lilypond();
        before_text += pair.first;
        after_text = pair.second + after_text;
    }

    std::string notation_string;
    for (const auto& i : note_objects) {
        notation_string += i->return_lilypond();
    }

    std::string note_text = fmt::format("<{0}>{1}{2} ", pitch_text,
                                        lilypond_duration, notation_string);

    return before_text + note_text + after_text + " ";
}

void Chord::add_note_object(
    std::unique_ptr<lmt::aux::AbstractNoteObject> note_object) {
    this->note_objects.push_back(std::move(note_object));
}
