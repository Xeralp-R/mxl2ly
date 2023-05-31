//
//  measure_attributes.cpp
//  mxl2ly
//
//  Created by Reventar on 08/01/2022.
//

#include "measure_attributes.hpp"

#include <exception>
#include <string>
#include <vector>

#include "fmt/format.h"
#include "tinyxml2/tixml2ex.h"

using namespace lmt::aux;
namespace tx2 = tinyxml2;

std::unique_ptr<AbstractMeasureAttribute> MeasureAttributeFactory::operator()(
    const tinyxml2::XMLElement* attr_ptr) const {
    std::string switcher = attr_ptr->Name();
    if (switcher == "clef") {
        return std::make_unique<Clef>(attr_ptr);
    }
    if (switcher == "key") {
        return std::make_unique<KeySignature>(attr_ptr);
    }
    if (switcher == "time") {
        return std::make_unique<TimeSignature>(attr_ptr);
    }
    return nullptr;
}

Clef::Clef(char type, short int staff_line)
    : type(type), staff_line(staff_line) {
    if (type != 'c' && type != 'f' && type != 'g') {
        throw std::logic_error("Incorrect clef");
    }
    if (staff_line > 5) {
        throw std::logic_error("Incorrect clef position");
    }
}

Clef::Clef(const tinyxml2::XMLElement* clef_ptr)
    : type(std::tolower(tx2::text(clef_ptr, "sign").at(0))),
      staff_line(tx2::int_text(clef_ptr, "line")) {
    if (this->type != 'c' && type != 'f' && type != 'g' && type != 'p') {
        throw std::logic_error("Incorrect clef");
    }
    if (this->staff_line > 5) {
        throw std::logic_error("Incorrect clef position");
    }
}

std::string Clef::return_lilypond() const {
    using namespace std::string_literals;
    switch (this->type) {
    case 'g':
        if (this->staff_line == 1) {
            return R"--(\clef french)--" + "\n"s;
        }
        return R"--(\clef treble)--" + "\n"s;
    case 'f':
        if (this->staff_line == 5) {
            return R"--(\clef subbass)--" + "\n"s;
        }
        if (this->staff_line == 3) {
            return R"--(\clef varbaritone)--" + "\n"s;
        }
        return R"--(\clef bass)--" + "\n"s;
    case 'c':
        if (this->staff_line == 1) {
            return R"--(\clef soprano)--" + "\n"s;
        }
        if (this->staff_line == 2) {
            return R"--(\clef mezzosoprano)--" + "\n"s;
        }
        if (this->staff_line == 3) {
            return R"--(\clef alto)--" + "\n"s;
        }
        if (this->staff_line == 4) {
            return R"--(\clef tenor)--" + "\n"s;
        }
        if (this->staff_line == 5) {
            return R"--(\clef baritone)--" + "\n"s;
        }
        return R"--()--";
    case 'p':
        return R"__(\clef percussion)__";
    default:
        // should be unreachable
        return R"--()--";
        break;
    }
}

KeySignature::KeySignature(int fifths) : fifths(fifths) {
    if (fifths < -7 || fifths > 7) {
        throw std::logic_error("Incorrect clef position");
    }
}

KeySignature::KeySignature(const tinyxml2::XMLElement* attr_ptr)
    : fifths(tx2::int_text(attr_ptr, "fifths")) {
    if (fifths < -7 || fifths > 7) {
        throw std::logic_error("Incorrect clef position");
    }
}

std::string KeySignature::return_lilypond() const {
    // allow for other modes next time
    return fmt::format(R"--(\key {0} \{1}{2})--", this->converter.at(fifths),
                       mode, '\n');
}

TimeSignature::TimeSignature(short int upper, short int lower)
    : upper_num(upper), lower_num(lower){};

TimeSignature::TimeSignature(const tinyxml2::XMLElement* attr_ptr)
    : upper_num(tx2::int_text(attr_ptr, "beats")),
      lower_num(tx2::int_text(attr_ptr, "beat-type")) {}

std::string TimeSignature::return_lilypond() const {
    return fmt::format(R"--(\time {0}/{1}{2})--", this->upper_num,
                       this->lower_num, '\n');
}

std::string Barline::return_lilypond() const {
    std::string returner;
    switch (this->type) {
    case Barline::Type::None:
        break;
    case Barline::Type::Regular:
        returner = R"--(|)--";
        break;
    case Barline::Type::Heavy:
        returner = R"--(.)--";
        break;
    case Barline::Type::LightLight:
        returner = R"--(||)--";
        break;
    case Barline::Type::LightHeavy:
        returner = R"--(|.)--";
        break;
    case Barline::Type::HeavyLight:
        returner = R"--(.|)--";
        break;
    case Barline::Type::HeavyHeavy:
        returner = R"--(..)--";
        break;
    }
    switch (this->repeat) {
    case Repeat::None:
        break;
    case Repeat::RepeatBefore:
        returner = ":" + returner;
        break;
    case Repeat::RepeatAfter:
        returner += ":";
        break;
    }

    return fmt::format(R"--(\bar "{0}"{1})--", returner, '\n');
}
