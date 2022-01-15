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

#include "fmt/format.h"
#include "header_and_paper.hpp"
#include "part.hpp"

using namespace lmt;

std::string MusicTree::convert_number_names(const std::string test) const {
    std::string returner;
    for (auto ch : test) {
        // if ch is any number from 0 to 9
        if (ch - '0' >= 0 && ch - '9' <= 0) {
            returner += number_names.at(ch - '0');
        } else {
            returner += ch;
        }
    }
    return returner;
}

void MusicTree::print_staff_info() const {
    const auto staff_width =
        dynamic_cast<Statement<Length>*>(statements.at(0).get())->get_content();

    out << "#(set-global-staff-size ";
    out << staff_width.get_points();
    out << ")\n\n";
}

void MusicTree::print_paper_block() const {
    // get the paper pointer
    const auto paper_ptr = dynamic_cast<Paper*>(statements.at(1).get());

    // Prepare the page size
    out << R"||(#(set! paper-alist )||" << newline << tab;
    out << fmt::format(
               R"--((cons '("new_size" . (cons (* {0} mm) (* {1} mm))) paper-alist)))--",
               paper_ptr->get_width().get_millimeters(),
               paper_ptr->get_height().get_millimeters())
        << newline;

    // Output the actual paper thing
    out << R"(\paper {)" << newline;
    out << tab << R"||(#(set-paper-size "new_size"))||" << newline;
    out << tab
        << fmt::format(R"||(top-margin = {0}\mm)||",
                       paper_ptr->get_margin(Paper::Margins::TopMargin)
                           .get_millimeters())
        << newline;
    out << tab
        << fmt::format(R"||(bottom-margin = {0}\mm)||",
                       paper_ptr->get_margin(Paper::Margins::BottomMargin)
                           .get_millimeters())
        << newline;
    out << tab
        << fmt::format(R"||(left-margin = {0}\mm)||",
                       paper_ptr->get_margin(Paper::Margins::LeftMargin)
                           .get_millimeters())
        << newline;
    out << tab
        << fmt::format(R"||(right-margin = {0}\mm)||",
                       paper_ptr->get_margin(Paper::Margins::RightMargin)
                           .get_millimeters())
        << newline;
    out << tab << R"||(ragged-last-bottom = ##f)||" << newline;
    out << "}" << newline << newline;
}

void MusicTree::print_header_block() const {
    const auto header_ptr = dynamic_cast<Header*>(statements.at(2).get());

    out << R"||(\header {)||" << newline;
    for (auto pair : header_ptr->get_statements()) {
        out << tab << fmt::format(R"||({0} = "{1}")||", pair.first, pair.second)
            << newline;
    }
    out << "}" << newline << newline;
}

void MusicTree::print_part_list() const {
    const auto list_ptr = dynamic_cast<PartList*>(statements.at(3).get());

    out << R"||(\score {)||" << newline;
    for (auto pair : list_ptr->get_parts()) {
        out << tab << R"||(\new Staff \with {)||" << newline;
        out << tab << tab << R"||(instrumentName = ")||" << pair.second
            << R"||(")||" << newline;
        out << tab << R"||(} \part-)||" << convert_number_names(pair.first)
            << newline;
    }
    out << "}" << newline;
}
