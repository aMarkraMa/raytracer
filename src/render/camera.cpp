#include "camera/camera.h"

Camera::Camera(const Vector& position) : _position(position) {}

const Vector& Camera::position() const {
    return _position;
}

Ray Camera::rayThroughCenter() {
    Vector direction(0, 0, 1); // Assuming the camera looks along the z-axis
    return Ray(_position, direction);
}