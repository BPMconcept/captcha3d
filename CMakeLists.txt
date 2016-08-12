cmake_minimum_required (VERSION 3.1)
project (Captcha3D VERSION 1.0 LANGUAGES C)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif()

# Static library
add_library(captcha3d STATIC
    lib/captcha3d.c
    lib/zbuffer.c
    lib/transformations.c
    lib/file.c
    lib/image.c
    lib/font.c
    lib/vector.c
    lib/color.c
    lib/letter.c)

target_compile_features(captcha3d PRIVATE c_variadic_macros)
target_link_libraries(captcha3d m png)
target_include_directories(captcha3d PUBLIC lib)

# Standalone Captcha3D executable
add_executable(launcher src/main.c)
target_link_libraries(launcher PRIVATE captcha3d)

# Beautify command
add_custom_target(
    beautify
    COMMAND astyle --style=kr --add-brackets --pad-oper --pad-header ${CMAKE_SOURCE_DIR}/src/*
)

