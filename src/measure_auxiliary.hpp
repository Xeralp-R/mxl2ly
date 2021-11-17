//
//  measure_auxiliary.hpp
//  mxl2ly
//
//  Created by Reventar on 17/11/2021.
//

#ifndef measure_auxiliary_hpp
#define measure_auxiliary_hpp

namespace lmt::aux {
    // The clef: add more clefs later
    enum class Clef {
        Treble,
        Alto,
        Bass
    };
    
    // The key signature
    struct KeySignature {
        // valid values: a to g only
        char pitch_class;
        enum {
            Major,
            Minor
            // TODO: add more here later
        } mode;
    };
    
    // the time signature
    struct TimeSignature {
        short int upper;
        short int lower;
    };
    
    struct Barline {
        enum {
            None,
            // A single light barline
            Regular,
            // A single heavy barline
            Heavy,
            // A regular double barline
            LightLight,
            // An ending barline
            LightHeavy,
            // A starting barline?
            HeavyLight,
            // An unusual double heavy barline
            HeavyHeavy
            // TODO: Add more here later
        } type;
        
        // a double repeat is listed as 1 repeat before and 1 repeat after in 2 different bars
        enum class Quality {
            //Regular,
            RepeatBefore,
            RepeatAfter
        } quality;
    };
}

#endif /* measure_auxiliary_hpp */
