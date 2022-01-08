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

/* Add later
 enum class Location {
 Above,
 Below
 };
 */

namespace lmt::aux {
struct AbstractNotation : public AbstractStatement {
    std::string         get_type() { return "note_statement"; }
    
    virtual std::string get_subtype() const          = 0;
    //virtual void        accept_musicxml(std::string) = 0;
    virtual std::string return_lilypond() const      = 0;
    
    virtual ~AbstractNotation(){};
};

class Dynamic : public AbstractNotation {
  public:
    Dynamic(std::string type) {
        if (!is_element(permitted_types.begin(), permitted_types.end(), type)) {
            throw std::logic_error("Incorrect dynamic");
        }

        this->var_type = type;
    }

    std::string get_subtype() const override { return "dynamic"; }
    std::string return_lilypond() const override;
    
    std::string type() const { return var_type; };

  private:
    std::string var_type;

    const std::vector<std::string> permitted_types{
        "pppppppp", "ppppppp", "pppppp", "ppppp",  "pppp",    "ppp",
        "pp",       "p",       "mp",     "mf",     "f",       "ff",
        "fff",      "ffff",    "fffff",  "ffffff", "fffffff", "ffffffff",
        "sf",       "sfz",     "rf",     "sffz"};
};

struct Articulation : public AbstractNotation {
    enum class Type {
        Staccato,      // like a dot
        Staccatissimo, // a wedge
        Tenuto,        // a line
        Espressivo,    // cresc/decresc on one note
        Accent,        // a < sign
        Marcato        // a hat?
    } type;

    Articulation(Articulation::Type type) : type(type) {}

    std::string get_subtype() const override { return "articulation"; }
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

    Ornament(Ornament::Type type) : type(type) {}

    std::string get_subtype() const override { return "ornament"; }
    std::string return_lilypond() const override;
};

struct Slur : public AbstractNotation {
    Slur(StartStopType start_stop) : start_stop(start_stop) {}
    StartStopType start_stop;

    std::string get_subtype() const override { return "slur"; }
    std::string return_lilypond() const override;
};
} // namespace lmt::aux

#endif /* notations_hpp */
