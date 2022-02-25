//
//  formatter.cpp
//  mxl2ly
//
//  Created by Reventar on 25/02/2022.
//

#include "formatter.hpp"

#include "ghc/filesystem.hpp"
#include "helper.hpp"
#include "nlohmann/json.hpp"
#include <fstream>

using namespace lmt;

Formatter::Formatter(std::string format_options) {
    auto format_list    = nlohmann::json::parse(format_options);
    this->will_format   = format_list.at("format");
    this->indent_string = format_list.at("indent");
}

void Formatter::format_file(std::string file_name) {
    std::ifstream input_file(file_name);
    std::ofstream output_file("~mxl2ly_teporary.tmp");

    std::string current_line;
    std::string current_indent;

    auto count_times = [](std::string tester, std::vector<char> comparers) {
        int count;
        for (auto inner_c : tester) {
            if (helper::is_element(comparers.begin(), comparers.end(),
                                   inner_c)) {
                ++count;
            }
        }
        return count;
    };

    while (std::getline(input_file, current_line)) {
        if (current_line == "") {
            output_file << '\n';
            continue;
        }

        // if there are more deindenting chars than indenting chars, deindent
        // this line
        if (count_times(current_line, indenting_chars) <
            count_times(current_line, deindenting_chars)) {
            current_indent.erase(current_indent.begin(),
                                 current_indent.begin() + indent_string.size());
        }

        // create and write the actual thing
        std::string resultant_line = current_indent + current_line + '\n';
        output_file << resultant_line;

        // if there are more indenting chars than deindenting chars, add indent
        // to next line
        if (count_times(current_line, indenting_chars) >
            count_times(current_line, deindenting_chars)) {
            current_indent += this->indent_string;
        }
    }

    // delete the first file
    input_file.close();
    ghc::filesystem::remove(file_name);
    ghc::filesystem::rename("~mxl2ly_teporary.tmp", file_name);
}
