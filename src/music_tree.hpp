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
#include "measure_objects.hpp"
#include "measure.hpp"
#include "note.hpp"

namespace lmt {
    
    class MusicTree {
    public:
        MusicTree() = default;
        ~MusicTree() = default;
        
        void accept_musicxml(std::string filename);
        void print_lilypond(std::string filename);
        
        // Constants
        const std::array<Length, 4> default_margins{inches(1), inches(1), inches(1),
            inches(1)};
        static constexpr char newline = '\n';
        static constexpr auto tab = "    ";
    private:
        // Functions and functors
        void extract_staff_info();
        void extract_paper_block();
        void extract_header_block();
        void extract_part_list();
        
        class ExtractMusicFunctor {
        public:
            ExtractMusicFunctor(MusicTree* tree_ptr) : tree_ptr(tree_ptr) {}
            void operator() ();
        private:
            MusicTree* tree_ptr;
            std::unique_ptr<Measure>     extract_measure(tinyxml2::XMLElement* meas_elem_ptr);
            std::unique_ptr<aux::Tuplet> extract_tuplet(std::vector<tinyxml2::XMLElement*> tuplet_elems);
            std::unique_ptr<Note>        extract_note(tinyxml2::XMLElement* note_elem_ptr);
        } extract_music{this};
        friend class ExtractMusicFunctor;
        
        void print_staff_info() const;
        void print_paper_block() const;
        void print_header_block() const;
        void print_part_list() const;
        
        class PrintMusicFunctor {
        public:
            PrintMusicFunctor(const MusicTree* tree_ptr) : tree_ptr(tree_ptr) {}
            void operator()();
        private:
            const MusicTree* tree_ptr;
            void print_measure(const Measure* measure_ptr);
            
            void print_note(const Note* note_ptr);
            void print_gracenote(const std::vector<const Note*> notes);
            void print_tuplet(const std::vector<const Note*> notes);
            void print_chord(const std::vector<const Note*> notes);
            void print_note(const Note* note_ptr, unsigned int lilypond_duration);
            
            double note_time_alteration = 1.00;
            bool is_grace = false;
        } print_music{this};
        friend class PrintMusicFunctor;
        
        std::string convert_number_names(const std::string) const;
        const std::vector<std::string> number_names {
            "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
        };
        
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
