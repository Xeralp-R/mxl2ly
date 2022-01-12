//
//  extract_music.cpp
//  mxl2ly
//
//  Created by Reventar on 08/12/2021.
//

#include "music_tree.hpp"

#include <vector>
#include <utility>
#include <memory>
#include <cctype>
#include <cmath>

#include "part.hpp"
#include "measure.hpp"
#include "note.hpp"
#include "tinyxml2/tixml2ex.h"

using namespace lmt;
namespace tx2 = tinyxml2;

void MusicTree::ExtractMusicFunctor::operator()() {
    for (auto* reader = tree_ptr->root_element->FirstChildElement("part");
         reader != nullptr && is_element(tree_ptr->valid_part_ids.begin(),
                                         tree_ptr->valid_part_ids.end(),
                                         reader->Attribute("id"));
         reader = tree_ptr->root_element->FirstChildElement("part")) {
        
        auto part_ptr = std::make_unique<Part>(reader->Attribute("id"));
        
        for (auto* measure_reader = reader->FirstChildElement("measure");
             measure_reader != nullptr;
             measure_reader = reader->FirstChildElement("measure")) {
            
            auto meas_ptr = extract_measure(measure_reader);
            part_ptr->add_measure(std::move(meas_ptr));
            reader->DeleteChild(measure_reader);
        }
        
        tree_ptr->statements.emplace_back(std::move(part_ptr));
        
        tree_ptr->root_element->DeleteChild(reader);
    }
}

std::unique_ptr<Measure>
MusicTree::ExtractMusicFunctor::extract_measure(tx2::XMLElement* meas_elem_ptr) {
    auto meas_uniq_ptr = std::make_unique<Measure>(meas_elem_ptr->IntAttribute("number"));
    
    auto meas_attributes = extract_measure_attributes(meas_elem_ptr);
    for (auto& ptr : meas_attributes) { meas_uniq_ptr->add_measure_object(std::move(ptr)); }
    
    for (auto reader = meas_elem_ptr->FirstChildElement();
         reader != nullptr;
         reader = reader->NextSiblingElement()) {
        
        std::string_view reader_name = reader->Name();
        
        if (reader_name == "note") {
            auto note = extract_note(reader);
            meas_uniq_ptr->add_measure_object(std::move(note));
        }
        else if (reader_name == "attributes") {
            //auto attributes = convert_attributes(reader);
            //for (auto& i : attributes) { meas_uniq_ptr->add_measure_object(std::move(i)); }
        }
        else if (reader_name == "direction") {
            //auto direction = convert_direction(reader);
            //meas_uniq_ptr->add_measure_object(std::move(direction));
        }
        else if (reader_name == "backup") {
            //auto backup = std::make_unique<aux::Backup>(reader->FirstChildElement()->IntText());
            //meas_uniq_ptr->add_measure_object(std::move(backup));
        }
    }
    
    return std::move(meas_uniq_ptr);
}

std::unique_ptr<Note>
MusicTree::ExtractMusicFunctor::extract_note(tx2::XMLElement* note_elem_ptr) {
    using tx2::find_element;
    
    unsigned int duration = 16;
    if (tx2::exists(note_elem_ptr, "type")) {
        auto note_value = tx2::text(find_element(note_elem_ptr, "type"));
        duration = this->duration_dispatcher.at(note_value)();
        
    } else if (!tx2::exists(note_elem_ptr, "grace")) {
        auto mxl_dur = tx2::int_text(find_element(note_elem_ptr, "duration"));
        duration = std::round(tree_ptr->measure_duration / mxl_dur);
        
    } else {}
    
    short int dotted = 0;
    for (auto i = note_elem_ptr->FirstChildElement("dot");
         i != nullptr;
         i = i->NextSiblingElement("dot")) {
        dotted += 1;
    }
    
    Note::Pitch pitch = Note::Pitch('r', 0, 0);
    if (tx2::exists(note_elem_ptr, "pitch")) {
        auto pitch_elem_ptr = note_elem_ptr->FirstChildElement("pitch");
        
        char pitch_class = tolower(pitch_elem_ptr->FirstChildElement("step")->GetText()[0]);
        short pitch_octave = pitch_elem_ptr->FirstChildElement("octave")->IntText();
        
        int pitch_alteration = 0;
        if (note_elem_ptr->FirstChildElement("alter") != nullptr) {
            pitch_alteration =  note_elem_ptr->FirstChildElement("alter")->IntText();
        }
        
        pitch = Note::Pitch(pitch_class, pitch_octave, pitch_alteration);
    }
    
    auto note_uniq_ptr = std::make_unique<Note>(pitch, duration, dotted);
    
    // handle articulation, ornaments, etc.
    
    // handle grace note
    if (tx2::exists(note_elem_ptr, "grace")) {
        auto grace_before = tx2::exists(note_elem_ptr->PreviousSiblingElement(), "grace");
        auto grace_after = tx2::exists(note_elem_ptr->NextSiblingElement(), "grace");
        auto function = [&](StartStopType type){
            auto grace_elem = tx2::find_element(note_elem_ptr, "grace");
            bool is_slashed = false;
            if (tx2::attribute_value(grace_elem, "slash") == "yes") {
                is_slashed = true;
            }
            auto i = std::make_unique<aux::GraceNote>(type, is_slashed);
            note_uniq_ptr->add_attribute(std::move(i));
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
    if (tx2::exists(note_elem_ptr, "notations/tuplet")) {
        StartStopType type = StartStopType::Start;
        if (tx2::attribute_value(tx2::find_element(note_elem_ptr,
                                                   "notations/tuplet"),
                                 "type") == "stop") {
            type = StartStopType::Stop;
        }
        unsigned short int actual_notes =
        tx2::int_text(tx2::find_element(note_elem_ptr,
                                        "time-modification/actual-notes"));
        unsigned short int normal_notes =
        tx2::int_text(tx2::find_element(note_elem_ptr,
                                        "time-modification/normal-notes"));
        note_uniq_ptr->add_attribute(std::make_unique<aux::Tuplet>(type,
                                                                   actual_notes,
                                                                   normal_notes));
    }
    
    // handle chord
    // The start of a chord is usually not indicated as <chord>. Thus,
    // we have to compare against the next element rather than comparing against the previous one.
    if (!tx2::exists(note_elem_ptr, "chord") &&
        tx2::exists(note_elem_ptr->NextSiblingElement(), "chord")) {
        note_uniq_ptr->add_attribute(std::make_unique<aux::Chord>(StartStopType::Start));
    }
    if (tx2::exists(note_elem_ptr, "chord") &&
        !tx2::exists(note_elem_ptr->NextSiblingElement(), "chord")) {
        note_uniq_ptr->add_attribute(std::make_unique<aux::Chord>(StartStopType::Stop));
    }
    
    auto vec = this->extract_notations(note_elem_ptr);
    for (auto& i : vec) {
        note_uniq_ptr->add_notation(std::move(i));
    }
    
    return std::move(note_uniq_ptr);
}
