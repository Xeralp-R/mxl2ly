set (HEADERS
    json.hpp
)

add_library(nlohmann INTERFACE
    ${HEADERS}
)

set_target_properties(nlohmann PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(
    nlohmann INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}"
)
