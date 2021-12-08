//
//  extract_music.cpp
//  mxl2ly
//
//  Created by Reventar on 08/12/2021.
//

#include "music_tree.hpp"

#include <vector>
#include <utility>
#include <memory>

#include "part.hpp"
#include "measure.hpp"
#include "note.hpp"

using namespace lmt;
namespace tx2 = tinyxml2;

static std::unique_ptr<Measure> extract_first_measure(tx2::XMLElement* part);
static std::unique_ptr<Note> extract_first_note(tx2::XMLElement* measure);

void MusicTree::extract_music() {
    for (auto* reader = root_element->FirstChildElement("part");
         reader != nullptr && is_element(valid_part_ids.begin(),
                                         valid_part_ids.end(),
                                         reader->Attribute("id"));
         reader = root_element->FirstChildElement("part")) {
        
        auto part_ptr = std::make_unique<Part>(reader->Attribute("id"));
        
        this->statements.emplace_back(std::move(part_ptr));
        
        this->root_element->DeleteChild(reader);
    }
}
