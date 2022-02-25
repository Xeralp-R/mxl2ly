//
//  file_option_parser.cpp
//  mxl2ly
//
//  Created by Reventar on 10/11/2021.
//

#include "file_option_parser.hpp"

FileOptionParser::FileOptionParser(int argc, char** argv) {
    // Declare the command line.
    TCLAP::CmdLine cmd("A program to convert musicxml to lilypond.", ' ',
                       "beta");

    // Add the filename as mandatory
    TCLAP::UnlabeledValueArg<std::string> filename_arg(
        "filename", "The name of the file being converted", true, "", "string");
    cmd.add(filename_arg);

    // Add the output name as optional
    TCLAP::ValueArg<std::string> output_arg(
        "o", "output",
        "The name of the file to output to: default is based on the input "
        "filename",
        false, "", "string");
    cmd.add(output_arg);

    TCLAP::SwitchArg is_hyper_correct(
        "c", "hyper-correct",
        "Add hyper-corrections based on the LSR, like grace echo correction ",
        cmd, false);

    TCLAP::ValueArg<std::string> format_arg(
        "f", "format", "Formatting options like indentation", false,
        "{format:true;indent:\"    \";}", "string: json-like");
    cmd.add(format_arg);

    // Parse the command-line arguments.
    cmd.parse(argc, argv);

    // Set the respective arguments
    this->filename = filename_arg.getValue();
    if (output_arg.isSet()) {
        this->outfilename = output_arg.getValue();
    } else {
        std::string temp  = filename_arg.getValue();
        this->outfilename = temp.substr(0, temp.find('.')) + ".ly";
    }
    this->format_options = format_arg.getValue();
    this->hypercorrect   = is_hyper_correct.getValue();
}
