get_filename_component(name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
file(GLOB source_files *.cpp)
add_executable(${name}
        ${source_files}
    )

target_link_libraries(${name} PUBLIC
    commonutils
    CONAN_PKG::fmt
    CONAN_PKG::ctre
    CONAN_PKG::cxxopts
    pthread
    )

set_target_properties(${name} PROPERTIES SUFFIX ".tsk" OUTPUT_NAME
    "excercise-${name}")
