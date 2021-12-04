//
//  measure.cpp
//  mxl2ly
//
//  Created by Reventar on 04/12/2021.
//

#include "measure.hpp"

#include <algorithm>
#include <exception>

#include "note.hpp"
#include "genexceptions.hpp"

using namespace lly;

// ==> Measures

// for the entire measure class,
// checking is done afterwards.
Measure::Measure(int id_number) : id_number(id_number) {}
Measure::Measure(int id_number, std::vector<lly::Note> notes) : id_number(id_number), notes(notes) {}

void Measure::add_note(lly::Note note) {
    this->count += note.get_duration();
    // add the note
    notes.push_back(note);
}

void Measure::set_partial() {
    partial = true;
}

void Measure::set_newline() {
    newline = true;
}

void Measure::set_actual_time_signature(lly::aux::TimeSignature time_signature) {
    this->actual_time_signature = time_signature;
}

void Measure::add_measure_object(lly::aux::Clef clef) {
    this->written_clef = clef;
}

void Measure::add_measure_object(lly::aux::KeySignature key_signature) {
    this->written_key_signature = key_signature;
}

void Measure::add_measure_object(lly::aux::TimeSignature time_signature) {
    this->written_time_signature = time_signature;
}

void Measure::add_measure_object(lly::aux::Barline barline) {
    switch (barline.quality) {
        case lly::aux::Barline::Quality::RepeatBefore:
            this->left_barline = barline;
            break;
        default:
            this->right_barline = barline;
            break;
    }
}

void Measure::add_measure_object(lly::aux::MeasureTypes variant_meas) {
    // handles clefs
    if (std::holds_alternative<lly::aux::Clef>(variant_meas)) {
        this->add_measure_object(std::get<lly::aux::Clef>(variant_meas));
        
        // this part handles key signatures
    } else if (std::holds_alternative<lly::aux::KeySignature>(variant_meas)) {
        this->add_measure_object(std::get<lly::aux::KeySignature>(variant_meas));
        
        // this part handles time signatures
    } else if (std::holds_alternative<lly::aux::TimeSignature>(variant_meas)) {
        this->add_measure_object(std::get<lly::aux::TimeSignature>(variant_meas));
        
        // this handles barlines
    } else if (std::holds_alternative<lly::aux::Barline>(variant_meas)) {
        this->add_measure_object(std::get<lly::aux::Barline>(variant_meas));
        
        // in other cases, throw an exception
    } else {
        throw exp::TypeException("a variant conaining either a Clef, KeySignature, Timesignature, or Barline",
                                 typeid(variant_meas).name());
    }
}

bool Measure::confirm() {
    // throw an exception if something goes wrong
    if (!this->actual_time_signature) {
        throw exp::MissingException("time signature in measure " + std::to_string(id_number));
    }
    double ostensible_count = actual_time_signature.value().upper /
    actual_time_signature.value().lower;
    if (this->count == ostensible_count) {
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const lly::Measure& meas) {
    os << "MEASURE:\nId-number: " << meas.id_number << ";\n";
    // Add more here later
    os << "NOTES ENCLOSED IN THIS MEASURE:\n";
    for (auto i : meas.notes) {
        os << i;
    }
    return os;
}

