//
//  note.hpp
//  mxl2ly
//
//  Created by Reventar on 17/11/2021.
//

#ifndef note_hpp
#define note_hpp

#include <array>
#include <exception>
#include <optional>
#include <ostream>
#include <string>
#include <unordered_map>
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

    Note(Pitch pitch, unsigned int lly_dur, short int dotted = 0);
    Note(Rest rest, unsigned int lly_dur, short int dotted = 0);

    void add_notation(std::unique_ptr<aux::AbstractNotation> notation);
    void add_attribute(std::unique_ptr<aux::AbstractNoteAttribute> attribute);

    std::string  get_subtype() override { return "note"; }
    short int    alteration() const { return pitch.alteration; }
    char         pitch_class() const { return pitch.pitch_class; }
    short int    octave() const { return pitch.octave; }
    short int    dots() const { return this->dotted; }
    unsigned int duration() const { return lly_dur; }

    std::optional<aux::GraceNote> get_grace_note() const;
    std::optional<aux::Chord>     get_chord() const;
    std::optional<aux::Tuplet>    get_tuplet() const;
  private:
    // ==> Required Variables
    Pitch        pitch;
    unsigned int lly_dur = 0; // duration of lilypond, not musicxml

    // ==> Non-required Variables
    std::vector<std::unique_ptr<lmt::aux::AbstractNotation>>        notations;
    std::array<std::unique_ptr<lmt::aux::AbstractNoteAttribute>, 3> attributes;
    short int dotted = 0; // number of dots
    
    // ==> Helper functions
    const std::unordered_map<std::string, std::function<int(void)>>
    attribute_dispatcher {
        {"grace_note", [](){return 0;}},
        {"chord",      [](){return 1;}},
        {"tuplet",     [](){return 2;}}
    };
};
} // namespace lmt

#endif /* note_hpp */
