#include "material/lambert_shader.h"
#include "geometry/hit_info.h"
#include "light/light.h"
#include <algorithm>

LambertShader::LambertShader(const Colour& colour) : _colour(colour) {}

Colour LambertShader::shade(const HitInfo& hit, const Light& light) {
    Vector toLight = (light.position() - hit.point).normalised();
    double intensity = std::max(0.0, hit.normal.dot(toLight));
    return _colour * intensity;
}
