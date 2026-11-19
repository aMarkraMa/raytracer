#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>

#include "colour/colour.h"
#include "geometry/sphere.h"
#include "material/flat_shader.h"
#include "material/lambert_shader.h"
#include "math/vector.h"
#include "render/camera.h"
#include "render/image.h"
#include "scene/scene.h"

namespace {

bool nearly_equal(double a, double b) {
    return std::fabs(a - b) < 1e-9;
}

bool colour_equal(const Colour& a, const Colour& b) {
    return nearly_equal(a.r(), b.r()) && nearly_equal(a.g(), b.g()) && nearly_equal(a.b(), b.b());
}

void expect_true(const char* name, bool value, int& failures) {
    if (value) {
        std::cout << "PASS: " << name << '\n';
        return;
    }
    ++failures;
    std::cout << "FAIL: " << name << '\n';
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

void expect_colour(
    const char* name,
    const Colour& actual,
    const Colour& expected,
    int& failures
) {
    if (colour_equal(actual, expected)) {
        std::cout << "PASS: " << name << '\n';
        return;
    }

    ++failures;
    std::cout << "FAIL: " << name
              << " got (" << actual.r() << ", " << actual.g() << ", " << actual.b() << ")"
              << " expected (" << expected.r() << ", " << expected.g() << ", " << expected.b()
              << ")\n";
}

}  // namespace

int main() {
    int failures = 0;
    Camera camera(Vector(0.0, 0.0, 0.0));

    Vector center = camera.rayThroughPixel(2, 1, 5, 3, 5.0).direction();
    expect_direction("5x3 screenWidth 5 center (2,1)", center, 0.0, 0.0, 1.0, failures);

    Vector topRight = camera.rayThroughPixel(4, 0, 5, 3, 5.0).direction();
    expect_direction("5x3 screenWidth 5 top-right (4,0)", topRight, 2.0, 1.0, 1.0, failures);

    Vector bottomLeft = camera.rayThroughPixel(0, 2, 5, 3, 5.0).direction();
    expect_direction("5x3 screenWidth 5 bottom-left (0,2)", bottomLeft, -2.0, -1.0, 1.0, failures);

    // trace: flat sphere + same toLight as before → same colour
    FlatShader flat(Colour(0.2, 0.4, 0.8));
    Scene flatScene(Vector(0.0, 0.0, -1.0).normalised());
    flatScene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 9.0), 5.0, flat));
    Ray centerRay = camera.rayThroughCenter();
    expect_colour(
        "trace flat sphere colour",
        camera.trace(centerRay, flatScene),
        Colour(0.2, 0.4, 0.8),
        failures
    );

    // trace: lambert with sideways toLight → black
    LambertShader lambert(Colour(1.0, 0.0, 0.0));
    Scene litScene(Vector(1.0, 0.0, 0.0));
    litScene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 9.0), 5.0, lambert));
    expect_colour(
        "trace lambert sideways is black",
        camera.trace(centerRay, litScene),
        Colour(0.0, 0.0, 0.0),
        failures
    );

    // miss → black background
    Ray missRay(Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0));
    expect_colour(
        "trace miss is black",
        camera.trace(missRay, litScene),
        Colour(0.0, 0.0, 0.0),
        failures
    );

    // render builds an image with the same scene colours
    Image image = camera.render(flatScene, 5, 3);
    expect_true("render size width", image.width() == 5, failures);
    expect_true("render size height", image.height() == 3, failures);
    expect_colour(
        "render center pixel matches trace",
        image.pixel(2, 1),
        Colour(0.2, 0.4, 0.8),
        failures
    );

    if (failures != 0) {
        std::cout << failures << " test(s) failed\n";
        return EXIT_FAILURE;
    }

    std::cout << "All tests passed\n";
    return EXIT_SUCCESS;
}
