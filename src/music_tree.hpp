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
#include <fstream>

#include "tinyxml2/tinyxml2.h"

#include "statement.hpp"
#include "helper.hpp"

namespace lmt {
    
    class MusicTree {
    public:
        MusicTree() = default;
        
        void accept_musicxml(std::string filename);
        void print_lilypond(std::string filename);
        
        // Constants
        const std::array<Length, 4> default_margins{inches(1), inches(1), inches(1),
            inches(1)};
        static constexpr char newline = '\n';
        static constexpr auto tab = "    ";
    private:
        // Functions
        void extract_staff_info();
        void extract_paper_block();
        void extract_header_block();
        void extract_part_list();
        void extract_music();
        
        void print_staff_info() const;
        void print_paper_block() const;
        void print_header_block() const;
        void print_music() const;
        void print_part_list() const;
        
        // Variables
        double tenths_to_mm_conversion;
        unsigned long int measure_duration;
        tinyxml2::XMLDocument xml_document;
        tinyxml2::XMLElement* root_element;
        
        std::vector<std::unique_ptr<AbstractStatement>> statements;
        std::vector<std::string> valid_part_ids;
        mutable std::ofstream out;
    };
    
} // namespace lmt

#endif /* music_tree_hpp */
