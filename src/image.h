#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

// Type alias for convinience
using Pixel = std::shared_ptr<Color>;

class Image {
public:
    Image(const int width, const double aspect_ratio, int samples_per_pixel)
        : _width(width), _aspect_ratio(aspect_ratio), _samples_per_pixel(samples_per_pixel) {
        _height = static_cast<int>(_width / _aspect_ratio);

        // Init pixels
        for (auto i = 0; i < _height; ++i) {
            std::vector<Pixel> tmp;

            for (int j = 0; j < _width; ++j) {
                auto pixel = std::make_shared<Color>(0, 0, 0);
                tmp.push_back(pixel);
            }

            _pixels.push_back(tmp);
        }
    }

    int height() const {
        return _height;
    }

    int width() const {
        return _width;
    }

    Pixel get_pixel(int i, int j) const {
        return _pixels[i][j];
    }

    void write_pixel(std::ostream &out, std::shared_ptr<Color> pixel) {
        auto r = pixel->x();
        auto g = pixel->y();
        auto b = pixel->z();

        // Divide the color by the number of samples and gamma-correct for gamma=2.0.
        auto scale = 1.0 / _samples_per_pixel;
        r = std::sqrt(scale * r);
        g = std::sqrt(scale * g);
        b = std::sqrt(scale * b);

        // Write the translated [0,255] value of each color component.
        out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
    }

    void save_file() {
        std::ofstream file;

        file.open("image.ppm");

        file << "P3\n" << _width << ' ' << _height << "\n255\n";

        for (auto i = _height - 1; i >= 0; --i) {
            for (int j = 0; j < _width; ++j) {
                auto pixel = _pixels[i][j];
                write_pixel(file, pixel);
            }
            _pixels[i].clear();
        }
        _pixels.clear();

        file.close();
    }

private:
    int _height;
    int _width;
    double _aspect_ratio;
    int _samples_per_pixel;
    std::vector<std::vector<Pixel>> _pixels;
};
