get_filename_component(name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
file(GLOB source_files *.cpp)
add_executable(${name}
        ${source_files}
    )

target_link_libraries(${name}
    CONAN_PKG::ctre
    utils
    pthread
    )

file(COPY "policies.txt" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set_target_properties(${name} PROPERTIES SUFFIX ".tsk" OUTPUT_NAME
    "excercise-${name}")
