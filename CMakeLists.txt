cmake_minimum_required(VERSION 3.15)

# set the project name
project(mxl2ly LANGUAGES CXX)

# set the cmake standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the tinyxml2 directory
add_subdirectory(tinyxml2)
add_subdirectory(tclap)

# set the sources
set (SOURCES
    main.cpp
)

# add the executable
add_executable(mxl2ly
    ${SOURCES}
)

# link the library to the executable
target_link_libraries(
    mxl2ly PUBLIC tinyxml2
)

target_link_libraries(
    mxl2ly PUBLIC tclap
)

target_include_directories(
    mxl2ly PUBLIC "${PROJECT_SOURCE_DIR}"
)

# State that we want all the warnings
if (MSVC)
add_compile_options(/W4 /WX) # warning level 4 and all warnings as errors
else()
add_compile_options(-Wall -Wextra -pedantic -Werror) # lots of warnings and all warnings as errors
endif()
