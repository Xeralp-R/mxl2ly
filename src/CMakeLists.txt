cmake_minimum_required(VERSION 3.15)

target_sources(mxl2ly
PRIVATE
    file_option_parser.hpp
    file_option_parser.cpp
    header_and_paper.hpp
    header_and_paper.cpp
    helper.hpp
    measure_auxiliary.hpp
    music_tree.hpp
    music_tree.cpp
    note.hpp
    note.cpp
    note_auxiliary.hpp
    statement.hpp
    part_and_measure.hpp
    part_and_measure.cpp
)
