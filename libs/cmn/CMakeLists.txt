file(GLOB utils_sources CONFIGURE_DEPENDS *.cpp)

add_library(utils STATIC
    ${utils_sources}
    )

target_link_libraries(utils PUBLIC
    pthread
    CONAN_PKG::fmt
    )

target_include_directories(utils PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/hh/aoc>
    )
