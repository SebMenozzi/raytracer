#pragma once

#include "object/ray.h"
#include "material/material.h"
#include "utils/utils.h"
#include "utils/vector3.h"

class Dielectric: public Material {
    public:
        Dielectric(double index_of_refraction)
            : _index_of_refraction(index_of_refraction) {}

        virtual bool scatter(const Ray& ray, const hit_record& record, Color& attenuation, Ray& scattered) const override {
            attenuation = Color(1.0, 1.0, 1.0);

            auto refraction_ratio = record.front_face ? (1.0 / _index_of_refraction) : _index_of_refraction;

            double cos_theta = std::fmin(Vector3::dot_product(-ray.direction(), record.normal), 1.0);
            double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

            bool cannot_refract = refraction_ratio * sin_theta > 1.0;
            Vector3 direction;

            if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
                direction = Vector3::reflect(ray.direction(), record.normal).unit_vector();
            else
                direction = Vector3::refract(ray.direction(), record.normal, refraction_ratio).unit_vector();

            scattered = Ray(record.point, direction);

            return true;
        }

    private:
        double _index_of_refraction;

        static double reflectance(double cosine, double ref_idx) {
            // Use Schlick's approximation for reflectance
            auto r0 = (1 - ref_idx) / (1 + ref_idx);
            r0 = r0 * r0;
            return r0 + (1 - r0) * std::pow(1 - cosine, 5);
        }
};
