//
//  measure.hpp
//  mxl2ly
//
//  Created by Reventar on 04/12/2021.
//

#ifndef measure_hpp
#define measure_hpp

#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <variant>
#include <utility>

#include "auxiliary.hpp"
#include "note.hpp"

// ==> Forward declarations
namespace lly {
    // Defined elsewhere
    class Note;
    class Voice;
    
    // Defined here
    class Measure;
}

std::ostream& operator<<(std::ostream&, const lly::Measure&);

// ==> Proper declarations
namespace lly {
    class Measure {
    public:
        // ==> constructors
        Measure(int id_number);
        Measure(int id_number, std::vector<lly::Note> notes);
        
        // ==> Setters
        void add_note(lly::Note);
        void set_partial(); // makes it a partial measure. Does not change the time signature.
        void set_newline(); // makes this measure on a new line.
        void set_actual_time_signature(lly::aux::TimeSignature);
        void add_measure_object(lly::aux::Clef);
        void add_measure_object(lly::aux::KeySignature);
        void add_measure_object(lly::aux::TimeSignature);
        void add_measure_object(lly::aux::Barline);
        void add_measure_object(lly::aux::MeasureTypes);
        
        // ==> Functions
        // confirms that the measure has the correct number of notes
        bool confirm();
        
        // ==> Friends
        friend Voice;
        friend std::ostream& ::operator<<(std::ostream&, const lly::Measure&);
    private:
        // ==> Variables
        std::vector<Note> notes;
        int id_number;
        bool partial = false;
        bool newline = false;
        double count = 0;
        std::optional<lly::aux::TimeSignature> actual_time_signature;
        
        std::optional<int> written_measure_number;
        std::optional<lly::aux::Clef> written_clef;
        std::optional<lly::aux::KeySignature> written_key_signature;
        std::optional<lly::aux::TimeSignature> written_time_signature;
        std::optional<lly::aux::Barline> left_barline;
        std::optional<lly::aux::Barline> right_barline;
    };
}


#endif /* measure_hpp */
