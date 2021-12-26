//
//  measure_objects.hpp
//  mxl2ly
//
//  Created by Reventar on 04/12/2021.
//

#ifndef measure_objects_hpp
#define measure_objects_hpp

#include <string>
#include <memory>

#include "statement.hpp"

namespace lmt::aux {
    struct AbstractMeasureObject : public AbstractStatement {
        std::string get_type() { return "measure_object"; }
        virtual std::string get_subtype() = 0;
        virtual ~AbstractMeasureObject(){};
    };
    
    class Backup : public AbstractMeasureObject {
    public:
        Backup(short int duration) : duration_back(duration) {}
        
        std::string get_subtype() { return "backup"; };
    private:
        short int duration_back;
    };
    
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
}

#endif /* measure_objects_hpp */
