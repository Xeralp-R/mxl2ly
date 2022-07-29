//
//  notations.hpp
//  mxl2ly
//
//  Created by Reventar on 17/11/2021.
//

#ifndef notations_hpp
#define notations_hpp

#include <exception>
#include <iostream>
#include <optional>
#include <ostream>
#include <string>
#include <variant>
#include <vector>

#include "helper.hpp"
#include "statement.hpp"
#include "tinyxml2/tinyxml2.h"

namespace lmt::aux {
struct AbstractNoteObject : public AbstractStatement {
    std::string get_type() override { return "note_object"; }

    virtual std::string get_subtype() const     = 0;
    virtual std::string return_lilypond() const = 0;
    virtual ~AbstractNoteObject(){};
};

struct AbstractNotation : public AbstractNoteObject {
    std::string get_subtype() const override { return "note_statement"; }

    virtual std::string get_subsubtype() const           = 0;
    virtual std::string return_lilypond() const override = 0;
    virtual ~AbstractNotation(){};
};

struct NotationFactory {
    std::vector<std::unique_ptr<AbstractNotation>>
    operator()(const tinyxml2::XMLElement* attr_ptr) const;
};

class Dynamic : public AbstractNotation {
  public:
    Dynamic(std::string type);
    Dynamic(const tinyxml2::XMLElement* dyn_ptr);

    std::string get_subsubtype() const override { return "dynamic"; }
    std::string return_lilypond() const override;

  private:
    std::string type;

    const std::vector<std::string> permitted_types{
        "pppppppp", "ppppppp", "pppppp", "ppppp",  "pppp",    "ppp",
        "pp",       "p",       "mp",     "mf",     "f",       "ff",
        "fff",      "ffff",    "fffff",  "ffffff", "fffffff", "ffffffff",
        "sf",       "sfz",     "rf",     "sffz",   "fz"};
};

struct Articulation : public AbstractNotation {
    enum class Type {
        Staccato,      // like a dot
        Staccatissimo, // a wedge
        Tenuto,        // a line
        Espressivo,    // cresc/decresc on one note
        Accent,        // a < sign
        Marcato,       // a hat?
        DetachedLegato // a mix of stacato and tenuto: only for musicxml
    } type;

    Articulation(Articulation::Type type);
    Articulation(const tinyxml2::XMLElement* art_ptr);

    std::string get_subsubtype() const override { return "articulation"; }
    std::string return_lilypond() const override;
};

struct Ornament : public AbstractNotation {
    enum class Type {
        Turn,
        InvertedTurn,
        Trill,
        Tremolo,
        Mordent,
        InvertedMordent
    } type;

    Ornament(Ornament::Type type);
    Ornament(const tinyxml2::XMLElement* ornament_ptr);

    std::string get_subsubtype() const override { return "ornament"; }
    std::string return_lilypond() const override;
};

struct Slur : public AbstractNotation {
    Slur(StartStopType start_stop);
    Slur(const tinyxml2::XMLElement* slur_ptr);

    std::string get_subsubtype() const override { return "slur"; }
    std::string return_lilypond() const override;

    StartStopType start_stop;
};
} // namespace lmt::aux

#endif /* notations_hpp */
