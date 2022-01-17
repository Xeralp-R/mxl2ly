//
//  note_attributes.hpp
//  mxl2ly
//
//  Created by Reventar on 27/12/2021.
//

#ifndef note_attributes_hpp
#define note_attributes_hpp

#include <exception>
#include <iostream>
#include <optional>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "helper.hpp"
#include "statement.hpp"
#include "tinyxml2/tinyxml2.h"

namespace lmt::aux {
struct AbstractNoteAttribute : public AbstractStatement {
    std::string         get_type() override { return "note_attribute"; }
    virtual std::string get_subtype() const                             = 0;
    virtual std::pair<std::string, std::string> return_lilypond() const = 0;
    virtual ~AbstractNoteAttribute(){};
};

struct GraceNote : public AbstractNoteAttribute {
    GraceNote(StartStopType start_stop, bool is_slashed)
        : start_stop(start_stop), is_slashed(is_slashed){};

    std::string get_subtype() const override { return "grace_note"; }
    std::pair<std::string, std::string> return_lilypond() const override;

    StartStopType start_stop;
    bool          is_slashed;
};

struct Chord : public AbstractNoteAttribute {
    Chord(StartStopType start_stop) : start_stop(start_stop){};

    std::string get_subtype() const override { return "chord"; }
    std::pair<std::string, std::string> return_lilypond() const override;

    StartStopType start_stop;
};

struct Tuplet : public AbstractNoteAttribute {
    Tuplet(StartStopType start_stop, unsigned short int actual_notes,
           unsigned short int normal_notes)
        : start_stop(start_stop), actual_notes(actual_notes),
          normal_notes(normal_notes){};

    std::string get_subtype() const override { return "tuplet"; }
    std::pair<std::string, std::string> return_lilypond() const override;

    StartStopType      start_stop;
    unsigned short int actual_notes;
    unsigned short int normal_notes;
};
} // namespace lmt::aux

#endif /* note_attributes_hpp */
