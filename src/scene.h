#pragma once

#include "image.h"
#include "hittable.h"
#include "camera.h"
#include "progress_bar.h"
#include "aabb.h"

#include <memory>
#include <vector>
#include <thread>
#include <future>
#include <mutex>

// Type alias for convinience
using Objects = std::vector<std::shared_ptr<Hittable>>;

class Scene: public Hittable {
    public:
        Scene(const Camera& camera): _camera(camera) {}

        Objects objects() const;
        void add_object(std::shared_ptr<Hittable> object);
        void render(const Image& image, const int samples_per_pixel);

        virtual bool hit(const Ray& ray, double t_min, double t_max, hit_record& record) const override;
        virtual bool bounding_box(AABB& output_box) const override;

    private:
        void clear();
        Color ray_color(const Ray& ray, int depth);

        Objects _objects;
        Camera _camera;
};

Objects Scene::objects() const {
    return _objects;
}

void Scene::clear() {
    _objects.clear();
}
void Scene::add_object(std::shared_ptr<Hittable> object) {
    _objects.push_back(object);
}

bool Scene::hit(const Ray& ray, double t_min, double t_max, hit_record& record) const {
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

bool Scene::bounding_box(AABB& output_box) const {
    if (_objects.empty())
        return false;

    AABB temp_box;
    bool first_box = true;

    for (const auto& object : _objects) {
        if (!object->bounding_box(temp_box))
            return false;

        output_box = first_box ? temp_box : AABB::surrounding_box(output_box, temp_box);
        first_box = false;
    }

    return true;
}

Color Scene::ray_color(const Ray& ray, int depth) {
    hit_record record;

    // If we exceed the ray bounce limit, display a black pixel
    if (depth <= 0) {
        return Color(0, 0, 0);
    }

    if (hit(ray, 0.001, infinity, record)) {
        Ray scattered;
        Color attenuation;

        if (record.material->scatter(ray, record, attenuation, scattered)) {
            return attenuation * ray_color(scattered, depth - 1);
        }

        return Color(1, 1, 1);
    }

    auto direction = ray.direction();
    auto unit_direction = direction.unit_vector();
    auto t = 0.5 * (unit_direction.y() + 1.0);

    return Vector3::linear_blend(t, Color(1.0, 1.0, 1.0), Color(0.5, 0.7, 1.0));
}

void Scene::render(const Image& image, const int samples_per_pixel) {
    std::size_t max = image.width() * image.height();
    std::size_t cores = std::thread::hardware_concurrency();

    std::cout << "Threads supported: " << cores << "\n";

    volatile std::atomic<std::size_t> count = 0;
    std::vector<std::future<void>> futures;
    auto cout_lock = new std::mutex();

    auto progress = ProgressBar(std::cout, 100);

    while (cores--)
    {
        futures.push_back(std::async(std::launch::async, [=, &image, &progress, &count]() {
            while (true)
            {
                std::size_t index = count++;
                if (index >= max)
                    break;

                std::size_t x = index / image.width();
                std::size_t y = index % image.width();

                auto pixel = image.get_pixel(x, y);

                for (int s = 0; s < samples_per_pixel; ++s) {
                    auto u = (y + random_double()) / (image.width() - 1);
                    auto v = (x + random_double()) / (image.height() - 1);
                    auto ray = _camera.ray(u, v);

                    *pixel += ray_color(ray, 10);
                }

                {
                    auto lock = std::lock_guard<std::mutex>(*cout_lock);
                    progress.write(count / (double) max);
                }
            }
        }));
    }

    for (auto& future: futures)
        future.get();
}
