//
//  file_option_parser.hpp
//  mxl2ly
//
//  Created by Reventar on 10/11/2021.
//

#ifndef file_option_parser_hpp
#define file_option_parser_hpp

#include <iostream>
#include <optional>
#include <string>

#include "tclap/CmdLine.h"

class FileOptionParser {
public:
    FileOptionParser(int argc, char **argv);
    
    std::string get_filename() { return this->filename; }
    std::optional<std::string> get_outfilename() { return this->outfilename; }
    
private:
    std::string filename;
    std::optional<std::string> outfilename;
};

#endif /* file_option_parser_hpp */
