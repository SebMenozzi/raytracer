#pragma once

#include <memory>

#include "ray.h"
#include "vector3.h"
#include "material.h"

struct hit_record {
    Point3D point;
    Vector3 normal;
    double t;
    bool front_face;
    std::shared_ptr<Material> material;

    inline void set_face_normal(const Ray& ray, const Vector3& outward_normal) {
        front_face = Vector3::dot_product(ray.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable {
    public:
        virtual bool hit(const Ray& ray, double t_min, double t_max, hit_record& record) const = 0;
};
