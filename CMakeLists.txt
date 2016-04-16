cmake_minimum_required (VERSION 2.8.11)
project (Captcha3D)

set(SOURCE_FILES
    src/captcha3d.c
    src/zbuffer.c
    src/illumination.c
    src/transformations.c
    src/file.c
    src/arial.c
    src/param.c
)

set (CMAKE_C_FLAGS "--std=c99 ${CMAKE_C_FLAGS}")

add_library(captcha3d STATIC ${SOURCE_FILES})

add_executable(launcher src/main.c)

add_custom_target(
    beautify
    COMMAND astyle --style=kr --add-brackets --pad-oper --pad-header ${CMAKE_SOURCE_DIR}/src/*
)

target_link_libraries(launcher captcha3d m png opencv_core opencv_highgui opencv_imgproc)
