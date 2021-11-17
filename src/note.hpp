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

#include "auxiliary.hpp"

// Forward declaration:
namespace lly {
    // Declared here
    class Note;
}

// so that this will work
std::ostream& operator<<(std::ostream& os, const lly::Note& nt);

// Actual declaration
namespace lly {
    // The class which represents notes
    class Note {
    public:
        // ==> Constructor
        Note(char pitch_class,
             lly::aux::Accidental accidental,
             short int octave,
             short int duration);
        Note(char pitch_class,
             lly::aux::Accidental accidental,
             short int octave,
             short int duration,
             short int dotted);
        
        // ==> Setter Functions
        void add_note_object(lly::aux::Dynamic);
        void add_note_object(lly::aux::Articulation);
        void add_note_object(lly::aux::Ornament);
        void add_note_object(lly::aux::Spanner);
        void add_note_object(lly::aux::Markup);
        void set_stem_direction(bool);
        
        // ==> Getter functions (I don't know whether these are necessary)
        char get_pitch_class();
        lly::aux::Accidental get_accidental();
        short int get_octave();
        lly::aux::Duration get_duration();
        
        // ==> Other Functions
        friend std::ostream& ::operator<<(std::ostream& os, const lly::Note& nt);
    private:
        // ==> Private setter functions
        void set_pitch_class(char);
        void set_accidental(lly::aux::Accidental);
        void set_octave(short int);
        void set_duration(short int);
        
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
