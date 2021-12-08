cmake_minimum_required(VERSION 3.15)

target_sources(mxl2ly
PRIVATE
    extract_music.cpp
    extract_paper_block.cpp
    file_option_parser.hpp
    file_option_parser.cpp
    header_and_paper.hpp
    header_and_paper.cpp
    helper.hpp
    measure.hpp
    measure.cpp
    measure_attributes.hpp
    measure_directions.hpp
    measure_objects.hpp
    music_tree.hpp
    music_tree.cpp
    note.hpp
    note.cpp
    note_auxiliary.hpp
    statement.hpp
    part.hpp
    part.cpp
)
