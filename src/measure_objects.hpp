//
//  measure_objects.hpp
//  mxl2ly
//
//  Created by Reventar on 04/12/2021.
//

#ifndef measure_objects_hpp
#define measure_objects_hpp

#include <memory>
#include <string>

#include "statement.hpp"

namespace lmt::aux {
struct AbstractMeasureObject : public AbstractStatement {
    std::string         get_type() { return "measure_object"; }
    virtual std::string get_subtype() const     = 0;
    virtual std::string return_lilypond() const = 0;
    virtual ~AbstractMeasureObject(){};
};

class Barline : public AbstractMeasureObject {
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

    std::string get_subtype() const override { return "barline"; }
    std::string return_lilypond() const override;

    Barline::Type   get_type() const { return type; }
    Barline::Repeat get_repeat() const { return repeat; }

  private:
    Barline::Type   type;
    Barline::Repeat repeat;
};

/*
class Tuplet : public AbstractMeasureObject {
  public:
    Tuplet(unsigned short int actual_notes, unsigned short int normal_notes)
        : actual_notes_var(actual_notes), normal_notes_var(normal_notes) {}

    void
    add_measure_object(std::unique_ptr<AbstractMeasureObject> abstract_ptr) {
        this->objects.push_back(std::move(abstract_ptr));
    }

    std::string            get_subtype() override { return "tuplet"; }
    int                    size() const { return this->objects.size(); }
    AbstractMeasureObject* at(int i) const { return this->objects.at(i).get(); }
    unsigned short int     actual_notes() const { return actual_notes_var; }
    unsigned short int     normal_notes() const { return normal_notes_var; }

  private:
    unsigned short int actual_notes_var = 0;
    unsigned short int normal_notes_var = 0;

    std::vector<std::unique_ptr<AbstractMeasureObject>> objects;
};
 */
} // namespace lmt::aux

#endif /* measure_objects_hpp */
