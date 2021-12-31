//
//  note_attributes.hpp
//  mxl2ly
//
//  Created by Reventar on 27/12/2021.
//

#ifndef note_attributes_hpp
#define note_attributes_hpp

#include <vector>
#include <optional>
#include <string>
#include <ostream>
#include <variant>
#include <iostream>
#include <exception>

#include "helper.hpp"
#include "statement.hpp"

namespace lmt::aux {
    struct AbstractNoteAttribute : public AbstractStatement {
        std::string get_type() { return "note_attribute"; }
        virtual std::string get_subtype() const = 0;
        virtual ~AbstractNoteAttribute(){};
    };
    
    struct GraceNote : public AbstractNoteAttribute {
        GraceNote(StartStopType start_stop,
                  bool is_slashed)
        : start_stop(start_stop), is_slashed(is_slashed) {};
        
        std::string get_subtype() const { return "grace_note"; }
        
        StartStopType start_stop;
        bool is_slashed;
    };
    
    struct Chord : public AbstractNoteAttribute {
        Chord(StartStopType start_stop) : start_stop(start_stop) {};
        
        std::string get_subtype() const { return "chord"; }
        
        StartStopType start_stop;
    };
    
    struct Tuplet : public AbstractNoteAttribute {
        Tuplet(StartStopType start_stop,
               unsigned short int actual_notes,
               unsigned short int normal_notes)
        : start_stop(start_stop), actual_notes(actual_notes), normal_notes(normal_notes) {};
        
        std::string get_subtype() const { return "tuplet"; }
        
        StartStopType start_stop;
        unsigned short int actual_notes;
        unsigned short int normal_notes;
    };
}

#endif /* note_attributes_hpp */
