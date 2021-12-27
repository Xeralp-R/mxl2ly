//
//  note.hpp
//  mxl2ly
//
//  Created by Reventar on 17/11/2021.
//

#ifndef note_hpp
#define note_hpp

#include <exception>
#include <optional>
#include <ostream>
#include <string>
#include <variant>
#include <vector>

#include "measure_objects.hpp"
#include "notations.hpp"
#include "note_attributes.hpp"

namespace lmt {
class Note : public aux::AbstractMeasureObject {
  public:
    class Pitch {
      public:
        Pitch(char pitch_class, short int octave, short int alteration);

        friend class Note;

      private:
        short int alteration;
        char      pitch_class;
        short int octave;

        std::vector<char>      valid_pitch_classes{'a', 'b', 'c', 'd', 'e',
                                              'f', 'g', 'r', 's'};
        std::vector<short int> valid_octaves{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::vector<short int> valid_alterations{-2, -1, 0, 1, 2};
    };
    struct Rest {};

    Note(Pitch pitch, unsigned int duration, short int dotted = 0);
    Note(Rest rest, unsigned int duration, short int dotted = 0);

    void add_notation(std::unique_ptr<aux::AbstractNotation> notation);
    void add_attribute(std::unique_ptr<aux::AbstractNoteAttribute> attribute);

    std::string  get_subtype() override { return "note"; }
    short int    alteration() const { return pitch.alteration; }
    char         pitch_class() const { return pitch.pitch_class; }
    short int    octave() const { return pitch.octave; }
    short int    dots() const { return this->dotted; }
    unsigned int duration() const { return mxl_dur; }
    
    std::optional<aux::Chord> get_chord();
    std::optional<aux::GraceNote> get_grace_note();
    std::optional<aux::Tuplet> get_tuplet();
  private:
    // ==> Required Variables
    Pitch        pitch;
    unsigned int mxl_dur = 0; // duration of musicxml, not lilypond

    // ==> Non-required Variables
    std::vector<std::unique_ptr<lmt::aux::AbstractNotation>> notations;
    std::vector<std::unique_ptr<lmt::aux::AbstractNoteAttribute>> attributes;
    short int dotted   = 0; // number of dots
};
} // namespace lmt

#endif /* note_hpp */
