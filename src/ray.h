#pragma once

#include "vector3.h"

class Ray {
public:
    Ray() {}
    Ray(const Point3D& origin, const Vector3& direction): _origin(origin), _direction(direction) {}

    Point3D origin() const { return _origin; }
    Vector3 direction() const { return _direction; }

    Point3D at(double t) const {
        return _origin + t * _direction;
    }

private:
    Point3D _origin;
    Vector3 _direction;
};
