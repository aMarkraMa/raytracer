add_executable(test_vector math/test_vector.cpp)
target_link_libraries(test_vector PRIVATE raytracer)
add_test(NAME vector_tests COMMAND test_vector)

add_executable(test_image render/test_image.cpp)
target_link_libraries(test_image PRIVATE raytracer)
add_test(NAME image_tests COMMAND test_image)

add_executable(test_camera render/test_camera.cpp)
target_link_libraries(test_camera PRIVATE raytracer)
add_test(NAME camera_tests COMMAND test_camera)

add_executable(test_sphere geometry/test_sphere.cpp)
target_link_libraries(test_sphere PRIVATE raytracer)
add_test(NAME sphere_tests COMMAND test_sphere)

add_executable(test_scene scene/test_scene.cpp)
target_link_libraries(test_scene PRIVATE raytracer)
add_test(NAME scene_tests COMMAND test_scene)
