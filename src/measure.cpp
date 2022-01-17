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

#include "chord.hpp"
#include "fmt/format.h"

using namespace lmt;
namespace tx2 = tinyxml2;

Measure::Measure(int id_number) : id_number(id_number) {}

Measure::Measure(tinyxml2::XMLElement* meas_elem, const MusicTree* tree_ptr) {
    // get the element number
    id_number = meas_elem->IntAttribute("number");

    // get all the attributes
    if (tx2::exists(meas_elem, "attributes")) {
        for (const auto spec_ptr : tx2::find_element(meas_elem, "attributes")) {
            auto temp = move(measure_attribute_factory(spec_ptr));
            if (temp == nullptr) {
                continue;
            }
            objects.push_back(move(temp));
        }
    }

    // get notes and chords
    for (auto reader = meas_elem->FirstChildElement(); reader != nullptr;
         reader      = reader->NextSiblingElement()) {

        std::string_view reader_name = reader->Name();
        if (reader_name != "note") {
            continue;
        }

        if (tx2::exists(reader->NextSiblingElement(), "chord")) {
            std::vector<tx2::XMLElement*> chord_vec = {reader};
            tx2::XMLElement*              chord_reader;
            for (chord_reader = reader->NextSiblingElement();
                 tx2::exists(chord_reader, "chord");
                 chord_reader = chord_reader->NextSiblingElement()) {
                chord_vec.push_back(chord_reader);
                reader = chord_reader;
            }
            add_measure_object(std::make_unique<Chord>(chord_vec, tree_ptr));
        } else {
            // auto note = extract_note(reader);
            auto note = std::make_unique<Note>(reader, tree_ptr);
            add_measure_object(std::move(note));
        }
    }
}

std::string Measure::return_lilypond() const {
    std::string measure_text;
    for (const auto& obj_ptr : objects) {
        measure_text += obj_ptr->return_lilypond();
    }

    measure_text += " |\n";
    if ((id_number % 5) == 0) {
        measure_text += fmt::format("% {0}{1}", id_number, '\n');
    }
    return measure_text;
}

void Measure::add_measure_object(
    std::unique_ptr<lmt::aux::AbstractMeasureObject> abstract_ptr) {
    if (abstract_ptr->get_subtype() == "backup") {
        this->number_of_voices += 1;
    };

    this->objects.push_back(std::move(abstract_ptr));
}
