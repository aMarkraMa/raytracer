#pragma once

#include "colour/colour.h"
#include "material/material.h"
#include "math/vector.h"

class LambertShader : public Material {
public:
    LambertShader(const Colour& colour);
    Colour shade(const Vector& normal, const Vector& toLight) override;

private:
    Colour _colour;
};
