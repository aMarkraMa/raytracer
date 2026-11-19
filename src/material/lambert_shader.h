#pragma once

#include "material/material.h"
#include "colour/colour.h"

class LambertShader : public Material {
private:
    Colour _colour;

public:
    LambertShader(const Colour& colour);
    Colour shade(const HitInfo& hit, const Light& light) override;
};
