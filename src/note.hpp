//
//  note.hpp
//  mxl2ly
//
//  Created by Reventar on 17/11/2021.
//

#ifndef note_hpp
#define note_hpp

#include <vector>
#include <optional>
#include <string>
#include <ostream>
#include <variant>
#include <exception>

#include "statement.hpp"
#include "notations.hpp"

namespace lmt {
    class Note : public AbstractStatement {
    public:
        class Pitch : public AbstractStatement {
            Pitch(char pitch_class, short int octave, short int alteration) {
                if (!is_element(valid_pitch_classes.begin(),
                                valid_pitch_classes.end(),
                                pitch_class)) {
                    throw std::logic_error("Invalid pitch class");
                }
                if (!is_element(valid_octaves.begin(),
                                valid_octaves.end(),
                                octave)) {
                    throw std::logic_error("Invalid octave");
                }
                if (!is_element(valid_alterations.begin(),
                                valid_alterations.end(),
                                alteration)) {
                    throw std::logic_error("Invalid alteration (sharp/flat)");
                }
                
                this->pitch_class = pitch_class;
                this->octave = octave;
                this->alteration = alteration;
            }
            
            std::string get_type() override { return "pitch"; }
        private:
            short int alteration;
            char pitch_class;
            short int octave;
            
            std::vector<char> valid_pitch_classes {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'r', 's'};
            std::vector<short int> valid_octaves {1, 2, 3, 4, 5, 6, 7, 8, 9};
            std::vector<short int> valid_alterations {-2, -1, 0, 1, 2};
        };
        
        Note(Pitch pitch,
             short int duration);
        Note(Pitch pitch,
             short int duration,
             short int dotted);
        
        void add_notation(std::unique_ptr<lmt::aux::AbstractNotation> notation);
    private:
        // ==> Required Variables
        Pitch pitch;
        short int duration; // valid values: powers of 2
        
        // ==> Non-required Variables
        std::vector<std::unique_ptr<lmt::aux::AbstractNotation>> notations;
        std::optional<short int> dotted = {}; // number of dots
        
        // ==> Constants
        std::vector<short int> valid_durations {1, 2, 4, 8, 16, 32, 64, 128};
    };
}

#endif /* note_hpp */
