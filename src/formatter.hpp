//
//  formatter.hpp
//  mxl2ly
//
//  Created by Reventar on 25/02/2022.
//

#ifndef formatter_hpp
#define formatter_hpp

#include <fstream>
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
    bool        deindent_mnos;
    int         line_width;

    // Formating spare functions
    void format_whitespace(std::ifstream& input_file,
                           std::ofstream& output_file);
    void format_indentation(std::ifstream& input_file,
                            std::ofstream& output_file);
    void format_linewidth(std::ifstream& input_file,
                          std::ofstream& output_file);
    void deindent_measure_nums(std::ifstream& input_file,
                               std::ofstream& output_file);

    // You may alter this: this is constant
    const std::vector<char> indenting_chars{'{', '<'};
    const std::vector<char> deindenting_chars{'}', '>'};
    const std::vector<char> ignoring_chars{'\\', '^', '_', '-'};
};
} // namespace lmt

#endif /* formatter_hpp */
