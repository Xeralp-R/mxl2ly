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
#include <memory>

#include "tinyxml2/tinyxml2.h"

#include "statement.hpp"

class MusicTree {
public:
    MusicTree(std::string filename);
    
    std::string to_lilypond();
private:
    // Functions
    void extract_first_layer();
    
    double tenths_to_mm_conversion;
    tinyxml2::XMLDocument xml_document;
    std::vector<std::unique_ptr<AbstractStatement>> statements;
};

#endif /* music_tree_hpp */
