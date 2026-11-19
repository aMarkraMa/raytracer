#include "material/lambert_shader.h"

#include <algorithm>

LambertShader::LambertShader(const Colour& colour) : _colour(colour) {}

Colour LambertShader::shade(const Vector& normal, const Vector& toLight) {
    double intensity = std::max(0.0, normal.dot(toLight));
    return _colour * intensity;
}
