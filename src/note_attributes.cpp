//
//  note_attributes.cpp
//  mxl2ly
//
//  Created by Reventar on 16/01/2022.
//

#include "note_attributes.hpp"

#include "fmt/format.h"

using namespace lmt::aux;

std::pair<std::string, std::string> GraceNote::return_lilypond() const {
    switch (this->start_stop) {
    case StartStopType::Start:
        return is_slashed ? std::pair(R"__(\slashedGrace { )__", "")
                          : std::pair(R"__(\grace { )__", "");
    case StartStopType::Stop:
        return std::pair("", R"__(} )__");
    case StartStopType::Both:
        return is_slashed ? std::pair(R"__(\slashedGrace { )__", "} ")
                          : std::pair(R"__(\grace { )__", "} ");
        // throw std::logic_error("impossible");
    }
}

std::pair<std::string, std::string> Chord::return_lilypond() const {
    switch (this->start_stop) {
    case StartStopType::Start:
        return std::pair(R"__(< )__", "");
    case StartStopType::Stop:
        return std::pair("", R"__(> )__");
    case StartStopType::Both:
        // unreached
        return {};
    }
}

std::pair<std::string, std::string> Tuplet::return_lilypond() const {
    switch (this->start_stop) {
    case StartStopType::Start:
        return std::pair(fmt::format(R"--(\tuplet {0}/{1} {2} )--",
                                     this->actual_notes, this->normal_notes,
                                     "{"),
                         "");
    case StartStopType::Stop:
        return std::pair("", "} ");
    case StartStopType::Both:
        // unreached
        return {};
    }
}
