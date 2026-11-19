#include "scene/scene.h"

Scene::Scene(const Vector& toLight) : _toLight(toLight) {}

const Vector& Scene::toLight() const {
    return _toLight;
}

void Scene::add(std::unique_ptr<Shape> shape) {
    _shapes.push_back(std::move(shape));
}

std::optional<HitInfo> Scene::nearestHit(const Ray& ray) const {
    std::optional<HitInfo> nearest;
    for (const std::unique_ptr<Shape>& shape : _shapes) {
        std::optional<HitInfo> hit = shape->hit(ray);
        if (hit && (!nearest || hit->t < nearest->t)) {
            nearest = hit;
        }
    }
    return nearest;
}
