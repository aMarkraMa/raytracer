#pragma once

#include <optional>

#include "geometry/hit_info.h"
#include "geometry/ray.h"

// Abstract shape: the renderer only needs hit(), not Sphere/Plane details.
class Shape {
public:
    virtual ~Shape() = default;

    // Nearest hit in front of the ray origin (t > 0), with a unit normal.
    virtual std::optional<HitInfo> hit(const Ray& ray) const = 0;
};
