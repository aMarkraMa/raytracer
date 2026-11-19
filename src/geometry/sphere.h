#pragma once

#include <optional>

#include "geometry/hit_info.h"
#include "geometry/ray.h"
#include "geometry/shape.h"
#include "material/material.h"
#include "math/vector.h"

class Sphere : public Shape {
public:
    Sphere(const Vector& center, double radius, Material& material);

    const Vector& center() const;
    double radius() const;
    Material& material() const;

    std::optional<HitInfo> hit(const Ray& ray) const override;

private:
    Vector _center;
    double _radius;
    Material& _material;
};
