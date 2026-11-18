cmake_minimum_required(VERSION 3.16)
project(Raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(raytracer
    src/math/vector.cpp
    src/ray/ray.cpp
    src/geometry/sphere.cpp
)
target_include_directories(raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

enable_testing()
add_executable(test_vector tests/math/test_vector.cpp)
target_link_libraries(test_vector PRIVATE raytracer)
add_test(NAME vector_tests COMMAND test_vector)
