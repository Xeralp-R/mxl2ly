#include <iostream>
#include <exception>
#include <string>
#include <fstream>

#include "tinyxml2/tinyxml2.h"
#include "tclap/CmdLine.h"
#include "src/file_option_parser.hpp"

int main(int argc, char* argv[]) {
    try {
        FileOptionParser file_option_parser (argc, argv);
        std::string filename = file_option_parser.get_filename();
        
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
