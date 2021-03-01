#pragma once

#include <cmath>

#include "utils/vector3.h"
#include "utils/utils.h"
#include "object/ray.h"

class Camera {
    public:
        Camera(
            Point3D lookfrom,
            Point3D lookat,
            Vector3 up,
            double fov,
            double aspect_ratio,
            double focus_distance
        ) {
            // http://ogldev.atspace.co.uk/www/tutorial12/tutorial12.html
            auto alpha = degrees_to_radians(fov / 2);
            auto vertical_distance = std::tan(alpha);
            auto viewport_height = 2.0 * vertical_distance;
            auto viewport_width = aspect_ratio * viewport_height;

            _w = (lookfrom - lookat).unit_vector();
            _u = Vector3::cross_product(up, _w).unit_vector();
            _v = Vector3::cross_product(_w, _u);

            auto focal_length = 1.0;

            _origin = lookfrom;
            _horizontal = focus_distance * viewport_width * _u;
            _vertical = focus_distance * viewport_height * _v;
            _lower_left_corner = _origin - _horizontal / 2 - _vertical / 2 - focus_distance * _w;
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
};

Ray Camera::ray(double s, double t) const {
    return Ray(
        _origin,
        (_lower_left_corner + s * _horizontal + t * _vertical - _origin).unit_vector()
    );
}
