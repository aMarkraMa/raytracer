#pragma once

#include "colour/colour.h"

struct HitInfo;
class Light;

class Material {
public:
    virtual ~Material() = default;
    virtual Colour shade(const HitInfo& hit, const Light& light) = 0;
};
