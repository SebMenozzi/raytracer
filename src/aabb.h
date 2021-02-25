#pragma once

#include "ray.h"

class AABB {
    public:
        AABB() {}
        AABB(const Point3D& a, const Point3D& b)
            : _min(a), _max(b) {}

        inline Point3D min() const { return _min; }
        inline Point3D max() const { return _max; }

        inline bool hit(const Ray& ray, double t_min, double t_max) const {
            for (int a = 0; a < 3; ++a) {
                auto invD = 1.0f / ray.direction()[a];
                auto t0 = (min()[a] - ray.origin()[a]) * invD;
                auto t1 = (max()[a] - ray.origin()[a]) * invD;

                if (invD < 0.0f)
                    std::swap(t0, t1);

                t_min = t0 > t_min ? t0 : t_min;
                t_max = t1 < t_max ? t1 : t_max;

                if (t_max <= t_min)
                    return false;
            }

            return true;
        }

        inline static AABB surrounding_box(AABB box0, AABB box1) {
            Point3D small(
                fmin(box0.min().x(), box1.min().x()),
                fmin(box0.min().y(), box1.min().y()),
                fmin(box0.min().z(), box1.min().z())
            );

            Point3D big(
                fmax(box0.max().x(), box1.max().x()),
                fmax(box0.max().y(), box1.max().y()),
                fmax(box0.max().z(), box1.max().z())
            );

            return AABB(small, big);
        }

    private:
        Point3D _min;
        Point3D _max;
};
