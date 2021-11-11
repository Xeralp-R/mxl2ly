//
//  music_tree.hpp
//  mxl2ly
//
//  Created by Reventar on 11/11/2021.
//

#ifndef music_tree_hpp
#define music_tree_hpp

#include <iostream>
#include <vector>

#include "tinyxml2/tinyxml2.h"

class MusicTree {
public:
    MusicTree(std::string filename);
    
    std::string to_lilypond();
private:
    // Functions
    tinyxml2::XMLDocument xml_document;
};

#endif /* music_tree_hpp */
