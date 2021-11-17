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

#include "statement.hpp"

namespace lmt {
    class Pitch : public AbstractStatement {
        char pitch_class;
        short int octave;
    };
    
    class Note : public AbstractStatement {
    public:
        // ==> Constructor
        Note(Pitch pitch,
             short int duration);
        Note(Pitch pitch,
             short int duration,
             short int dotted);
        
        // ==> Setter Functions
        void add_note_object(AbstractStatement*);
        void set_stem_direction(bool);
        
        // ==> Getter functions (I don't know whether these are necessary)
        Pitch get_pitch();
        lly::aux::Duration get_duration();
    private:
        // ==> Required Variables
        char pitch_class; // valid values: a-g, r, s
        short int octave; // valid values: -3 to 4
        lly::aux::Accidental accidental; // std::optional because there's an error without.
        short int duration; // valid values: powers of 2
        
        // ==> Non-required Variables
        std::vector<lly::aux::Directions> directions;
        std::vector<lly::aux::Notations> notations;
        std::optional<bool> stem_direction = {}; // true for up, false for down
        std::optional<short int> dotted = {}; // number of dots
        
        // ==> Constants
        std::vector<char> valid_pitch_classes {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'r', 's'};
        std::vector<short int> valid_octaves {-3, -2, -1, 0, 1, 2, 3, 4};
        std::vector<short int> valid_durations {1, 2, 4, 8, 16, 32, 64, 128};
    };
}

#endif /* note_hpp */
