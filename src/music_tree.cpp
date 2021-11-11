//
//  music_tree.cpp
//  mxl2ly
//
//  Created by Reventar on 11/11/2021.
//

#include "music_tree.hpp"


MusicTree::MusicTree(std::string filename) { 
    this->xml_document.LoadFile(filename.c_str());
    std::cout << "Loaded file in class!" << std::endl;
}
