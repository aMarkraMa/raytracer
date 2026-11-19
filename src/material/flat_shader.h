#pragma once

#include "material/material.h"
#include "colour/colour.h"

class FlatShader : public Material {
private:
    Colour _colour;

public:
    FlatShader(const Colour& colour);
    Colour shade(const HitInfo& hit, const Light& light) override;
};
