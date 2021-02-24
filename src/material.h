#pragma once

#include "ray.h"

struct hit_record;

class Material {
    public:
        virtual bool scatter(const Ray& ray, const hit_record& record, Color& attenuation, Ray& scattered) const = 0;
};
