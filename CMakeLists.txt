cmake_minimum_required (VERSION 2.8.11)
project (Captcha3D)

add_executable(
    captcha-3d
    src/main.c
    src/zbuffer.c
    src/illumination.c
    src/transformations.c
    src/param.c
)

target_link_libraries(captcha-3d m opencv_core opencv_highgui opencv_imgproc)
