#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "geometry/hit_info.h"
#include "geometry/ray.h"
#include "geometry/shape.h"
#include "math/vector.h"

class Scene {
public:
    explicit Scene(const Vector& toLight);

    const Vector& toLight() const;
    void add(std::unique_ptr<Shape> shape);
    std::optional<HitInfo> nearestHit(const Ray& ray) const;

private:
    std::vector<std::unique_ptr<Shape>> _shapes;
    Vector _toLight;
};
