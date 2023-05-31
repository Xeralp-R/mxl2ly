//
//  notations.cpp
//  mxl2ly
//
//  Created by Reventar on 08/01/2022.
//

#include "notations.hpp"

#include "fmt/format.h"
#include "tinyxml2/tixml2ex.h"

using namespace lmt::aux;

std::vector<std::unique_ptr<AbstractNotation>>
NotationFactory::operator()(const tinyxml2::XMLElement* attr_ptr) const {

    std::vector<std::unique_ptr<AbstractNotation>> returner;
    std::string                                    switcher = attr_ptr->Name();
    if (switcher == "articulations") {
        for (auto ptr : attr_ptr) {
            returner.push_back(std::move(std::make_unique<Articulation>(ptr)));
        }
        return returner;
    }
    if (switcher == "dynamics") {
        for (auto ptr : attr_ptr) {
            returner.push_back(std::move(std::make_unique<Dynamic>(ptr)));
        }
        return returner;
    }
    if (switcher == "ornaments") {
        for (auto ptr : attr_ptr) {
            returner.push_back(std::move(std::make_unique<Ornament>(ptr)));
        }
        return returner;
    }
    if (switcher == "slur") {
        returner.push_back(std::move(std::make_unique<Slur>(attr_ptr)));
        return returner;
    }
    if (switcher == "tied") {
        returner.push_back(std::move(std::make_unique<Tie>(attr_ptr)));
        return returner;
    }
    if (switcher == "arpeggiate") {
        returner.push_back(std::move(std::make_unique<Arpeggiando>(attr_ptr)));
        return returner;
    }
    return {};
}

Dynamic::Dynamic(std::string type) : type(type) {
    if (!helper::is_element(permitted_types.begin(), permitted_types.end(),
                            type)) {
        throw std::logic_error("Incorrect dynamic");
    }
}

Dynamic::Dynamic(const tinyxml2::XMLElement* dyn_ptr)
    : type(dyn_ptr->FirstChildElement()->Name()) {
    if (!helper::is_element(permitted_types.begin(), permitted_types.end(),
                            type)) {
        throw std::logic_error("Incorrect dynamic");
    }
}

std::string Dynamic::return_lilypond() const {
    return fmt::format(R"__(\{0})__", this->type);
}

Articulation::Articulation(Articulation::Type type) : type(type) {}

Articulation::Articulation(const tinyxml2::XMLElement* art_ptr) {
    std::string art_name = art_ptr->Name();
    if (art_name == "accent") {
        type = Articulation::Type::Accent;
    } else if (art_name == "strong-accent") {
        type = Articulation::Type::Marcato;
    } else if (art_name == "staccato") {
        type = Articulation::Type::Staccato;
    } else if (art_name == "tenuto") {
        type = Articulation::Type::Tenuto;
    } else if (art_name == "detached-legato") {
        type = Articulation::Type::DetachedLegato;
    } else if (art_name == "staccatissimo") {
        type = Articulation::Type::Staccatissimo;
    } else {
        std::cerr << "Warning: Unhandled articulation " << art_name << '\n';
        // throw std::logic_error("currently unhandled articulation");
    }
}

std::string Articulation::return_lilypond() const {
    switch (this->type) {
    case Articulation::Type::Accent:
        return R"__(->)__";
    case Articulation::Type::Espressivo:
        return R"__(\espressivo)__";
    case Articulation::Type::Tenuto:
        return R"__(--)__";
    case Articulation::Type::Marcato:
        return R"__(-^)__";
    case Articulation::Type::Staccato:
        return R"__(-.)__";
    case Articulation::Type::Staccatissimo:
        return R"__(-!)__";
    case Articulation::Type::DetachedLegato:
        return R"__(-.--)__";
    default:
        // unreached, supposedly
        return "";
    }
}

Ornament::Ornament(Ornament::Type type) : type(type) {}

Ornament::Ornament(const tinyxml2::XMLElement* ornament_ptr) {
    std::string ornament_name = ornament_ptr->Name();
    // correct later
    if (ornament_name == "turn" || ornament_name == "delayed-turn" ||
        ornament_name == "vectical-turn") {
        type = Ornament::Type::Turn;
    } else if (ornament_name == "inverted-turn" ||
               ornament_name == "delayed-inverted-turn" ||
               ornament_name == "inverted-vertical-turn") {
        type = Ornament::Type::InvertedTurn;
    } else if (ornament_name == "trill-mark" || ornament_name == "shake" ||
               ornament_name == "wavy-line") {
        type = Ornament::Type::Trill;
    } else if (ornament_name == "tremolo") {
        type = Ornament::Type::Tremolo;
    } else if (ornament_name == "mordent") {
        type = Ornament::Type::Mordent;
    } else if (ornament_name == "inverted-mordent") {
        type = Ornament::Type::InvertedMordent;
    } else {
        std::cerr << "Warning: Unhandled ornament " << ornament_name << '\n';
        // throw std::logic_error("currently unhandled ornament");
    }
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

Slur::Slur(StartStopType start_stop) : start_stop(start_stop) {}

Slur::Slur(const tinyxml2::XMLElement* slur_ptr) {
    std::string obj_name = tinyxml2::attribute_value(slur_ptr, "type");
    if (obj_name == "start") {
        start_stop = StartStopType::Start;
    } else if (obj_name == "stop") {
        start_stop = StartStopType::Stop;
    } else {
        std::cerr << "Warning: Unusual slur \n";
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

Tie::Tie(StartStopType start_stop) : start_stop(start_stop) {}

Tie::Tie(const tinyxml2::XMLElement* tie_ptr) {
    std::string obj_name = tinyxml2::attribute_value(tie_ptr, "type");
    if (obj_name == "start") {
        start_stop = StartStopType::Start;
    } else if (obj_name == "stop") {
        start_stop = StartStopType::Stop;
    } else if (obj_name == "let-ring") {
        std::cerr << "Let ring not yet implemented. \n";
    } else {
        std::cerr << "Warning: Unusual tie \n";
    }
}

std::string Tie::return_lilypond() const {
    switch (this->start_stop) {
    case StartStopType::Start:
        return "~";
        break;
    default:
        return "";
        break;
    }
}

Arpeggiando::Arpeggiando(UpDownType up_down) : up_down(up_down) {}

Arpeggiando::Arpeggiando(const tinyxml2::XMLElement* arp_ptr) {
    std::string direction_str = tinyxml2::attribute_value(arp_ptr, "direction");

    if (direction_str == "down") {
        this->up_down = UpDownType::Down;
        return;
    }
    this->up_down = UpDownType::Up;
}

std::string Arpeggiando::return_lilypond() const {
    switch (this->up_down) {
    case UpDownType::Down:
        return R"__(\arpeggio)__";
        std::cerr << "Cannot accomodate downward arpeggios yet";
        break;

    default:
        return R"__(\arpeggio)__";
        break;
    }
}
