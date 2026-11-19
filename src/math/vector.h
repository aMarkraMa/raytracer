#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

class Vector {
public:
    Vector();
    Vector(double x, double y, double z);

    double x() const;
    double y() const;
    double z() const;

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double scalar) const;

    double dot(const Vector& other) const;
    double length() const;
    Vector normalised() const;

    friend Vector operator*(double scalar, const Vector& vector);

private:
    double _x;
    double _y;
    double _z;
};

#endif
