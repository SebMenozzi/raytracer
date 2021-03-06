#pragma once

#include "utils/vector3.h"
#include "object/ray.h"
#include "material/material.h"

class Lambertian: public Material {
    public:
        Lambertian(const Color& albedo) : _albedo(albedo) {}

        virtual bool scatter(const Ray& ray, const hit_record& record, Color& attenuation, Ray& scattered) const override {
            auto scatter_direction = (record.normal + Vector3::random_in_unit_sphere()).unit_vector();

            // Catch degenerate scatter direction
            if (scatter_direction.near_zero())
                scatter_direction = record.normal;

            scattered = Ray(record.point, scatter_direction);
            attenuation = _albedo;
            return true;
        }

    private:
        Color _albedo;
};
