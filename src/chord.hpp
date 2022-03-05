//
//  chord.hpp
//  mxl2ly
//
//  Created by Reventar on 16/01/2022.
//

#ifndef chord_hpp
#define chord_hpp

#include <array>
#include <exception>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "measure_objects.hpp"
#include "notations.hpp"
#include "note.hpp"
#include "note_attributes.hpp"

#include "tinyxml2/tixml2ex.h"

namespace lmt {
class MusicTree;

class Chord : public aux::AbstractMeasureObject {
  public:
    Chord(std::vector<tinyxml2::XMLElement*> elements,
          const MusicTree*                   tree_ptr);

    std::string get_subtype() const override { return "chord"; }
    std::string return_lilypond() const override;

    void add_note_object(std::unique_ptr<aux::AbstractNoteObject> note_object);

  private:
    std::vector<Note::Pitch> pitches;
    unsigned int             lly_dur;
    short int                dotted; // number of dots

    std::vector<std::unique_ptr<lmt::aux::AbstractNoteObject>> note_objects;
    std::array<std::unique_ptr<lmt::aux::AbstractNoteAttribute>, 2> attributes;

    const std::unordered_map<std::string, std::function<unsigned(void)>>
        duration_dispatcher{
            {"1024th", []() { return 1024; }}, {"512th", []() { return 512; }},
            {"256th", []() { return 256; }},   {"128th", []() { return 128; }},
            {"64th", []() { return 64; }},     {"32nd", []() { return 32; }},
            {"16th", []() { return 16; }},     {"eighth", []() { return 8; }},
            {"quarter", []() { return 4; }},   {"half", []() { return 2; }},
            {"whole", []() { return 1; }}};
    aux::NotationFactory notation_factory;
};
} // namespace lmt

#endif /* chord_hpp */
