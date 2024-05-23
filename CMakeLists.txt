cmake_minimum_required(VERSION 3.8)

project(VSMP)

add_compile_options(
  "-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
  "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET
    libavdevice
    libavfilter
    libavformat
    libavcodec
    libswresample
    libswscale
    libavutil
)

add_executable(${PROJECT_NAME} main.c dither.h dither.c)

target_link_libraries(${PROJECT_NAME}
    PkgConfig::LIBAV
    SDL2
    SDL2_image
)
