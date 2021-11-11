#include <iostream>
#include <exception>
#include <string>
#include <fstream>

#include "tinyxml2/tinyxml2.h"
#include "ghc/filesystem.hpp"

#include "src/file_option_parser.hpp"

int main(int argc, char* argv[]) {
    try {
        FileOptionParser file_option_parser (argc, argv);
        std::string filename = file_option_parser.get_filename();
        
        if (!ghc::filesystem::exists(filename)) {
            throw std::invalid_argument("File cannot be found");
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
        std::cerr << "Unknown error ocurred. Terminating." << std::endl;
        exit(3);
    }
}
