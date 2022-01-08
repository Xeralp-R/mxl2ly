//
//  notations.cpp
//  mxl2ly
//
//  Created by Reventar on 08/01/2022.
//

#include "notations.hpp"

#include "fmt/format.h"

using namespace lmt::aux;

std::string Dynamic::return_lilypond() const {
    return fmt::format(R"--(\{0})--", this->var_type);
}

std::string Articulation::return_lilypond() const {
    switch (this->type) {
        case Articulation::Type::Accent:
            return R"--(->)--";
        case Articulation::Type::Espressivo:
            return R"--(\espressivo)--";
        case Articulation::Type::Tenuto:
            return R"--(--)--";
        case Articulation::Type::Marcato:
            return R"--(-^)--";
        case Articulation::Type::Staccato:
            return R"--(-.)--";
        case Articulation::Type::Staccatissimo:
            return R"--(-!)--";
    }
    // unreached.
}

std::string Ornament::return_lilypond() const {
    switch (this->type) {
        case Ornament::Type::Trill:
            return R"__(\trill)__";
            break;
        case Ornament::Type::Tremolo:
            return R"__(\tremolo)__";
        case Ornament::Type::Turn:
            return R"__(\turn)__";
        case Ornament::Type::InvertedTurn:
            return R"__(\reverseturn)__";
        case Ornament::Type::Mordent:
            return R"__(\prall)__";
        case Ornament::Type::InvertedMordent:
            return R"__(\mordent)__";
    }
}

std::string Slur::return_lilypond() const {
    switch (this->start_stop) {
        case StartStopType::Start:
            return R"__(()__";
        case StartStopType::Stop:
            return R"__())__";
        case StartStopType::Both:
        default:
            // unreached
            return "";
            break;
    }
}
