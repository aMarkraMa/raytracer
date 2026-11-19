#include <cmath>
#include <cstdlib>
#include <iostream>

#include "math/vector.h"
#include "render/camera.h"

namespace {

bool nearly_equal(double a, double b) {
    return std::fabs(a - b) < 1e-9;
}

void expect_direction(
    const char* name,
    const Vector& actual,
    double expected_x,
    double expected_y,
    double expected_z,
    int& failures
) {
    if (nearly_equal(actual.x(), expected_x)
        && nearly_equal(actual.y(), expected_y)
        && nearly_equal(actual.z(), expected_z)) {
        std::cout << "PASS: " << name << '\n';
        return;
    }

    ++failures;
    std::cout << "FAIL: " << name
              << " got (" << actual.x() << ", " << actual.y() << ", " << actual.z() << ")"
              << " expected (" << expected_x << ", " << expected_y << ", " << expected_z << ")\n";
}

}  // namespace

int main() {
    int failures = 0;
    Camera camera(Vector(0.0, 0.0, 0.0));

    Vector center = camera.rayThroughPixel(2, 1, 5, 3, 5.0).direction();
    expect_direction("5x3 screenWidth 5 center (2,1)", center, 0.0, 0.0, 1.0, failures);

    Vector topRight = camera.rayThroughPixel(4, 0, 5, 3, 5.0).direction();
    expect_direction("5x3 screenWidth 5 top-right (4,0)", topRight, 2.0, 1.0, 1.0, failures);

    // Course note had z = -1 here; with a screen in front of the camera at +z the consistent value is +1.
    Vector bottomLeft = camera.rayThroughPixel(0, 2, 5, 3, 5.0).direction();
    expect_direction("5x3 screenWidth 5 bottom-left (0,2)", bottomLeft, -2.0, -1.0, 1.0, failures);

    Vector wideCenter = camera.rayThroughPixel(255, 127, 512, 256, 2.0).direction();
    expect_direction(
        "512x256 screenWidth 2 near-center (255,127)",
        wideCenter,
        -1.0 / 512.0,
        1.0 / 512.0,
        1.0,
        failures
    );

    Vector wideTopLeft = camera.rayThroughPixel(0, 0, 512, 256, 2.0).direction();
    expect_direction(
        "512x256 screenWidth 2 top-left (0,0)",
        wideTopLeft,
        -511.0 / 512.0,
        255.0 / 512.0,
        1.0,
        failures
    );

    if (failures != 0) {
        std::cout << failures << " test(s) failed\n";
        return EXIT_FAILURE;
    }

    std::cout << "All tests passed\n";
    return EXIT_SUCCESS;
}
