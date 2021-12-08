//
//  music_tree.hpp
//  mxl2ly
//
//  Created by Reventar on 11/11/2021.
//

#ifndef music_tree_hpp
#define music_tree_hpp

#include <array>
#include <iostream>
#include <memory>
#include <vector>

#include "tinyxml2/tinyxml2.h"

#include "statement.hpp"
#include "helper.hpp"

namespace lmt {
    
    class MusicTree {
    public:
        MusicTree(std::string filename);
        
        std::string to_lilypond();
        
    private:
        // Functions
        void extract_staff_info();
        void extract_paper_block();
        void extract_header_block();
        void extract_part_list();
        
        double tenths_to_mm_conversion;
        tinyxml2::XMLDocument xml_document;
        tinyxml2::XMLElement* root_element;
        std::vector<std::unique_ptr<AbstractStatement>> statements;
        
        // Constants
        const std::array<Length, 4> default_margins{inches(1), inches(1), inches(1),
            inches(1)};
    };
    
} // namespace lmt

#endif /* music_tree_hpp */
