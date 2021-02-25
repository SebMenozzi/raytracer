#pragma once

#include <cmath>
#include <memory>

#include "hittable.h"
#include "vector3.h"
#include "aabb.h"

class Sphere: public Hittable {
    public:
        Sphere() {}
        Sphere(Point3D center, double radius, std::shared_ptr<Material> material)
            : _center(center), _radius(radius), _material(material) {};

        virtual bool hit(const Ray& ray, double t_min, double t_max, hit_record& record) const override;
        virtual bool bounding_box(AABB& output_box) const override;

    private:
        Point3D _center;
        double _radius;
        std::shared_ptr<Material> _material;
};

// https://en.wikipedia.org/wiki/Dot_product
// c = a -b
// c . c = (a - b)⋅(a - b)
// Equation : t^2⋅b⋅b + 2tb⋅(A - C) + (A - C)⋅(A - C) − r^2 = 0
bool Sphere::hit(const Ray& ray, double t_min, double t_max, hit_record& record) const {
    auto oc = ray.origin() - _center;
    auto a = ray.direction().squared_length();
    auto half_b = Vector3::dot_product(oc, ray.direction());
    auto c = oc.squared_length() - _radius * _radius;

    auto discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
        return false;

    auto sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range
    auto root = (-half_b - sqrtd) / a;

    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;

        if (root < t_min || t_max < root)
            return false;
    }

    record.t = root;
    record.point = ray.at(record.t);
    auto outward_normal = (record.point - _center) / _radius;
    record.set_face_normal(ray, outward_normal);
    record.material = _material;

    return true;
}

bool Sphere::bounding_box(AABB& output_box) const {
    output_box = AABB(
        _center - Vector3(_radius, _radius, _radius),
        _center + Vector3(_radius, _radius, _radius)
    );

    return true;
}
