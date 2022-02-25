//
//  formatter.hpp
//  mxl2ly
//
//  Created by Reventar on 25/02/2022.
//

#ifndef formatter_hpp
#define formatter_hpp

#include <string>
#include <vector>

namespace lmt {
class Formatter {
  public:
    Formatter(std::string format_options);
    void format_file(std::string file_name);

  private:
    // Note to the user: pass in arguments to the format string.
    // Do not alter default values.
    bool        will_format;
    std::string indent_string;

    // You may alter this: this is constant
    const std::vector<char> indenting_chars{'{', '<'};
    const std::vector<char> deindenting_chars{'}', '>'};
};
} // namespace lmt

#endif /* formatter_hpp */
