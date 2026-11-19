#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>

#include "colour/colour.h"
#include "geometry/plane.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "material/flat_shader.h"
#include "math/vector.h"
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

Colour material_colour(const HitInfo& hit) {
    // FlatShader::shade ignores lighting and returns its stored colour.
    return hit.material->shade(hit.normal, Vector(0.0, 0.0, -1.0));
}

}  // namespace

int main() {
    int failures = 0;
    Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));

    FlatShader red(Colour(1.0, 0.0, 0.0));
    FlatShader blue(Colour(0.0, 0.0, 1.0));

    // Sphere alone: hit at t = 5 (point z = 4).
    {
        Scene scene(Vector(0.0, 0.0, -1.0));
        scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 9.0), 5.0, red));
        std::optional<HitInfo> hit = scene.nearestHit(ray);
        expect_true("sphere alone hits", hit.has_value(), failures);
        if (hit.has_value()) {
            expect_true("sphere alone t = 5", nearly_equal(hit->t, 5.0), failures);
            expect_true(
                "sphere alone material is red",
                colour_equal(material_colour(*hit), Colour(1.0, 0.0, 0.0)),
                failures
            );
        }
    }

    // Sphere then nearer blue plane at z = 2: plane wins at t = 3.
    {
        Scene scene(Vector(0.0, 0.0, -1.0));
        scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 9.0), 5.0, red));
        scene.add(std::make_unique<Plane>(Vector(0.0, 0.0, 2.0), Vector(0.0, 0.0, -1.0), blue));
        std::optional<HitInfo> hit = scene.nearestHit(ray);
        expect_true("nearer plane hits", hit.has_value(), failures);
        if (hit.has_value()) {
            expect_true("nearer plane t = 3", nearly_equal(hit->t, 3.0), failures);
            expect_true(
                "nearer plane material is blue",
                colour_equal(material_colour(*hit), Colour(0.0, 0.0, 1.0)),
                failures
            );
        }
    }

    // Sphere then farther blue plane at z = 20: sphere wins at t = 5.
    {
        Scene scene(Vector(0.0, 0.0, -1.0));
        scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 9.0), 5.0, red));
        scene.add(std::make_unique<Plane>(Vector(0.0, 0.0, 20.0), Vector(0.0, 0.0, -1.0), blue));
        std::optional<HitInfo> hit = scene.nearestHit(ray);
        expect_true("farther plane keeps sphere", hit.has_value(), failures);
        if (hit.has_value()) {
            expect_true("farther plane case t = 5", nearly_equal(hit->t, 5.0), failures);
            expect_true(
                "farther plane case material is red",
                colour_equal(material_colour(*hit), Colour(1.0, 0.0, 0.0)),
                failures
            );
        }
    }

    // Only a sphere off to the side: miss.
    {
        Scene scene(Vector(0.0, 0.0, -1.0));
        scene.add(std::make_unique<Sphere>(Vector(6.0, 0.0, 9.0), 5.0, red));
        std::optional<HitInfo> hit = scene.nearestHit(ray);
        expect_true("off-axis sphere misses", !hit.has_value(), failures);
    }

    if (failures != 0) {
        std::cout << failures << " test(s) failed\n";
        return EXIT_FAILURE;
    }

    std::cout << "All tests passed\n";
    return EXIT_SUCCESS;
}
