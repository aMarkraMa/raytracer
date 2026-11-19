#pragma once
#include "math/vector.h"
#include "colour/colour.h"

class Light {
private:
    Vector _position;
    Colour _colour;

public:
    Light(const Vector& position, const Colour& colour);

    const Vector& position() const;
    const Colour& colour() const;
};
