#include "render/camera.h"

#include <optional>

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
        return Colour(0.0, 0.0, 0.0);
    }
    return hit->material->shade(hit->normal, scene.toLight());
}

Image Camera::render(const Scene& scene, int width, int height) const {
    Image image(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
    const double screenWidth = 2.0;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Ray ray = rayThroughPixel(
                static_cast<unsigned int>(x),
                static_cast<unsigned int>(y),
                static_cast<unsigned int>(width),
                static_cast<unsigned int>(height),
                screenWidth
            );
            image.setPixel(
                static_cast<unsigned int>(x),
                static_cast<unsigned int>(y),
                trace(ray, scene)
            );
        }
    }

    return image;
}
