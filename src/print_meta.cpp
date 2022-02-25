//
//  print_lilypond.cpp
//  mxl2ly
//
//  Created by Reventar on 15/12/2021.
//

#include "music_tree.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <string_view>
#include <vector>

#include "corrector.hpp"
#include "fmt/format.h"
#include "header_and_paper.hpp"
#include "part.hpp"

using namespace lmt;

void MusicTree::print_staff_info() const {
    const auto staff_width =
        dynamic_cast<Statement<Length>*>(statements.at(0).get())->get_content();

    out << "#(set-global-staff-size ";
    out << staff_width.get_points();
    out << ")\n\n";

    if (this->correction) {
        out << lmt::aux::corrected_preamble << "\n\n";
    }
}

void MusicTree::print_paper_block() const {
    // get the paper pointer
    const auto paper_ptr = dynamic_cast<Paper*>(statements.at(1).get());

    // Prepare the page size
    out << R"||(#(set! paper-alist )||" << newline;
    out << fmt::format(
               R"--((cons '("new_size" . (cons (* {0} mm) (* {1} mm))) paper-alist)))--",
               paper_ptr->get_width().get_millimeters(),
               paper_ptr->get_height().get_millimeters())
        << newline;

    // Output the actual paper thing
    out << R"(\paper {)" << newline;
    out << R"||(#(set-paper-size "new_size"))||" << newline;
    out << fmt::format(R"||(top-margin = {0}\mm)||",
                       paper_ptr->get_margin(Paper::Margins::TopMargin)
                           .get_millimeters())
        << newline;
    out << fmt::format(R"||(bottom-margin = {0}\mm)||",
                       paper_ptr->get_margin(Paper::Margins::BottomMargin)
                           .get_millimeters())
        << newline;
    out << fmt::format(R"||(left-margin = {0}\mm)||",
                       paper_ptr->get_margin(Paper::Margins::LeftMargin)
                           .get_millimeters())
        << newline;
    out << fmt::format(R"||(right-margin = {0}\mm)||",
                       paper_ptr->get_margin(Paper::Margins::RightMargin)
                           .get_millimeters())
        << newline;
    out << R"||(ragged-last-bottom = ##f)||" << newline;
    out << "}" << newline << newline;
}

void MusicTree::print_header_block() const {
    const auto header_ptr = dynamic_cast<Header*>(statements.at(2).get());

    out << R"||(\header {)||" << newline;
    for (auto pair : header_ptr->get_statements()) {
        out << fmt::format(R"||({0} = "{1}")||", pair.first, pair.second)
            << newline;
    }
    out << "}" << newline << newline;
}

void MusicTree::print_part_list() const {
    /*const auto list_ptr = dynamic_cast<PartList*>(statements.at(3).get());

    out << R"||(\score {)||" << newline;
    std::for_each(print_directory.begin(), print_directory.end(),
                  [this](const auto& a) { out << a; });
    out << "}" << newline;*/
}

void MusicTree::print_music() const {
    std::vector<std::string> print_directory;

    for (int i = 4; i < this->statements.size(); ++i) {
        auto part_ptr = dynamic_cast<Part*>(this->statements.at(i).get());

        const auto& [entry, music] = part_ptr->return_lilypond();
        out << music;
        print_directory.push_back(entry);
    }

    out << R"||(\score {)||" << newline;
    std::for_each(print_directory.begin(), print_directory.end(),
                  [this](const auto& a) { out << a; });
    out << (this->correction ? lmt::aux::corrected_layout : "\\layout {}\n");
    out << "}" << newline;
}
