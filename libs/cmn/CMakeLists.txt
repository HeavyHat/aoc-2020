file(GLOB utils_sources CONFIGURE_DEPENDS *.cpp)

add_library(commonutils STATIC
    ${utils_sources}
    )

target_link_libraries(commonutils PUBLIC
    pthread
    CONAN_PKG::fmt
    )

target_include_directories(commonutils PUBLIC
    .
    )
