#pragma once

#include <cmath>
#include <iostream>
#include "utils.h"

class Vector3
{
    public:
        Vector3(): _data{0, 0, 0} {}

        Vector3(const double x, const double y, const double z) {
            _data[0] = x;
            _data[1] = y;
            _data[2] = z;
        }

        inline double x() const { return _data[0]; }
        inline double y() const { return _data[1]; }
        inline double z() const { return _data[2]; }

        inline Vector3 operator-() const {
            return Vector3(-x(), -y(), -z());
        }

        inline double operator[](std::size_t i) const { return _data[i]; }
    	inline double& operator[](std::size_t i) { return _data[i]; };

        inline bool operator==(const Vector3 &v) {
            return (x() == v.x() && y() == v.y() && z() == v.z());
        }

        // ?= operator with vector
        inline Vector3& operator+=(const Vector3 &v);
    	inline Vector3& operator-=(const Vector3 &v);
    	inline Vector3& operator*=(const Vector3 &v);
    	inline Vector3& operator/=(const Vector3 &v);

        // ?= operator with scalar
        inline Vector3& operator+=(const double e);
    	inline Vector3& operator-=(const double e);
    	inline Vector3& operator*=(const double e);
    	inline Vector3& operator/=(const double e);

        // Other useful methods
        inline double squared_length() const;
        inline double length() const;
        inline Vector3 unit_vector() const;
        inline bool near_zero() const;

        // Static methods
        inline static double dot_product(const Vector3 &v1, const Vector3 &v2);
        inline static Vector3 cross_product(const Vector3 &v1, const Vector3 &v2);
        inline static Vector3 random();
        inline static Vector3 random(double min, double max);
        inline static Vector3 random_in_unit_sphere();
        inline static Vector3 random_in_unit_disk();
        inline static Vector3 random_unit_vector();
        inline static Vector3 random_in_hemisphere(const Vector3& normal);
        inline static Vector3 reflect(const Vector3& vector, const Vector3& normal);
        inline static Vector3 refract(const Vector3& uv, const Vector3& normal, double refraction_ratio);
        inline static Vector3 linear_blend(double t, Vector3 start, Vector3 end);

    private:
        double _data[3];
};

// Type aliases for convinience
using Point3D = Vector3; // 3D point
using Color = Vector3;  // RGB color

// Operator vector & scalar

inline Vector3 operator+(const Vector3 &v, const double e) {
    return Vector3(v.x() + e, v.y() + e, v.z() + e);
}
inline Vector3 operator+(const double e, const Vector3 &v) {
    return v + e;
}

inline Vector3 operator-(const Vector3 &v, const double e) {
    return v + (-e);
}
inline Vector3 operator-(const double e, const Vector3 &v) {
    return v - e;
}

inline Vector3 operator*(const Vector3 &v, const double e) {
    return Vector3(v.x() * e, v.y() * e, v.z() * e);
}
inline Vector3 operator*(const double e, const Vector3 &v) {
    return v * e;
}

inline Vector3 operator/(const Vector3 &v, const double e) {
    return Vector3(v.x() / e, v.y() / e, v.z() / e);
}
inline Vector3 operator/(const double e, const Vector3 &v) {
    return Vector3(e / v.x(), e / v.y(), e / v.z());
}

// Operator vector & vector

inline Vector3 operator+(const Vector3 &v1, const Vector3 &v2) {
    return Vector3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

inline Vector3 operator-(const Vector3 &v1, const Vector3 &v2) {
    return v1 + (-v2);
}

inline Vector3 operator*(const Vector3 &v1, const Vector3 &v2) {
    return Vector3(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
}

inline Vector3 operator/(const Vector3 &v1, const Vector3 &v2) {
    return v1 * (1 / v2);
}

// Operator ?= with vector

inline Vector3& Vector3::operator+=(const Vector3 &v) {
    _data[0] += v.x();
    _data[1] += v.y();
    _data[2] += v.z();

    return *this;
}
inline Vector3& Vector3::operator-=(const Vector3 &v) {
    return *this += -v;
}
inline Vector3& Vector3::operator*=(const Vector3 &v) {
    _data[0] *= v.x();
    _data[1] *= v.y();
    _data[2] *= v.z();

    return *this;
}
inline Vector3& Vector3::operator/=(const Vector3 &v) {
    return *this *= 1.0 / v;
}

// Operator ?= with scalar

inline Vector3& Vector3::operator+=(const double e) {
    _data[0] += e;
    _data[1] += e;
    _data[2] += e;

    return *this;
}
inline Vector3& Vector3::operator-=(const double e) {
    return *this += -e;
}
inline Vector3& Vector3::operator*=(const double e) {
    _data[0] *= e;
    _data[1] *= e;
    _data[2] *= e;

    return *this;
}
inline Vector3& Vector3::operator/=(const double e) {
    return *this *= 1 / e;
}

// Useful methods

inline double Vector3::squared_length() const {
    return x() * x() + y() * y() + z() * z();
}
inline double Vector3::length() const {
    return std::sqrt(squared_length());
}
inline Vector3 Vector3::unit_vector() const {
    return (*this) / length();
}
inline bool Vector3::near_zero() const {
    // Return true if the vector is close to zero in all dimensions.
    const auto s = 1e-8;

    return (fabs(x()) < s && fabs(y()) < s && fabs(z()) < s);
}

// Static methods

inline double Vector3::dot_product(const Vector3 &v1, const Vector3 &v2) {
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}
inline Vector3 Vector3::cross_product(const Vector3 &v1, const Vector3 &v2) {
    return Vector3(
         (v1.y() * v2.z() - v1.z() * v2.y()),
        -(v1.x() * v2.z() - v1.z() * v2.x()),
         (v1.x() * v2.y() - v1.y() * v2.x())
    );
}
inline Vector3 Vector3::random() {
    return Vector3(random_double(), random_double(), random_double());
}
inline Vector3 Vector3::random(double min, double max) {
    return Vector3(
        random_double(min, max),
        random_double(min, max),
        random_double(min, max)
    );
}
inline Vector3 Vector3::random_in_unit_sphere() {
    while (true) {
        auto p = Vector3::random(-1, 1);

        if (p.squared_length() >= 1)
            continue;

        return p;
    }
}
inline Vector3 Vector3::random_in_unit_disk() {
    while (true) {
        auto p = Vector3(random_double(-1, 1), random_double(-1, 1), 0);

        if (p.squared_length() >= 1)
            continue;

        return p;
    }
}
inline Vector3 Vector3::random_unit_vector() {
    auto vec = Vector3::random_in_unit_sphere();

    return vec.unit_vector();
}
inline Vector3 Vector3::random_in_hemisphere(const Vector3& normal) {
    auto in_unit_sphere = random_in_unit_sphere();

    // In the same hemisphere as the normal
    if (Vector3::dot_product(in_unit_sphere, normal) > 0.0)
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}
inline Vector3 Vector3::reflect(const Vector3& vector, const Vector3& normal) {
    return vector - 2 * Vector3::dot_product(vector, normal) * normal;
}
inline Vector3 Vector3::refract(const Vector3& uv, const Vector3& normal, double refraction_ratio) {
    auto cos_theta = std::fmin(Vector3::dot_product(-uv, normal), 1.0);
    auto r_out_perp = refraction_ratio * (uv + cos_theta * normal);
    auto r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.squared_length())) * normal;

    return r_out_perp + r_out_parallel;
}
inline Vector3 Vector3::linear_blend(double t, Vector3 start, Vector3 end) {
    return (1.0 - t) * start + t * end;
}
