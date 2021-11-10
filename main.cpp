#include <iostream>
#include <exception>
#include <string>
#include <fstream>

#include "tinyxml2/tinyxml2.h"
#include "tclap/CmdLine.h"

int main(int argc, char* argv[]) {
    try {
        // Declare the command line.
        TCLAP::CmdLine cmd("A program to convert musicxml to lilypond.", ' ', "beta");
        
        // Add the filename as mandatory
        TCLAP::UnlabeledValueArg<std::string> filename_arg("filename",
                                                           "The name of the file being converted",
                                                           true,
                                                           "",
                                                           "string" );
        
        // Add the output name as optional
        TCLAP::ValueArg<std::string> output_arg("o",
                                                "output",
                                                "The name of the file to output to: default is based on the input filename",
                                                false,
                                                "",
                                                "string");
        
        // add those arguments
        cmd.add(filename_arg);
        cmd.add(output_arg);
        
        // Parse the command-line arguments.
        cmd.parse(argc, argv);
        std::string filename = filename_arg.getValue();
        
        std::fstream filestr;
        filestr.open(filename, std::ios::in);
        
        if (filestr.is_open()) {
            std::cout << "Opened file" << std::endl;
        }
        else {
            std::cout << "File was not opened" << std::endl;
        }
    }
    catch (TCLAP::ArgException &e) {
        std::cerr << "Error: " << e.error() << " for arg " << e.argId() << std::endl;
        exit(1);
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(2);
    }
    catch (...) {
        std::cerr << "Unknown error occured. Terminating." << std::endl;
        exit(3);
    }
}
