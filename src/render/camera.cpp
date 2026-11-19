#include "render/camera.h"

#include <optional>

#include "light/light.h"

Camera::Camera(const Vector& position) : _position(position) {}

const Vector& Camera::position() const {
    return _position;
}

Ray Camera::rayThroughCenter() const {
    return Ray(_position, Vector(0.0, 0.0, 1.0));
}

Ray Camera::rayThroughPixel(
    unsigned int x,
    unsigned int y,
    unsigned int imageWidth,
    unsigned int imageHeight,
    double screenWidth
) const {
    double pixelSize = screenWidth / static_cast<double>(imageWidth);
    double dirX = (static_cast<double>(x) + 0.5 - imageWidth / 2.0) * pixelSize;
    double dirY = (imageHeight / 2.0 - (static_cast<double>(y) + 0.5)) * pixelSize;
    return Ray(_position, Vector(dirX, dirY, 1.0));
}

Colour Camera::trace(const Ray& ray, const Scene& scene) const {
    std::optional<HitInfo> hit = scene.nearestHit(ray);
    if (!hit.has_value()) {
        return Colour(0.5, 0.7, 1.0);
    }

    // Temporary: shade still needs a Light; Scene currently only stores toLight.
    Light light(hit->point + scene.toLight(), Colour(1.0, 1.0, 1.0));
    return hit->material->shade(*hit, light);
}
