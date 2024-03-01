//
//  directions.cpp
//  mxl2ly
//
//  Created by Reventar on 05/03/2022.
//

#include "directions.hpp"

#include "fmt/format.h"
#include "tinyxml2/tixml2ex.h"

namespace tx2 = tinyxml2;
using namespace lmt::aux;

std::vector<std::unique_ptr<AbstractDirection>> DirectionFactory::operator()(
    const tinyxml2::XMLElement* direct_type_ptr) const {
    std::vector<std::unique_ptr<AbstractDirection>> returner;

    for (auto true_elem : direct_type_ptr) {
        std::string elem_name = true_elem->Name();

        if (elem_name == "dynamics") {
            returner.push_back(std::make_unique<DirectionDynamic>(true_elem));
            continue;
        }
        if (elem_name == "wedge") {
            returner.push_back(std::make_unique<Wedge>(true_elem));
            continue;
        }
        if (elem_name == "words") {
            returner.push_back(std::make_unique<Words>(true_elem));
            continue;
        }
        if (elem_name == "rehearsal") {
            returner.push_back(std::make_unique<RehearsalMark>(true_elem));
        }
    }

    return returner;
}

Wedge::Wedge(const tinyxml2::XMLElement* wedge_ptr) {
    std::string wedge_type = tx2::attribute_value(wedge_ptr, "type");

    if (wedge_type == "crescendo") {
        this->type       = Type::Crescendo;
        this->start_stop = StartStopType::Start;
    } else if (wedge_type == "diminuendo") {
        this->type       = Type::Decrescendo;
        this->start_stop = StartStopType::Start;
    } else if (wedge_type == "stop") {
        this->start_stop = StartStopType::Stop;
        // no value assigned to type.
    } else {
        // does not matter: assigning junk value
        this->start_stop = StartStopType::Both;
    }
}

std::string Wedge::return_lilypond() const {
    switch (start_stop) {
    case StartStopType::Both:
        return "";
    case StartStopType::Stop:
        return R"__(\!)__";
    case StartStopType::Start:
        if (type == Type::Decrescendo) {
            return R"__(\>)__";
        }
        return R"__(\<)__";
    }
}

Words::Words(const tinyxml2::XMLElement* words_ptr) {
    content = tx2::text(words_ptr);

    auto italicity =
        (tx2::attribute_value(words_ptr, "font-style") == "italic");
    auto boldicity = (tx2::attribute_value(words_ptr, "font-weight") == "bold");

    if (boldicity && italicity) {
        formatting = Formatting::BoldItalics;
    } else if (boldicity) {
        formatting = Formatting::Bold;
    } else if (italicity) {
        formatting = Formatting::Italics;
    } else {
        formatting = Formatting::None;
    }
}

std::string Words::return_lilypond() const {
    auto is_bold   = (static_cast<short unsigned>(formatting) >= 2);
    auto is_italic = (static_cast<short unsigned>(formatting) % 2 != 0);

    return fmt::format(R"__(-\markup {{ {1}{2}"{0}" }})__", content,
                       is_bold ? R"__(\bold )__" : "",
                       is_italic ? R"__(\italic )__" : "");
}

RehearsalMark::RehearsalMark(const tx2::XMLElement* dyn_ptr) {
    text = tx2::text(dyn_ptr);
}

std::string RehearsalMark::return_lilypond() const {
    return fmt::format(R"__(-\mark "{0}" )__", text);
}
