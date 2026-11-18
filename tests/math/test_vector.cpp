#include <cmath>
#include <cstdlib>
#include <iostream>

#include "math/vector.h"

namespace {

bool nearly_equal(double a, double b) {
    return std::fabs(a - b) < 1e-9;
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

}  // namespace

int main() {
    int failures = 0;

    Vector sum = Vector(1.0, 2.0, 3.0) + Vector(4.0, 5.0, 6.0);
    expect_components("addition with +", sum, 5.0, 7.0, 9.0, failures);

    Vector difference = Vector(-1.0, 4.0, 0.0) - Vector(-5.0, 2.0, 1.0);
    expect_components("subtraction with -", difference, 4.0, 2.0, -1.0, failures);

    Vector left_scaled = 2.0 * Vector(1.0, -2.0, 3.0);
    expect_components("left scalar multiply 2 * v", left_scaled, 2.0, -4.0, 6.0, failures);

    Vector right_scaled = Vector(1.0, -2.0, 3.0) * 2.0;
    expect_components("right scalar multiply v * 2", right_scaled, 2.0, -4.0, 6.0, failures);

    if (failures != 0) {
        std::cout << failures << " test(s) failed\n";
        return EXIT_FAILURE;
    }

    std::cout << "All tests passed\n";
    return EXIT_SUCCESS;
}
