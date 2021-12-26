cmake_minimum_required(VERSION 3.15)

target_sources(mxl2ly
PRIVATE
    extract_meta.cpp
    extract_music.cpp
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
    statement.hpp
    part.hpp
    part.cpp
    print_meta.cpp
    print_music.cpp
)
