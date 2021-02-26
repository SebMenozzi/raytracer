#include <iostream>
#include <memory>

#include "tests.h"

#include "camera.h"
#include "scene.h"
#include "bvh_node.h"

#include "sphere.h"
#include "image.h"

#include "material.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"

Scene random_scene(const Camera& camera) {
    auto main_scene = Scene(camera);

    auto ground_scene = Scene(camera);
    auto ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    ground_scene.add_object(std::make_shared<Sphere>(Point3D(0, -1000, 0), 1000, ground_material));

    main_scene.add_object(std::make_shared<BVHNode>(ground_scene));

    auto small_balls_scene = Scene(camera);
    for (int x = -4; x < 4; ++x) {
        for (int y = -4; y < 4; ++y) {
            auto random_mat = random_double();
            auto center = Point3D(x + 0.9 * random_double(), 0.2, y + 0.9 * random_double());

            std::shared_ptr<Material> sphere_material;

            if (random_mat < 0.8) {
                // Diffuse
                auto albedo = Color::random() * Color::random();
                sphere_material = std::make_shared<Lambertian>(albedo);
                small_balls_scene.add_object(std::make_shared<Sphere>(center, 0.2, sphere_material));
            } else if (random_mat < 0.95) {
                // Metal
                auto albedo = Color::random(0.5, 1);
                auto fuzziness = random_double(0, 0.5);
                sphere_material = std::make_shared<Metal>(albedo, fuzziness);
                small_balls_scene.add_object(std::make_shared<Sphere>(center, 0.2, sphere_material));
            } else {
                // Glass
                sphere_material = std::make_shared<Dielectric>(1.5);
                small_balls_scene.add_object(std::make_shared<Sphere>(center, 0.2, sphere_material));
            }
        }
    }
    main_scene.add_object(std::make_shared<BVHNode>(small_balls_scene));

    auto big_balls_scene = Scene(camera);

    auto material1 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    big_balls_scene.add_object(std::make_shared<Sphere>(Point3D(-4, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Dielectric>(1.5);
    big_balls_scene.add_object(std::make_shared<Sphere>(Point3D(0, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    big_balls_scene.add_object(std::make_shared<Sphere>(Point3D(4, 1, 0), 1.0, material3));

    main_scene.add_object(std::make_shared<BVHNode>(big_balls_scene));

    return main_scene;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_failure("Missing one argument");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "tests") == 0) {
        Tests::check_vector3();
    }

    if (strcmp(argv[1], "image") == 0) {
        const double aspect_ratio = 16.0 / 9.0;
        const int samples_per_pixel = 100;

        // Image
        const int image_width = 1200;
        auto image = Image(image_width, aspect_ratio, samples_per_pixel);

        // Setup the camera
        auto lookfrom = Point3D(13, 2, 3);
        auto lookat = Point3D(0, 0, 0);
        auto up = Vector3(0, 1, 0);
        auto fov = 20.0;
        auto focus_distance = 10.0;

        auto camera = Camera(
            lookfrom,
            lookat,
            up,
            fov,
            aspect_ratio,
            focus_distance
        );

        // Scene
        auto scene = random_scene(camera);
        // Render
        scene.render(image, samples_per_pixel);
        // Save the rendering as a ppm image
        image.save_file();
    }

    return EXIT_SUCCESS;
}
