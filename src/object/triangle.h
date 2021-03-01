#pragma once

#include "object/hittable.h"

class Triangle : public Hittable {
    public:
        Triangle() {}
        Triangle(Vector3 a, Vector3 b, Vector3 c, std::shared_ptr<Material> material) : _a(a), _b(b), _c(c) {
            _edge1 = b - a;
            _edge2 = c - a;
            normal = Vector3::cross_product(edge1, edge2).unit_vector();
        };

    virtual bool hit(const ray& r, Float t_min, Float t_max, hit_record& rec, random_gen& rng);
    virtual bool bounding_box(Float t0, Float t1, aabb& box) const;

    vec3 normal;
    vec3 a, b, c, na, nb, nc;
    vec3 edge1, edge2;
    Float area;
    bool normals_provided;
    bool single;
    std::shared_ptr<material> mp;
    std::shared_ptr<alpha_texture> alpha_mask;
    std::shared_ptr<bump_texture> bump_tex;
};
