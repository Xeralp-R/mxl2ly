//
//  formatter.cpp
//  mxl2ly
//
//  Created by Reventar on 25/02/2022.
//

#include "formatter.hpp"

#include <fstream>
#include <numeric>
#include <regex>
#include <sstream>

#include "ghc/filesystem.hpp"
#include "helper.hpp"
#include "nlohmann/json.hpp"

using namespace lmt;

Formatter::Formatter(std::string format_options) {
    auto format_list    = nlohmann::json::parse(format_options);
    this->will_format   = format_list.at("format");
    this->indent_string = format_list.at("indent");
    this->line_width    = format_list.at("maxLineWidth");
    this->deindent_mnos = format_list.at("deindentMeasureNumbers");
}

void Formatter::format_file(std::string file_name) {
    ghc::filesystem::copy_file(
        file_name, "~mxl2ly_temporary_1.tmp",
        ghc::filesystem::copy_options::overwrite_existing);

    std::ifstream input_file("~mxl2ly_temporary_1.tmp");
    std::ofstream output_file("~mxl2ly_temporary_2.tmp");
    auto          copy_over = [&]() {
        input_file.close();
        output_file.close();
        ghc::filesystem::rename("~mxl2ly_temporary_2.tmp",
                                         "~mxl2ly_temporary_1.tmp");
        input_file.open("~mxl2ly_temporary_1.tmp");
        output_file.open("~mxl2ly_temporary_2.tmp");
    };

    format_whitespace(input_file, output_file);
    copy_over();
    format_indentation(input_file, output_file);
    copy_over();
    format_linewidth(input_file, output_file);
    copy_over();
    deindent_measure_nums(input_file, output_file);
    copy_over();

    // delete the first file
    input_file.close();
    output_file.close();
    ghc::filesystem::remove(file_name);
    ghc::filesystem::remove("~mxl2ly_temporary_2.tmp");
    ghc::filesystem::rename("~mxl2ly_temporary_1.tmp", file_name);
}

void Formatter::format_whitespace(std::ifstream& input_file,
                                  std::ofstream& output_file) {
    std::string current_line;
    std::regex  replacer(R"__((\S+)(\s+))__");
    std::string replacant = R"__($1 )__";
    while (std::getline(input_file, current_line)) {
        if (current_line == "") {
            output_file << '\n';
            continue;
        }

        output_file << std::regex_replace(current_line, replacer, replacant)
                    << '\n';
    }
}

void Formatter::format_indentation(std::ifstream& input_file,
                                   std::ofstream& output_file) {
    std::string current_line;
    std::string current_indent;

    auto count_times = [this](std::string tester, std::vector<char> comparers) {
        int  count;
        char last_character = '\0';

        for (auto inner_c : tester) {
            // if it is in the vector and it is not to be ignored
            if (helper::is_element(comparers.begin(), comparers.end(),
                                   inner_c) &&
                !helper::is_element(ignoring_chars.begin(),
                                    ignoring_chars.end(), last_character)) {
                ++count;
            }
            last_character = inner_c;
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
    };
}

void Formatter::format_linewidth(std::ifstream& input_file,
                                 std::ofstream& output_file) {
    if (line_width == 0) {
        return;
    }

    auto split_string = [](const std::string c_input, unsigned int count) {
        auto input = c_input;

        // if the input is short enough, then don't bother
        if (input.size() < count) {
            return std::vector{input};
        }

        // how this regex works:
        // split the string into everything before and after
        // the last space before the last text.
        // The 2 parts will be analyzed separately.
        std::regex               line_checker(R"__(([\s\S]+\s+)(\S+\s*))__");
        std::vector<std::string> returner;

        while (!input.empty()) {
            auto tentative = input.substr(0, count);
            auto actual    = std::regex_replace(tentative, line_checker, "$1");
            auto spare     = std::regex_replace(tentative, line_checker, "$2");

            // if this is the end of the bar
            if (spare == "|" || spare == "" ||
                !std::regex_match(tentative, line_checker)) {
                returner.push_back(tentative);
                input.clear();
            } else {
                returner.push_back(actual);
                input = spare + input.replace(0, tentative.size(), "");
            }
        }
        return returner;
    };

    std::string current_line;
    while (std::getline(input_file, current_line)) {
        unsigned int multiplicand =
            std::floor(current_line.size() / line_width);
        if (multiplicand == 0) {
            output_file << current_line << '\n';
            continue;
        }

        // analyze the current line
        std::regex  indent_regex(R"__((\s*)[\s\S]*)__");
        std::smatch indent_match;
        std::string current_indent;
        if (std::regex_search(current_line, indent_match, indent_regex)) {
            current_indent = indent_match[1];
        }

        std::string unindented_line =
            current_line.replace(0, current_indent.size(), "");
        unsigned int effective_lw = line_width - current_indent.size();
        auto         vec          = split_string(unindented_line, effective_lw);
        for (auto line : vec) {
            output_file << current_indent << line << '\n';
        }
    }
}

void Formatter::deindent_measure_nums(std::ifstream& input_file,
                                      std::ofstream& output_file) {
    std::string current_line;
    std::regex  comment_regex(R"__(\s+% \d+)__");
    while (std::getline(input_file, current_line)) {
        if (std::regex_search(current_line, comment_regex)) {
            current_line = current_line.replace(0, indent_string.size(), "");
        }
        output_file << current_line << '\n';
    }
}
