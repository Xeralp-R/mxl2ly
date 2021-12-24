cmake_minimum_required(VERSION 3.15)

set (HEADERS
    args.h
    chrono.h
    color.h
    compile.h
    core.h
    format-inl.h
    format.h
    os.h
    ostream.h
    printf.h
    ranges.h
    xchar.h
    )

set (SOURCES
    format.cc
    os.cc
    )

add_library(fmt-lib ${SOURCES} ${HEADERS})

target_include_directories(fmt-lib PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
target_include_directories(fmt-lib PUBLIC "${CMAKE_SOURCE_DIR}/lib")
