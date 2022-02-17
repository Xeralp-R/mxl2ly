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

    // get all the attributes
    /*
    std::vector<tx2::XMLElement*> attr_vec;
    std::copy_if(
        elem_vec.begin(), elem_vec.end(), std::back_inserter(attr_vec),
        [](tinyxml2::XMLElement* x) { return x->Name() == "attributes"s; });
    for (const auto spec_ptr : attr_vec) {
        auto temp = move(measure_attribute_factory(spec_ptr));
        if (temp == nullptr) {
            continue;
        }
        objects.push_back(move(temp));
    }*/

    // get notes and chords
    for (auto iter = elem_vec.begin(); iter != elem_vec.end(); ++iter) {
        auto reader = *iter;

        const auto reader_name = reader->Name();
        if (reader_name != "note"s && reader_name != "attributes"s) {
            continue;
        }

        // Handle attrbibutes
        if (reader_name == "attributes"s) {
            for (const auto spec_ptr : reader) {
                auto temp = move(measure_attribute_factory(spec_ptr));
                if (temp == nullptr) {
                    continue;
                }
                objects.push_back(move(temp));
            }
            continue;
        }

        // Handle notes
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
