#include <cmath>
#include <cstdlib>
#include <iostream>

#include "colour/colour.h"
#include "render/image.h"

namespace {

bool nearly_equal(double a, double b) {
    return std::fabs(a - b) < 1e-9;
}

bool colour_equal(const Colour& a, const Colour& b) {
    return nearly_equal(a.r(), b.r()) && nearly_equal(a.g(), b.g()) && nearly_equal(a.b(), b.b());
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

    Image image(5, 4);
    Colour red(1.0, 0.0, 0.0);
    image.setPixel(3, 2, red);

    expect_colour("setPixel(3,2) is red", image.pixel(3, 2), red, failures);
    expect_colour("other pixel (0,0) stays black", image.pixel(0, 0), Colour(0.0, 0.0, 0.0), failures);
    expect_colour("other pixel (4,3) stays black", image.pixel(4, 3), Colour(0.0, 0.0, 0.0), failures);

    if (failures != 0) {
        std::cout << failures << " test(s) failed\n";
        return EXIT_FAILURE;
    }

    std::cout << "All tests passed\n";
    return EXIT_SUCCESS;
}
