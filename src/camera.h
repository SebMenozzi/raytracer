#pragma once

#include <cmath>

#include "vector3.h"
#include "ray.h"
#include "utils.h"

class Camera {
    public:
        Camera(
            Point3D lookfrom,
            Point3D lookat,
            Vector3 up,
            double fov,
            double aspect_ratio,
            double aperture,
            double focus_distance
        ) {
            auto theta = degrees_to_radians(fov);
            auto h = std::tan(theta / 2);
            auto viewport_height = 2.0 * h;
            auto viewport_width = aspect_ratio * viewport_height;

            _w = (lookfrom - lookat).unit_vector();
            _u = Vector3::cross_product(up, _w).unit_vector();
            _v = Vector3::cross_product(_w, _u);

            auto focal_length = 1.0;

            _origin = lookfrom;
            _horizontal = focus_distance * viewport_width * _u;
            _vertical = focus_distance * viewport_height * _v;
            _lower_left_corner = _origin - _horizontal / 2 - _vertical / 2 - focus_distance * _w;

            _lens_radius = aperture / 2;
        }

        Ray ray(double s, double t) const;

    private:
        Point3D _origin;
        Point3D _lower_left_corner;
        Vector3 _horizontal;
        Vector3 _vertical;
        Vector3 _u;
        Vector3 _v;
        Vector3 _w;
        double _lens_radius;
};

Ray Camera::ray(double s, double t) const {
    auto radius = _lens_radius * Vector3::random_in_unit_disk();
    auto offset = _u * radius.x() + _v * radius.y();

    return Ray(
        _origin + offset,
        _lower_left_corner + s * _horizontal + t * _vertical - _origin - offset
    );
}
