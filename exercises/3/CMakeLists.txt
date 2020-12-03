get_filename_component(name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
file(GLOB source_files *.cpp)
add_executable(${name}
        ${source_files}
    )

target_link_libraries(${name} PUBLIC
    CONAN_PKG::fmt
    utils
    pthread
    )

set_target_properties(${name} PROPERTIES SUFFIX ".tsk" OUTPUT_NAME
    "excercise-${name}")
