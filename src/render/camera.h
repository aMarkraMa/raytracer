#pragma once

#include "colour/colour.h"
#include "geometry/ray.h"
#include "light/light.h"
#include "math/vector.h"
#include "scene/scene.h"

class Camera {
public:
    Camera(const Vector& position);

    const Vector& position() const;

    Ray rayThroughCenter() const;
    Ray rayThroughPixel(
        unsigned int x,
        unsigned int y,
        unsigned int imageWidth,
        unsigned int imageHeight,
        double screenWidth
    ) const;

    Colour trace(const Ray& ray, const Scene& scene) const;

private:
    Vector _position;
};
