#pragma once

#include "hittable.h"
#include "utils.h"
#include "camera.h"
#include "sphere.h"
#include "image.h"
#include "material.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"

#include <memory>
#include <vector>

class Scene {
    public:
        Scene(const Camera& camera): _camera(camera) {}

        bool hit(const Ray& ray, hit_record& record) const;
        Color ray_color(const Ray& ray, int depth);
        void random();
        void render(const Image& image, const int samples_per_pixel, const int max_depth);

    private:
        void clear();
        void add_object(std::shared_ptr<Hittable> object);

        std::vector<std::shared_ptr<Hittable>> _objects;
        Camera _camera;
};

void Scene::clear() {
    _objects.clear();
}
void Scene::add_object(std::shared_ptr<Hittable> object) {
    _objects.push_back(object);
}

bool Scene::hit(const Ray& ray, hit_record& record) const {
    double t_min = 0.001;
    double t_max = infinity;

    hit_record tmp;
    bool has_hit = false;
    auto closest = t_max;

    for (const auto& object : _objects) {
        if (object->hit(ray, t_min, closest, tmp)) {
            has_hit = true;
            closest = tmp.t;
            record = tmp;
        }
    }

    return has_hit;
}

Color Scene::ray_color(const Ray& ray, int depth) {
    hit_record record;

    // If we exceed the ray bounce limit, display a black pixel
    if (depth <= 0)
        return Color(0, 0, 0);

    if (hit(ray, record)) {
        Ray scattered;
        Color attenuation;

        if (record.material->scatter(ray, record, attenuation, scattered))
            return attenuation * ray_color(scattered, depth - 1);

        return Color(0, 0, 0);
    }

    auto direction = ray.direction();
    auto unit_direction = direction.unit_vector();
    auto t = 0.5 * (unit_direction.y() + 1.0);

    return Vector3::linear_blend(t, Color(1.0, 1.0, 1.0), Color(0.5, 0.7, 1.0));
}

void Scene::random() {
    auto ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    add_object(std::make_shared<Sphere>(Point3D(0, -1000, 0), 1000, ground_material));

    for (int x = -2; x < 2; ++x) {
        for (int y = 0; y < 3; ++y) {
            auto random_mat = random_double();
            auto center = Point3D(x + 0.9 * random_double(), 0.2, y + 0.9 * random_double());

            std::shared_ptr<Material> sphere_material;

            if (random_mat < 0.8) {
                // Diffuse
                auto albedo = Color::random() * Color::random();
                sphere_material = std::make_shared<Lambertian>(albedo);
                add_object(std::make_shared<Sphere>(center, 0.2, sphere_material));
            } else if (random_mat < 0.95) {
                // Metal
                auto albedo = Color::random(0.5, 1);
                auto fuzziness = random_double(0, 0.5);
                sphere_material = std::make_shared<Metal>(albedo, fuzziness);
                add_object(std::make_shared<Sphere>(center, 0.2, sphere_material));
            } else {
                // Glass
                sphere_material = std::make_shared<Dielectric>(1.5);
                add_object(std::make_shared<Sphere>(center, 0.2, sphere_material));
            }
        }
    }

    auto material1 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    add_object(std::make_shared<Sphere>(Point3D(-2.5, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Dielectric>(1.5);
    add_object(std::make_shared<Sphere>(Point3D(0, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    add_object(std::make_shared<Sphere>(Point3D(2.5, 1, 0), 1.0, material3));
}

void Scene::render(const Image& image, const int samples_per_pixel, const int max_depth) {
    for (auto i = image.height() - 1; i >= 0; --i) {
        std::cerr << "\r\033[;32mProgress: " << (image.height() - i) << " / " << image.height() << "\033[0m" << std::flush;

        for (int j = 0; j < image.width(); ++j) {
            auto pixel_color = image.get_pixel(i, j);

            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (j + random_double()) / (image.width() - 1);
                auto v = (i + random_double()) / (image.height() - 1);
                auto ray = _camera.ray(u, v);
                *pixel_color += ray_color(ray, max_depth);
            }
        }
    }
}
