//
//  directions.hpp
//  mxl2ly
//
//  Created by Reventar on 04/12/2021.
//

#ifndef directions_hpp
#define directions_hpp

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "helper.hpp"
#include "notations.hpp"
#include "statement.hpp"
#include "tinyxml2/tinyxml2.h"

namespace lmt::aux {
struct AbstractDirection : public AbstractNoteObject {
    std::string get_subtype() const override { return "note_direction"; }

    virtual std::string get_subsubtype() const           = 0;
    virtual std::string return_lilypond() const override = 0;
    virtual ~AbstractDirection(){};
};

struct DirectionFactory {
    std::vector<std::unique_ptr<AbstractDirection>>
    operator()(const tinyxml2::XMLElement* direction_ptr) const;
};

struct Wedge : AbstractDirection {
    enum class Type { Crescendo, Decrescendo } type;
    StartStopType start_stop;

    Wedge(Type type, StartStopType start_stop)
        : type(type), start_stop(start_stop){};
    Wedge(const tinyxml2::XMLElement* wedge_ptr);

    std::string get_subsubtype() const override { return "wedge"; }
    std::string return_lilypond() const override;
};

struct Words : AbstractDirection {
    enum class Formatting { None, Italics, Bold, BoldItalics } formatting;
    std::string content;

    Words(std::string content)
        : content(content), formatting(Formatting::None){};
    Words(std::string content, Formatting formatting)
        : content(content), formatting(formatting) {}
    Words(const tinyxml2::XMLElement* words_ptr);

    std::string get_subsubtype() const override { return "words"; }
    std::string return_lilypond() const override;
};

struct DirectionDynamic : public AbstractDirection {
    Dynamic actual;

    DirectionDynamic(std::string type) : actual(type){};
    DirectionDynamic(const tinyxml2::XMLElement* dyn_ptr) : actual(dyn_ptr){};

    std::string get_subsubtype() const override { return "direction_dynamic"; }
    std::string return_lilypond() const override {
        return actual.return_lilypond();
    }
};
} // namespace lmt::aux

#endif /* directions_hpp */
