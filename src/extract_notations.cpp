//
//  extract_notations.cpp
//  mxl2ly
//
//  Created by Reventar on 01/01/2022.
//

#include "music_tree.hpp"

#include <cctype>
#include <cmath>
#include <memory>
#include <utility>
#include <vector>

#include "notations.hpp"
#include "note.hpp"
#include "tinyxml2/tixml2ex.h"

using namespace lmt;
namespace tx2 = tinyxml2;

static const aux::NotationFactory notation_factory;

std::vector<std::unique_ptr<aux::AbstractNotation>>
MusicTree::ExtractMusicFunctor::extract_notations(
    tinyxml2::XMLElement* note_ptr) {
    if (!tx2::exists(note_ptr, "notations")) {
        return {};
    }

    std::vector<std::unique_ptr<aux::AbstractNotation>> returner;
    for (auto notation_ptr : tx2::selection(note_ptr, "notations")) {
        for (auto object_ptr : notation_ptr) {
            auto temp = notation_factory(object_ptr);

            returner.reserve(returner.size() + temp.size());
            for (auto& i : temp) {
                returner.push_back(std::move(i));
            }
        }
    }

    return returner;
}
