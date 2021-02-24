#include <iostream>
#include <memory>

#include "tests.h"
#include "camera.h"
#include "scene.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_failure("Missing one argument");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "tests") == 0) {
        Tests::check_vector3();
    }

    if (strcmp(argv[1], "image") == 0) {
        const auto aspect_ratio = 3.0 / 2.0;
        const int samples_per_pixel = 100;
        const int max_depth = 10;

        // Image
        const int image_width = 400;
        auto image = Image(image_width, aspect_ratio, samples_per_pixel);

        // Setup the camera
        auto lookfrom = Point3D(0, 0.5, 4);
        auto lookat = Point3D(0, 0, 0);
        auto up = Vector3(0, 1, 0);
        auto fov = 60.0;
        auto aperture = 0.1;
        auto focus_distance = 10.0;

        auto camera = Camera(
            lookfrom,
            lookat,
            up,
            fov,
            aspect_ratio,
            aperture,
            focus_distance
        );

        // Scene
        auto scene = Scene(camera);
        // Add random objects
        scene.random();
        // Render
        scene.render(image, samples_per_pixel, max_depth);
        // Save the rendering as a ppm image
        image.save_file();
    }

    return EXIT_SUCCESS;
}
