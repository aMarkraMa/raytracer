#include "geometry/sphere.h"

#include <algorithm>
#include <cmath>

Sphere::Sphere(const Vector& center, double radius, Material& material)
    : _center(center), _radius(radius), _material(material) {}

const Vector& Sphere::center() const {
    return _center;
}

double Sphere::radius() const {
    return _radius;
}

Material& Sphere::material() const {
    return _material;
}

std::optional<HitInfo> Sphere::hit(const Ray& ray) const {
    Vector D = ray.direction();
    Vector O = ray.origin();
    Vector L = O - _center;

    double a = D.dot(D);
    double b = 2.0 * D.dot(L);
    double c = L.dot(L) - _radius * _radius;

    double delta = b * b - 4.0 * a * c;
    if (delta < 0.0) {
        return std::nullopt;
    }

    double sqrtDelta = std::sqrt(delta);
    double t1 = (-b - sqrtDelta) / (2.0 * a);
    double t2 = (-b + sqrtDelta) / (2.0 * a);

    double t = -1.0;
    if (t1 > 0.0 && t2 > 0.0) {
        t = std::min(t1, t2);
    } else if (t1 > 0.0) {
        t = t1;
    } else if (t2 > 0.0) {
        t = t2;
    }

    if (t <= 0.0) {
        return std::nullopt;
    }

    Vector point = ray.at(t);
    Vector normal = (point - _center).normalised();
    return HitInfo{t, point, normal, &_material};
}
