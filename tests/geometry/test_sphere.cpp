#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>

#include "colour/colour.h"
#include "geometry/plane.h"
#include "geometry/sphere.h"
#include "light/light.h"
#include "material/flat_shader.h"
#include "material/lambert_shader.h"
#include "math/vector.h"
#include "render/camera.h"
#include "scene/scene.h"

namespace {

bool nearly_equal(double a, double b) {
    return std::fabs(a - b) < 1e-9;
}

void expect_true(const char* name, bool value, int& failures) {
    if (value) {
        std::cout << "PASS: " << name << '\n';
        return;
    }
    ++failures;
    std::cout << "FAIL: " << name << '\n';
}

void expect_components(
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
    double expected_r,
    double expected_g,
    double expected_b,
    int& failures
) {
    if (nearly_equal(actual.r(), expected_r)
        && nearly_equal(actual.g(), expected_g)
        && nearly_equal(actual.b(), expected_b)) {
        std::cout << "PASS: " << name << '\n';
        return;
    }

    ++failures;
    std::cout << "FAIL: " << name
              << " got (" << actual.r() << ", " << actual.g() << ", " << actual.b() << ")"
              << " expected (" << expected_r << ", " << expected_g << ", " << expected_b << ")\n";
}

}  // namespace

int main() {
    int failures = 0;

    FlatShader flat(Colour(0.2, 0.4, 0.8));
    Sphere sphere(Vector(0.0, 0.0, 0.0), 1.0, flat);

    Ray missRay(Vector(0.0, 0.0, -5.0), Vector(0.0, 2.0, 1.0));
    expect_true("sphere miss returns nullopt", !sphere.hit(missRay).has_value(), failures);

    Ray hitRay(Vector(0.0, 0.0, -5.0), Vector(0.0, 0.0, 1.0));
    std::optional<HitInfo> hit = sphere.hit(hitRay);
    expect_true("sphere hit returns HitInfo", hit.has_value(), failures);
    if (hit.has_value()) {
        expect_components("closest hit point", hit->point, 0.0, 0.0, -1.0, failures);
        expect_components("outward normal", hit->normal, 0.0, 0.0, -1.0, failures);
        expect_true("sphere hit t is positive", hit->t > 0.0, failures);
    }

    FlatShader planeColour(Colour(0.1, 0.8, 0.1));
    Plane plane(Vector(0.0, -1.0, 0.0), Vector(0.0, 1.0, 0.0), planeColour);
    Ray planeRay(Vector(0.0, 0.0, -3.0), Vector(0.0, -1.0, 1.0));
    expect_true("plane hit returns HitInfo", plane.hit(planeRay).has_value(), failures);

    Shape& shapeRef = sphere;
    expect_true("sphere is usable as Shape", shapeRef.hit(hitRay).has_value(), failures);

    Camera camera(Vector(0.0, 0.0, -3.0));
    FlatShader sceneFlat(Colour(0.2, 0.4, 0.8));
    Scene scene(Vector(0.0, 0.0, -3.0));
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 0.0), 1.0, sceneFlat));

    Ray centerRay = camera.rayThroughCenter();
    Colour flatColour = camera.trace(centerRay, scene);
    expect_colour("flat shade via scene.trace", flatColour, 0.2, 0.4, 0.8, failures);

    LambertShader lambert(Colour(1.0, 0.0, 0.0));
    Scene litScene(Vector(10.0, 0.0, 0.0));
    litScene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 0.0), 1.0, lambert));

    Ray lambertRay(Vector(0.0, 0.0, -5.0), Vector(0.0, 0.0, 1.0));
    Colour shaded = camera.trace(lambertRay, litScene);
    expect_true("lambert shades hit to black when light is sideways", nearly_equal(shaded.r(), 0.0), failures);

    Ray skyRay = camera.rayThroughPixel(0, 0, 5, 3, 5.0);
    Colour sky = camera.trace(skyRay, litScene);
    expect_colour("miss uses background colour", sky, 0.5, 0.7, 1.0, failures);

    if (failures != 0) {
        std::cout << failures << " test(s) failed\n";
        return EXIT_FAILURE;
    }

    std::cout << "All tests passed\n";
    return EXIT_SUCCESS;
}
