set (HEADERS
    filesystem.hpp
    fs_fwd.hpp
    fs_impl.hpp
    fs_std_fwd.hpp
    fs_std_impl.hpp
    fs_std.hpp
)

add_library(ghc INTERFACE
    ${HEADERS}
)

set_target_properties(ghc PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(ghc INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
