#include "material/flat_shader.h"
#include "geometry/hit_info.h"
#include "light/light.h"

FlatShader::FlatShader(const Colour& colour) : _colour(colour) {}

Colour FlatShader::shade(const HitInfo& hit, const Light& light) {
    return _colour;
}
