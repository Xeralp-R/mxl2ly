//
//  music_tree.hpp
//  mxl2ly
//
//  Created by Reventar on 11/11/2021.
//

#ifndef music_tree_hpp
#define music_tree_hpp

#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include "tinyxml2/tinyxml2.h"

#include "helper.hpp"
#include "measure.hpp"
#include "measure_objects.hpp"
#include "notations.hpp"
#include "note.hpp"
#include "statement.hpp"

namespace lmt {

class MusicTree {
  public:
    MusicTree()  = default;
    ~MusicTree() = default;

    void set_corrections(bool correction) { this->correction = correction; };
    void accept_musicxml(std::string filename);
    void print_lilypond(std::string filename);

    unsigned long get_measure_duration() const {
        return this->measure_duration;
    };

    // Constants
    const std::array<Length, 4> default_margins{inches(1), inches(1), inches(1),
                                                inches(1)};
    static constexpr char       newline = '\n';

  private:
    // Functions and functors
    void extract_staff_info();
    void extract_paper_block();
    void extract_header_block();
    void extract_part_list();
    void extract_music();

    void print_staff_info() const;
    void print_paper_block() const;
    void print_header_block() const;
    void print_part_list() const;
    void print_music() const;

    // Variables
    double                tenths_to_mm_conversion;
    unsigned long int     measure_duration;
    tinyxml2::XMLDocument xml_document;
    tinyxml2::XMLElement* root_element;

    std::vector<std::unique_ptr<AbstractStatement>> statements;
    std::vector<std::string>                        valid_part_ids;
    mutable std::ofstream                           out;

    bool correction = false;
};

} // namespace lmt

#endif /* music_tree_hpp */
