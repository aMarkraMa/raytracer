#pragma once

#include "math/vector.h"
#include "material/material.h"

struct HitInfo {
    double t;
    Vector point;
    Vector normal;
    Material* material;
};
