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
    
    for (auto reader = meas_elem_ptr->FirstChildElement();
         reader != nullptr;
         reader = meas_elem_ptr->FirstChildElement()) {
        
        std::string_view reader_name = reader->Name();
        
        // note: add grace note functionality later.
        if (reader_name == "note" && reader->FirstChildElement("grace") != nullptr) {
            meas_elem_ptr->DeleteChild(reader);
            continue;
        }
        else if (reader_name == "note" &&
                 tx2::find_element(reader, "notations/tuplet") != nullptr) {
            std::vector<tx2::XMLElement*> tuplet_notes;
            
            tuplet_notes.push_back(reader);
            
            auto next_note = reader;
            do {
                next_note = next_note->NextSiblingElement();
                tuplet_notes.push_back(next_note);
                // while we're not at the end of the tuplet
            } while (tx2::find_element(next_note, "notations/tuplet") == nullptr);
            
            meas_uniq_ptr->add_measure_object(extract_tuplet(tuplet_notes));
            
            for (auto i : tuplet_notes) {
                meas_elem_ptr->DeleteChild(i);
            }
            
            continue;
        }
        else if (reader_name == "note") {
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
        
        meas_elem_ptr->DeleteChild(reader);
    }
    
    return std::move(meas_uniq_ptr);
}

std::unique_ptr<aux::Tuplet>
MusicTree::ExtractMusicFunctor::extract_tuplet(std::vector<tx2::XMLElement*> tuplet_elems) {
    auto act_notes = tx2::int_text(tx2::find_element(tuplet_elems.at(0),
                                                     "time-modification/actual-notes"));
    auto nor_notes = tx2::int_text(tx2::find_element(tuplet_elems.at(0),
                                                     "time-modification/normal-notes"));
    auto tuplet_uniq_ptr = std::make_unique<aux::Tuplet>(act_notes, nor_notes);
    
    for (auto reader : tuplet_elems) {
        std::string_view reader_name = reader->Name();
        
        // note: add grace note functionality later.
        if (reader_name == "note" && reader->FirstChildElement("grace") != nullptr) {
            // add another time
            continue;
        }
        else if (reader_name == "note") {
            auto note = extract_note(reader);
            tuplet_uniq_ptr->add_measure_object(std::move(note));
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
    
    return std::move(tuplet_uniq_ptr);
}

std::unique_ptr<Note>
MusicTree::ExtractMusicFunctor::extract_note(tx2::XMLElement* note_elem_ptr) {
    unsigned int duration = note_elem_ptr->FirstChildElement("duration")->IntText();
    
    bool in_chord = note_elem_ptr->FirstChildElement("chord") != nullptr;
    
    short int dotted = 0;
    if (note_elem_ptr->FirstChildElement("dotted") != nullptr) {
        dotted = note_elem_ptr->FirstChildElement("dotted")->IntText();
    }
    
    Note::Pitch pitch = Note::Pitch('r', 0, 0);
    if (note_elem_ptr->FirstChildElement("pitch") != nullptr) {
        auto pitch_elem_ptr = note_elem_ptr->FirstChildElement("pitch");
        
        char pitch_class = tolower(pitch_elem_ptr->FirstChildElement("step")->GetText()[0]);
        short pitch_octave = pitch_elem_ptr->FirstChildElement("octave")->IntText();
        
        int pitch_alteration = 0;
        if (note_elem_ptr->FirstChildElement("alter") != nullptr) {
            pitch_alteration =  note_elem_ptr->FirstChildElement("alter")->IntText();
        }
        
        pitch = Note::Pitch(pitch_class, pitch_octave, pitch_alteration);
    }
    
    auto note_uniq_ptr = std::make_unique<Note>(pitch, duration, dotted, in_chord);
    
    // handle articulation, ornaments, etc.
    
    return std::move(note_uniq_ptr);
}
