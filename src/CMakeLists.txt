cmake_minimum_required(VERSION 3.15)

target_sources(mxl2ly
PRIVATE
    chord.hpp
    chord.cpp
    corrector.hpp
    directions.hpp
    directions.cpp
    extract_meta.cpp
    file_option_parser.hpp
    file_option_parser.cpp
    formatter.hpp
    formatter.cpp
    header_and_paper.hpp
    header_and_paper.cpp
    helper.hpp
    measure.hpp
    measure.cpp
    measure_attributes.hpp
    measure_attributes.cpp
    measure_objects.hpp
    music_tree.hpp
    music_tree.cpp
    notations.hpp
    notations.cpp
    note.hpp
    note.cpp
    note_attributes.hpp
    note_attributes.cpp
    statement.hpp
    part.hpp
    part.cpp
    print_meta.cpp
)
