//
//  measure_attributes.hpp
//  mxl2ly
//
//  Created by Reventar on 17/11/2021.
//

#ifndef measure_attributes_hpp
#define measure_attributes_hpp

#include <string>
#include <vector>
#include <map>
#include <exception>

#include "statement.hpp"

namespace lmt::aux {
    struct AbstractMeasureAttribute : public AbstractStatement {
        std::string get_type() { return "measure_attribute"; }
        virtual std::string get_subtype() = 0;
        virtual ~AbstractMeasureAttribute(){};
    };
    
    // The clef: add more clefs later
    class Clef : public AbstractMeasureAttribute {
    public:
        Clef(char type, short int staff_line) {
            if (type != 'c' && type != 'f' && type != 'g') {
                throw std::logic_error("Incorrect clef");
            }
            if (staff_line > 5) {
                throw std::logic_error("Incorrect clef position");
            }
            
            this->type = type;
            this->staff_line = staff_line;
        }
        
        std::string get_subtype() override { return "key-signature"; }
    private:
        char type;
        short int staff_line;
    };
    
    // The key signature
    class KeySignature : public AbstractMeasureAttribute {
    public:
        KeySignature(int fifths) {
            if (fifths < -7 || fifths > 7) {
                throw std::logic_error("Incorrect clef position");
            }
            
            this->fifths = fifths;
        }
        
        std::string get_subtype() { return "key-signature"; }
    private:
        int fifths;
        std::string pitch_class;
        std::string mode {"major"};
        
        const std::map<int, std::string> converter {
            {-7, "ces"},
            {-6, "ges"},
            {-5, "des"},
            {-4, "aes"},
            {-3, "ees"},
            {-2, "bes"},
            {-1, "f"},
            {0, "c"},
            {1, "g"},
            {2, "d"},
            {3, "a"},
            {4, "e"},
            {5, "b"},
            {6, "fis"},
            {7, "cis"}
        };
    };
    
    // the time signature
    class TimeSignature : public AbstractMeasureAttribute {
    public:
        TimeSignature(short int upper, short int lower)
        : upper_num{upper}, lower_num{lower} {};
        
        std::string get_subtype() override { return "time-signature"; }
        
        short int get_upper() { return this->upper_num; }
        short int get_lower() { return this->lower_num; }
    private:
        short int upper_num;
        short int lower_num;
    };
    
    class Barline : public AbstractMeasureAttribute {
    public:
        enum class Type {
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
        };
        
        // a double repeat is listed as 1 repeat before and 1 repeat after in 2 different bars
        enum class Repeat {
            //Regular,
            RepeatBefore,
            RepeatAfter
        };
        
        Barline(Barline::Type type, Barline::Repeat repeat)
        : type(type), repeat(repeat) {};
        
        std::string get_subtype() override { return "barline"; }
        
        Barline::Type get_type() const { return type; }
        Barline::Repeat get_repeat() const { return repeat; }
    private:
        const Barline::Type type;
        const Barline::Repeat repeat;
    };
}

#endif /* measure_attributes_hpp */
