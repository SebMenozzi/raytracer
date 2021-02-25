#pragma once

#include "material.h"
#include "vector3.h"
#include "ray.h"

class Metal: public Material {
    public:
        Metal(const Color& albedo, double fuzziness)
            : _albedo(albedo), _fuzziness(fuzziness < 1 ? fuzziness : 1) {}

        virtual bool scatter(const Ray& ray, const hit_record& record, Color& attenuation, Ray& scattered) const override {
            auto direction = ray.direction();
            auto unit_direction = direction.unit_vector();
            auto reflected = Vector3::reflect(unit_direction, record.normal);
            scattered = Ray(record.point, reflected + _fuzziness * Vector3::random_in_unit_sphere());
            attenuation = _albedo;

            return (Vector3::dot_product(scattered.direction(), record.normal) > 0);
        }

    private:
        Color _albedo;
        double _fuzziness;
};
