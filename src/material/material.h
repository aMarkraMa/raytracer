#pragma once

#include "colour/colour.h"
#include "math/vector.h"

class Material {
public:
    virtual ~Material() = default;
    virtual Colour shade(const Vector& normal, const Vector& toLight) = 0;
};
