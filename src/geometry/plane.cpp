#include "geometry/plane.h"

#include <cmath>

Plane::Plane(const Vector& point, const Vector& normal, Material& material)
    : _point(point), _normal(normal.normalised()), _material(material) {}

const Vector& Plane::point() const {
    return _point;
}

const Vector& Plane::normal() const {
    return _normal;
}

Material& Plane::material() const {
    return _material;
}

std::optional<HitInfo> Plane::hit(const Ray& ray) const {
    double denom = ray.direction().dot(_normal);
    if (std::fabs(denom) < 1e-9) {
        return std::nullopt;
    }

    double t = (_point - ray.origin()).dot(_normal) / denom;
    if (t <= 0.0) {
        return std::nullopt;
    }

    Vector point = ray.at(t);
    return HitInfo{t, point, _normal, &_material};
}
