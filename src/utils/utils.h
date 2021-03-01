#pragma once

#include <iostream>
#include <limits>
#include <cstdlib>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline void print_success(const char* message) {
    std::cout << "\033[;32m[SUCCESS] " << message << "\033[0m\n";
}

inline void print_failure(const char* message) {
    std::cout << "\033[;31m[FAILURE] " << message << "\033[0m\n";
}

inline void print_info(const char* message) {
    std::cout << "\033[;34m[INFO] " << message << "\033[0m\n";
}

inline void print_result(bool result, const char* message) {
    if (result == 1)
        print_success(message);
    else
        print_failure(message);
}

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}

inline int random_int(int min, int max) {
    return static_cast<int>(random_double(min, max + 1));
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;

    return x;
}
