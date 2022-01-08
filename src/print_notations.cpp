//
//  print_notations.cpp
//  mxl2ly
//
//  Created by Reventar on 03/01/2022.
//

#include "music_tree.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>

#include "fmt/format.h"
#include "notations.hpp"

using namespace lmt;
using namespace lmt::aux;

static const
std::unordered_map<std::string, std::function<void(const AbstractStatement*)>>
print_notation_dispatcher {
    {"", [](){}}
};

void MusicTree::PrintMusicFunctor::print_notations(const Note* note_ptr) {
    auto notations = note_ptr->get_notations();
}
