//
//  note_auxiliary.hpp
//  mxl2ly
//
//  Created by Reventar on 17/11/2021.
//

#ifndef note_auxiliary_hpp
#define note_auxiliary_hpp

#include <vector>
#include <optional>
#include <string>
#include <ostream>
#include <variant>
#include <iostream>

namespace lmt::aux {
    enum class Location {
        Above,
        Below
    };
    
    struct Duration {
        short int time;
        std::optional<short int> dotted;
        operator double() const;
    };
    
    // the accidental
    struct Accidental {
        // the quality
        enum {
            DoubleFlat,
            Flat,
            Natural,
            Sharp,
            DoubleSharp
        } type;
        
        // whether it is cautionary
        enum class Quality {
            Invisible,
            Cautionary,
            Visible
        } quality;
    };
    
    // I think it may be better to represent them individually,
    // rather than have to match strings-
    // something that can be tricky to do in C++.
    struct Dynamic {
        enum {
            pppppppp,
            ppppppp,
            pppppp,
            ppppp,
            pppp,
            ppp,
            pp,
            p,
            mp,
            mf,
            f,
            ff,
            fff,
            ffff,
            fffff,
            ffffff,
            fffffff,
            ffffffff
        } type;
        
        std::optional<Location> location {};
    };
    
    struct Articulation {
        enum {
            Staccato, // like a dot
            Staccatissimo, // a wedge
            Tenuto, // a line
            Espressivo, // cresc/decresc on one note
            Accent, // a < sign
            Marcato // a hat?
        } type;
        
        std::optional<Location> location {};
    };
    
    struct Ornament {
        enum {
            Turn,
            Trill,
            Prall,
            Mordent
        } type;
        
        std::optional<Location> location {};
    };
    
    struct Spanner {
        enum {
            Crescendo,
            Decrescendo,
            Pedal,
            OttavaAlta,
            OttavaBassa,
            Slur
        } type;
        
        // true if it starts: false if it ends
        bool start;
        
        std::optional<Location> location {};
    };
    
    struct Markup {
        std::string text;
        bool italics;
        bool boldface;
        std::optional<Location> location {};
    };
    
    // represents symbols
    // TODO: Implement
    struct Symbol {};
    
    // a function to stringify vectors using python list notation:
    // e.g. [1,2,3,4,5]
    std::string stringify(std::vector<short int> vec);
    std::string stringify(std::vector<int> vec);
    std::string stringify(std::vector<char> vec);
    
    // convenient typedefs:
    typedef std::variant<Ornament, Articulation, Dynamic, Spanner> Notations;
    typedef std::variant<Spanner, Markup, Symbol> Directions;
    typedef std::variant<KeySignature, TimeSignature, Clef> Attributes;
}

#endif /* note_auxiliary_hpp */
