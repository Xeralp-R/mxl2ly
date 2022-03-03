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

    // get notes and chords
    for (auto iter = elem_vec.begin(); iter != elem_vec.end(); ++iter) {
        auto reader = *iter;

        const auto reader_name = reader->Name();
        if (reader_name != "note"s && reader_name != "attributes"s &&
            reader_name != "backup"s) {
            continue;
        }

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

        // Handle notes
        // move to add_measure later
        this->mxl_count += tx2::exists(reader, "duration")
                               ? tx2::int_text(reader, "duration")
                               : 0;

        auto temp_iter = iter;
        ++temp_iter;
        if (temp_iter != elem_vec.end() && tx2::exists(*temp_iter, "chord")) {
            std::vector<tx2::XMLElement*>           chord_vec = {reader};
            tx2::XMLElement*                        chord_reader;
            std::vector<tx2::XMLElement*>::iterator chord_iter;

            for (chord_iter = temp_iter; chord_iter != elem_vec.end() &&
                                         tx2::exists(*chord_iter, "chord");
                 ++chord_iter) {
                chord_vec.push_back(*chord_iter);
                temp_iter = chord_iter;
            }
            add_measure_object(std::make_unique<Chord>(chord_vec, tree_ptr));
            iter = temp_iter;
        } else {
            // auto note = extract_note(reader);
            // auto note = std::make_unique<Note>(reader, tree_ptr);
            add_measure_object(std::make_unique<Note>(reader, tree_ptr));
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
