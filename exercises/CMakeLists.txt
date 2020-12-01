if(NOT DEFINED AOC_EXERCISE)
    message(FATAL "Please set the AOC_EXERCISE variable to compile a particule
    exercise.")
else()
    add_subdirectory(${AOC_EXERCISE})
endif()
