#pragma once

#include <iostream>
#include <cmath>
#include <memory>

#include "hittable.h"
#include "vector3.h"
#include "aabb.h"
#include "macro.h"

class Sphere: public Hittable {
    public:
        Sphere() {}
        Sphere(Point3D center, double radius, std::shared_ptr<Material> material)
            : _center(center), _radius(radius), _material(material) {};

        virtual bool hit(const Ray& ray, double t_min, double t_max, hit_record& record) const override;
        virtual bool bounding_box(AABB& output_box) const override;

    private:
        inline bool hit_geometric(const Ray& ray, double& t0, double& t1) const {
            auto oc = _center - ray.origin();
            // Distance between the origin and the point A corresponding to the sphere center projected on the ray
            auto toa = Vector3::dot_product(oc, ray.direction());

            // if tco is < 0, the ray is going in the opposite direction
            if (toa < 0)
                return false;

            // Pythagorean theorem : d^2 + toa^2 = l^2
            auto d2 = oc.squared_length() - toa * toa;
            auto r2 = _radius * _radius;

            // The ray is missing the sphere
            if (d2 > r2)
                return false;

            // Distance between A and P, P is the intersection point of the vector t0 * D with the sphere
            // From Pythagorean theorem : d^2 + tpa^2 = radius^2
            auto tpa = std::sqrt(r2 - d2);

            // 2 roots
            t0 = toa - tpa;
            t1 = toa + tpa;

            return true;
        }

        inline bool hit_algebric(const Ray& ray, double& t0, double& t1) const {
            // Sphere equation : (px - cx)^2 + (py - cy)^2 + (pz - cz)^2 = R^2
            // (P(t) - C)^2 =  R^2
            // ((o + tD) - C)^2 - R^2 = 0, with o + tD the ray equation
            auto oc = ray.origin() - _center;
            auto a = 1;
            auto b = 2 * Vector3::dot_product(oc, ray.direction());
            auto c = oc.squared_length() - _radius * _radius;

            auto discriminant = b * b - 4 * a * c;

            if (discriminant < 0)
                return false;

            auto sqrtd = std::sqrt(discriminant);

            // 2 roots
            t0 = (-b - sqrtd) / (2 * a);
            t1 = (-b + sqrtd) / (2 * a);

            return true;
        }

        Point3D _center;
        double _radius;
        std::shared_ptr<Material> _material;
};

bool Sphere::hit(const Ray& ray, double t_min, double t_max, hit_record& record) const {
    double t0, t1;
    bool result;

    // Both techniques work perfectly and have similar performances
    // No preference can be made, I like both :)
    if (true)
        result = hit_algebric(ray, t0, t1);
    else
        result = hit_geometric(ray, t0, t1);

    if (!result)
        return false;

    auto root = t0;

    // Find the nearest root that lies in the acceptable range
    if (root < t_min || t_max < root) {
        root = t1;

        if (root < t_min || t_max < root)
            return false;
    }

    record.t = root;
    record.point = ray.position(record.t);
    auto normal = (record.point - _center).unit_vector();
    record.set_face_normal(ray, normal);
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
