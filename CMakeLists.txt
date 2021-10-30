cmake_minimum_required(VERSION 3.15)

# set the project name
project(ly2musicxml LANGUAGES CXX)

# set the cmake standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the sources
set (SOURCES
    main.cpp
)

# add the executable
add_executable(mxl2ly
    ${SOURCES}
)

# State that we want all the warnings
if (MSVC)
# warning level 4 and all warnings as errors
add_compile_options(/W4 /WX)
else()
# lots of warnings and all warnings as errors
add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()