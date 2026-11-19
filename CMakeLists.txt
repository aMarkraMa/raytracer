cmake_minimum_required(VERSION 3.16)
project(Raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    lodepng
    GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
    GIT_TAG 7b2893e35891c0c85bee5595caafaf3c2044b409
)
FetchContent_MakeAvailable(lodepng)
if(NOT TARGET lodepng)
    add_library(lodepng STATIC ${lodepng_SOURCE_DIR}/lodepng.cpp)
    target_include_directories(lodepng PUBLIC ${lodepng_SOURCE_DIR})
endif()

add_library(raytracer
    src/math/vector.cpp
    src/geometry/ray.cpp
    src/geometry/sphere.cpp
    src/geometry/plane.cpp
    src/scene/scene.cpp
    src/colour/colour.cpp
    src/render/image.cpp
    src/render/camera.cpp
    src/io/png_saver.cpp
    src/light/light.cpp
    src/material/flat_shader.cpp
    src/material/lambert_shader.cpp
)
target_include_directories(raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(raytracer PUBLIC lodepng)

add_executable(raytracer_app src/main.cpp)
target_link_libraries(raytracer_app PRIVATE raytracer)
set_target_properties(raytracer_app PROPERTIES OUTPUT_NAME raytracer)

enable_testing()
add_subdirectory(tests)
