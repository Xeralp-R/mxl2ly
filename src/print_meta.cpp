//
//  print_lilypond.cpp
//  mxl2ly
//
//  Created by Reventar on 15/12/2021.
//

#include "music_tree.hpp"

#include <vector>
#include <string_view>
#include <memory>
#include <iostream>
#include <fstream>

#include "header_and_paper.hpp"
#include "fmt/format.h"

using namespace lmt;

void MusicTree::print_staff_info() {
    auto staff_width = dynamic_cast<Statement<Length>*>(statements.at(1).get())->get_content();
    
    out << "#(set-global-staff-size ";
    out << staff_width.get_points();
    out << ")\n\n";
}

void MusicTree::print_paper_block() {
    // get the paper pointer
    auto paper_ptr = dynamic_cast<Paper*>(statements.at(2).get());
    
    // Prepare the page size
    out << R"||(#(set! paper-alist )||" << newline << tab;
    out << fmt::format(R"||((cons '("new_size" . (cons (* {0} mm) )||",
                       paper_ptr->get_height().get_millimeters());
    out << fmt::format(R"||((* {0} mm))) paper-alist)))||",
                       paper_ptr->get_width().get_millimeters()) << newline;
    
    // Output the actual paper thing
    out << R"(\paper {)" << newline;
    out << tab << R"||(#(set-paper-size "new_size"))||" << newline;
    out << tab << fmt::format(R"||(top-margin = {0}\mm)||",
                              paper_ptr->get_margin(Paper::Margins::TopMargin)
                              .get_millimeters()) << newline;
    out << tab << fmt::format(R"||(bottom-margin = {0}\mm)||",
                              paper_ptr->get_margin(Paper::Margins::BottomMargin)
                              .get_millimeters()) << newline;
    out << tab << fmt::format(R"||(left-margin = {0}\mm)||",
                              paper_ptr->get_margin(Paper::Margins::LeftMargin)
                              .get_millimeters()) << newline;
    out << tab << fmt::format(R"||(right-margin = {0}\mm)||",
                              paper_ptr->get_margin(Paper::Margins::RightMargin)
                              .get_millimeters()) << newline;
    out << tab << R"||(ragged-last-bottom = ##f)||" << newline;
    out << "}" << newline << newline;
}

void MusicTree::print_header_block() {
    auto header_ptr = dynamic_cast<Header*>(statements.at(3).get());
    
    out << R"||(\header {)||" << newline;
    for (auto pair : header_ptr->get_statements()) {
        out << tab << fmt::format(R"||({0} = "{1}")||",
                                  pair.first, pair.second) << newline;
    }
    out << "}" << newline << newline;
}
