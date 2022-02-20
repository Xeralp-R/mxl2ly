//
//  part_.hpp
//  mxl2ly
//
//  Created by Reventar on 17/11/2021.
//

#ifndef part_hpp
#define part_hpp

#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "measure.hpp"
#include "statement.hpp"
#include "tinyxml2/tixml2ex.h"

namespace lmt {
class PartList : public AbstractStatement {
  public:
    PartList() = default;
    PartList(std::initializer_list<std::pair<std::string, std::string>> parts);

    void add_part(std::string part_id, std::string part_name);

    std::string get_type() override { return "part_list"; }
    std::map<std::string, std::string> get_parts() const { return this->parts; }

  private:
    std::map<std::string, std::string> parts;
};

class Part : public AbstractStatement {
  public:
    Part(std::string id);
    Part(tinyxml2::XMLElement* part_elem, const MusicTree* tree_ptr);

    void add_measure(std::unique_ptr<Measure> measure_ptr);

    std::pair<std::string, std::string> return_lilypond() const;

    std::string get_type() override { return "part"; }
    std::string get_id() const { return this->id; }
    // int         size() const { return this->measures.size(); }
    // Measure*    at(int index) const { return this->measures.at(index).get();
    // }

  private:
    struct Staff {
        Staff(int id) : id(id){};
        std::vector<std::unique_ptr<Measure>> measures;
        int                                   id;
    };

    std::string id;

    std::vector<std::unique_ptr<Staff>> staves;
    /*
     bool        using_many_staves;
    // the measures if there's only 1 voice
    std::vector<std::unique_ptr<Measure>> measures_flat;
    // the measures if there are many voices
    std::unordered_map<int, std::vector<std::unique_ptr<Measure>>>
        measures_dimen;
     */
};
} // namespace lmt

#endif /* part_hpp */
