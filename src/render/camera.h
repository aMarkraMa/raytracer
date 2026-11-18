#pragma once
#include "math/vector.h"
#include "ray/ray.h"

class Camera {
private:
    Vector _position;

public:
    Camera(const Vector& position);

    const Vector& position() const;

    Ray rayThroughCenter();
};
