cmake_minimum_required (VERSION 2.8.11)
project (Captcha3D)

set(SOURCE_FILES
    src/main.c
    src/zbuffer.c
    src/illumination.c
    src/transformations.c
    src/param.c
)

add_executable(captcha-3d ${SOURCE_FILES})

add_custom_target(
    beautify
    COMMAND astyle --style=kr --add-brackets --pad-oper --pad-header ${CMAKE_SOURCE_DIR}/src/*
)

target_link_libraries(captcha-3d m opencv_core opencv_highgui opencv_imgproc)
