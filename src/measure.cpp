//
//  measure.cpp
//  mxl2ly
//
//  Created by Reventar on 04/12/2021.
//

#include "measure.hpp"
#include "music_tree.hpp"

#include <algorithm>
#include <exception>
#include <iterator>

#include "chord.hpp"
#include "fmt/format.h"
#include "tinyxml2/tixml2ex.h"

using namespace lmt;
namespace tx2 = tinyxml2;

Measure::Measure(int id_number) : id_number(id_number) {}

auto converter =
    [](tx2::XMLElement* meas_elem) -> std::vector<tinyxml2::XMLElement*> {
    std::vector<tinyxml2::XMLElement*> returner;
    for (auto i : meas_elem) {
        returner.push_back(i);
    }
    return returner;
};

Measure::Measure(tinyxml2::XMLElement* meas_elem, const MusicTree* tree_ptr)
    : Measure(converter(meas_elem), meas_elem->IntAttribute("number"),
              tree_ptr) {}

Measure::Measure(std::vector<tinyxml2::XMLElement*> elem_vec, int id_number,
                 const MusicTree* tree_ptr)
    : id_number(id_number) {
    using namespace std::string_literals;
    mxl_full_duration = tree_ptr->get_measure_duration();

    // initialize the first line
    this->lines.push_back(std::make_unique<MusicLine>());
    std::vector<std::unique_ptr<lmt::aux::AbstractDirection>> holder;

    // get notes and chords
    for (auto iter = elem_vec.begin(); iter != elem_vec.end(); ++iter) {
        auto reader = *iter;

        const auto reader_name = reader->Name();

        // Handle backups
        if (reader_name == "backup"s) {
            add_measure_object(std::make_unique<aux::Backup>(
                tx2::int_text(reader, "duration")));
            continue;
        }

        // Handle attrbibutes
        if (reader_name == "attributes"s) {
            for (const auto spec_ptr : reader) {
                auto temp = move(measure_attribute_factory(spec_ptr));
                if (temp == nullptr) {
                    continue;
                }
                add_measure_object(move(temp));
            }
            continue;
        }

        // Handle directions
        if (reader_name == "direction"s) {
            for (const auto dir_ptr :
                 tx2::selection(reader, "direction-type")) {
                auto temp = std::move(measure_direction_factory(dir_ptr));
                if (temp.empty()) {
                    continue;
                }
                for (auto& i : temp) {
                    holder.push_back(std::move(i));
                }
            }
        }

        // Handle notes
        if (reader_name != "note"s) {
            continue;
        }
        // move to add_measure later
        this->mxl_count += tx2::exists(reader, "duration")
                               ? tx2::int_text(reader, "duration")
                               : 0;

        auto temp_iter = iter;
        ++temp_iter;
        if (temp_iter != elem_vec.end() && tx2::exists(*temp_iter, "chord")) {
            // it is a chord
            std::vector<tx2::XMLElement*>           chord_vec = {reader};
            tx2::XMLElement*                        chord_reader;
            std::vector<tx2::XMLElement*>::iterator chord_iter;

            for (chord_iter = temp_iter; chord_iter != elem_vec.end() &&
                                         tx2::exists(*chord_iter, "chord");
                 ++chord_iter) {
                chord_vec.push_back(*chord_iter);
                temp_iter = chord_iter;
            }
            auto chord = std::make_unique<Chord>(chord_vec, tree_ptr);
            if (not holder.empty()) {
                for (auto& i : holder) {
                    chord->add_note_object(std::move(i));
                }
                holder.clear();
            }
            add_measure_object(std::move(chord));
            iter = temp_iter;
        } else {
            // It is a note
            auto note = std::make_unique<Note>(reader, tree_ptr);
            if (not holder.empty()) {
                for (auto& i : holder) {
                    note->add_note_object(std::move(i));
                }
                holder.clear();
            }
            add_measure_object(std::move(note));
        }
    }
}

void Measure::add_measure_object(
    std::unique_ptr<lmt::aux::AbstractMeasureObject> abstract_ptr) {
    if (abstract_ptr->get_subtype() == "backup") {
        current_line += 1;
        this->lines.push_back(std::make_unique<MusicLine>());

        mxl_count =
            mxl_count - dynamic_cast<aux::Backup*>(abstract_ptr.get())->mxl_dur;
        if (mxl_count != 0) {
            // TODO: accomodate dotted backups
            this->lines.at(current_line)
                ->objects.push_back(std::make_unique<Note>(
                    Note::Pitch('s'), mxl_full_duration / mxl_count));
        }
    };

    this->lines.at(current_line)->objects.push_back(std::move(abstract_ptr));
}

std::vector<std::string> Measure::return_lilypond() const {
    std::vector<std::string> measure_content;

    for (const auto& line : lines) {
        std::string line_text;

        for (const auto& obj_ptr : line->objects) {
            line_text += obj_ptr->return_lilypond();
        }

        measure_content.push_back(line_text);
    }

    return measure_content;
}
