//
//  extract_notations.cpp
//  mxl2ly
//
//  Created by Reventar on 01/01/2022.
//

#include "music_tree.hpp"

#include <vector>
#include <utility>
#include <memory>
#include <cctype>
#include <cmath>

#include "note.hpp"
#include "notations.hpp"
#include "tinyxml2/tixml2ex.h"

using namespace lmt;
using namespace lmt::aux;
namespace tx2 = tinyxml2;

using std::unordered_map, std::string, std::function, std::vector;
using std::unique_ptr, aux::AbstractNotation, tinyxml2::XMLElement;
using std::make_unique, std::move;

static
unordered_map<string,
function<vector<unique_ptr<AbstractNotation>>(XMLElement*)>>
notation_dispatcher {
    {"slur", [](XMLElement* obj_ptr) -> vector<unique_ptr<AbstractNotation>> {
        std::string obj_name = tx2::attribute_value(obj_ptr, "type");
        vector<unique_ptr<AbstractNotation>> returner;
        
        if (obj_name == "start") {
            returner.push_back(move(make_unique<Slur>(StartStopType::Start)));
        }
        else if (obj_name == "stop") {
            returner.push_back(move(make_unique<Slur>(StartStopType::Stop)));
        }
        return returner;
    }},
    {"ornaments", [](XMLElement* obj_ptr) -> vector<unique_ptr<AbstractNotation>> {
        std::string ornament_name = obj_ptr->FirstChildElement()->Name();
        vector<unique_ptr<AbstractNotation>> returner;
        
        if (ornament_name == "turn" ||
            ornament_name == "delayed-turn" ||
            ornament_name == "vectical-turn") {
            returner.push_back(make_unique<Ornament>(Ornament::Type::Turn));
        }
        else if (ornament_name == "inverted-turn" ||
                 ornament_name == "delayed-inverted-turn" ||
                 ornament_name == "inverted-vertical-turn") {
            returner.push_back(make_unique<Ornament>(Ornament::Type::InvertedTurn));
        }
        else if (ornament_name == "trill-mark" ||
                 ornament_name == "shake" ||
                 ornament_name == "wavy-line") {
            returner.push_back(make_unique<Ornament>(Ornament::Type::Trill));
        }
        else if (ornament_name == "tremolo") {
            returner.push_back(make_unique<Ornament>(Ornament::Type::Tremolo));
        }
        else if (ornament_name == "mordent") {
            returner.push_back(make_unique<Ornament>(Ornament::Type::Mordent));
        }
        else if (ornament_name == "inverted-mordent") {
            returner.push_back(make_unique<Ornament>(Ornament::Type::InvertedMordent));
        }
        return returner;
    }},
    {"articulations", [](XMLElement* obj_ptr) -> vector<unique_ptr<AbstractNotation>> {
        vector<unique_ptr<AbstractNotation>> returner;
        for (auto art_ptr : obj_ptr) {
            std::string art_name = art_ptr->Name();
            if (art_name == "accent") {
                returner.push_back(move(make_unique<Articulation>(Articulation::Type::Accent)));
            }
            else if (art_name == "strong-accent") {
                returner.push_back(move(make_unique<Articulation>(Articulation::Type::Marcato)));
            }
            else if (art_name == "staccato") {
                returner.push_back(move(make_unique<Articulation>(Articulation::Type::Staccato)));
            }
            else if (art_name == "tenuto") {
                returner.push_back(move(make_unique<Articulation>(Articulation::Type::Tenuto)));
            }
            else if (art_name == "detached-legato") {
                returner.push_back(move(make_unique<Articulation>(Articulation::Type::Tenuto)));
                returner.push_back(move(make_unique<Articulation>(Articulation::Type::Staccato)));
            }
            else if (art_name == "staccatissimo") {
                returner.push_back(move(make_unique<Articulation>(Articulation::Type::Staccatissimo)));
            }
        }
        return returner;
    }},
    {"dynamics", [](XMLElement* obj_ptr) -> vector<unique_ptr<AbstractNotation>> {
        vector<unique_ptr<AbstractNotation>> returner;
        for (auto dyn_ptr : obj_ptr) {
            returner.push_back(move(make_unique<Dynamic>(dyn_ptr->Name())));
        }
        return returner;
    }},
};

std::vector<std::unique_ptr<aux::AbstractNotation>>
MusicTree::ExtractMusicFunctor::extract_notations(tinyxml2::XMLElement* note_ptr) {
    if (!tx2::exists(note_ptr, "notations")) {
        return {};
    }
    
    vector<unique_ptr<AbstractNotation>> returner;
    for (auto notation_ptr : tx2::selection(note_ptr, "notations")) {
        for (auto object_ptr : notation_ptr) {
            std::string object_name = object_ptr->Name();
            
            vector<unique_ptr<AbstractNotation>> temp = {};
            try {
                temp = notation_dispatcher.at(object_name)(object_ptr);
            } catch (...) {}
            
            returner.reserve(returner.size() + temp.size());
            for (auto& i : temp) {
                returner.push_back(move(i));
            }
        }
    }
    
    return returner;
}
