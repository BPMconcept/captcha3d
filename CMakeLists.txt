cmake_minimum_required (VERSION 2.8.11)
project (Captcha3D)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif()

set(SOURCE_FILES
    src/captcha3d.c
    src/zbuffer.c
    src/transformations.c
    src/file.c
    src/image.c
    src/font.c
    src/vector.c
    src/color.c
    src/letter.c
)

set (CMAKE_C_FLAGS "--std=c99 ${CMAKE_C_FLAGS}")

# Static library
add_library(captcha3d STATIC ${SOURCE_FILES})
target_link_libraries(captcha3d m png)

# Standalone Captcha3D executable
add_executable(launcher src/main.c)
target_link_libraries(launcher captcha3d)

# Beautify command
add_custom_target(
    beautify
    COMMAND astyle --style=kr --add-brackets --pad-oper --pad-header ${CMAKE_SOURCE_DIR}/src/*
)

