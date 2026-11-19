#pragma once

#include <optional>

#include "geometry/hit_info.h"
#include "geometry/ray.h"
#include "geometry/shape.h"
#include "material/material.h"
#include "math/vector.h"

class Plane : public Shape {
public:
    Plane(const Vector& point, const Vector& normal, Material& material);

    const Vector& point() const;
    const Vector& normal() const;
    Material& material() const;

    std::optional<HitInfo> hit(const Ray& ray) const override;

private:
    Vector _point;
    Vector _normal;
    Material& _material;
};
