//
//  measure_attributes.hpp
//  mxl2ly
//
//  Created by Reventar on 17/11/2021.
//

#ifndef measure_attributes_hpp
#define measure_attributes_hpp

#include <exception>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "measure_objects.hpp"
#include "tinyxml2/tinyxml2.h"

namespace lmt::aux {
struct AbstractMeasureAttribute : public AbstractMeasureObject {
    std::string get_subtype() { return "attribute"; }

    virtual std::string get_subsubtype() const  = 0;
    virtual std::string return_lilypond() const = 0;

    virtual ~AbstractMeasureAttribute(){};
};

struct MeasureAttributeFactory {
    std::unique_ptr<AbstractMeasureAttribute>
    operator()(const tinyxml2::XMLElement* attr_ptr) const;
};

// The clef: add more clefs later
class Clef : public AbstractMeasureAttribute {
  public:
    Clef(char type, short int staff_line);
    Clef(const tinyxml2::XMLElement* clef_ptr);

    std::string get_subsubtype() const override { return "key-signature"; }
    std::string return_lilypond() const override;

  private:
    char      type;
    short int staff_line;
};

// The key signature
class KeySignature : public AbstractMeasureAttribute {
  public:
    KeySignature(int fifths);
    KeySignature(const tinyxml2::XMLElement* clef_ptr);

    std::string get_subsubtype() const override { return "key-signature"; }
    std::string return_lilypond() const override;

  private:
    int         fifths;
    std::string pitch_class;
    std::string mode{"major"};

    const std::map<int, std::string> converter{
        {-7, "ces"}, {-6, "ges"}, {-5, "des"}, {-4, "aes"}, {-3, "ees"},
        {-2, "bes"}, {-1, "f"},   {0, "c"},    {1, "g"},    {2, "d"},
        {3, "a"},    {4, "e"},    {5, "b"},    {6, "fis"},  {7, "cis"}};
};

// the time signature
class TimeSignature : public AbstractMeasureAttribute {
  public:
    TimeSignature(short int upper, short int lower);
    TimeSignature(const tinyxml2::XMLElement* attr_ptr);

    std::string get_subsubtype() const override { return "time-signature"; }
    std::string return_lilypond() const override;

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

    // a double repeat is listed as 1 repeat before and 1 repeat after in 2
    // different bars
    enum class Repeat { None, RepeatBefore, RepeatAfter };

    Barline(Barline::Type type, Barline::Repeat repeat)
        : type(type), repeat(repeat){};

    std::string get_subsubtype() const override { return "barline"; }
    std::string return_lilypond() const override;

    Barline::Type   get_type() const { return type; }
    Barline::Repeat get_repeat() const { return repeat; }

  private:
    Barline::Type   type;
    Barline::Repeat repeat;
};
} // namespace lmt::aux

#endif /* measure_attributes_hpp */
