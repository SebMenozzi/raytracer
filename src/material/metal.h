#pragma once

#include "material/material.h"
#include "utils/vector3.h"
#include "object/ray.h"

class Metal: public Material {
    public:
        Metal(const Color& albedo, double fuzziness)
            : _albedo(albedo), _fuzziness(fuzziness < 1 ? fuzziness : 1) {}

        virtual bool scatter(const Ray& ray, const hit_record& record, Color& attenuation, Ray& scattered) const override {
            auto direction = ray.direction();
            auto reflected = Vector3::reflect(ray.direction(), record.normal);
            auto scatter_direction = (reflected + _fuzziness * Vector3::random_in_unit_sphere()).unit_vector();
            scattered = Ray(record.point, scatter_direction);
            attenuation = _albedo;

            return true;
        }

    private:
        Color _albedo;
        double _fuzziness;
};
