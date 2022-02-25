#include <exception>
#include <fstream>
#include <iostream>
#include <string>

#include "ghc/filesystem.hpp"

#include "src/file_option_parser.hpp"
#include "src/music_tree.hpp"
#include "src/formatter.hpp"

int main(int argc, char* argv[]) {
    try {
        FileOptionParser file_option_parser(argc, argv);
        std::string      filename = file_option_parser.get_filename();

        if (!ghc::filesystem::exists(filename)) {
            throw std::invalid_argument("File cannot be found");
        }

        { // placed in a block to prevent too much memory use
            lmt::MusicTree music_tree;
            music_tree.accept_musicxml(filename);
            music_tree.set_corrections(file_option_parser.get_hypercorrect());
            music_tree.print_lilypond(file_option_parser.get_outfilename());
        }

        lmt::Formatter formatter(file_option_parser.get_format_options());
        formatter.format_file(file_option_parser.get_outfilename());
    } catch (TCLAP::ArgException& e) {
        std::cerr << "Error: " << e.error() << " for arg " << e.argId()
                  << std::endl;
        exit(1);
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(2);
    } catch (...) {
        std::cerr << "Unknown error ocurred. Terminating." << std::endl;
        exit(3);
    }
}
