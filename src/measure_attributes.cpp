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

using namespace lmt::aux;

std::string Clef::return_lilypond() const {
    switch (this->type) {
        case 'g':
            if (this->staff_line == 1) {
                return R"--(\clef french)--";
            }
            return R"--(\clef treble)--";
        case 'f':
            if (this->staff_line == 5) {
                return R"--(\clef subbass)--";
            }
            if (this->staff_line == 3) {
                return R"--(\clef varbaritone)--";
            }
            return R"--(\clef bass)--";
        case 'c':
            if (this->staff_line == 1) {
                return R"--(\clef soprano)--";
            }
            if (this->staff_line == 2) {
                return R"--(\clef mezzosoprano)--";
            }
            if (this->staff_line == 3) {
                return R"--(\clef alto)--";
            }
            if (this->staff_line == 4) {
                return R"--(\clef tenor)--";
            }
            if (this->staff_line == 5) {
                return R"--(\clef baritone)--";
            }
            return R"--()--";
        default:
            // should be unreachable
            return R"--()--";
            break;
    }
}

std::string KeySignature::return_lilypond() const {
    // allow for other modes next time
    return fmt::format(R"--(\key {0} \{1})--",
                       this->converter.at(fifths),
                       mode);
}

std::string TimeSignature::return_lilypond() const {
    return fmt::format(R"--(\time {0}/{1})--",
                       this->upper_num, this->lower_num);
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
    
    return fmt::format(R"--(\bar "{0}")--",
                       returner);
}
