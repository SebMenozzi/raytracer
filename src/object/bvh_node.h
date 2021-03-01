#pragma once

#include <algorithm>

#include "object/hittable.h"
#include "utils/utils.h"
#include "scene/scene.h"

class BVHNode: public Hittable {
    public:
        BVHNode();

        BVHNode(const Scene& scene) : BVHNode(scene.objects(), 0, scene.objects().size()) {}

        BVHNode(const Objects& objects, size_t start, size_t end);

        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& record) const override;
        virtual bool bounding_box(AABB& output_box) const override;

        inline static bool box_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis) {
            AABB box_a;
            AABB box_b;

            if (!a->bounding_box(box_a) || !b->bounding_box(box_b))
                std::cerr << "No bounding box in bvh_node constructor.\n";

            return box_a.min()[axis] < box_b.min()[axis];
        }

        inline static bool box_x_compare (const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
            return box_compare(a, b, 0);
        }

        inline static bool box_y_compare (const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
            return box_compare(a, b, 1);
        }

        inline static bool box_z_compare (const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
            return box_compare(a, b, 2);
        }

    public:
        std::shared_ptr<Hittable> left;
        std::shared_ptr<Hittable> right;
        AABB box;
};

BVHNode::BVHNode(const Objects& objects, size_t start, size_t end) {
    auto mutable_objects = objects;

    int axis = random_int(0,2);

    auto comparator = (axis == 0) ? BVHNode::box_x_compare : (axis == 1) ? BVHNode::box_y_compare : BVHNode::box_z_compare;

    size_t object_span = end - start;

    if (object_span == 1) {
        left = right = mutable_objects[start];
    } else if (object_span == 2) {
        if (comparator(mutable_objects[start], mutable_objects[start + 1])) {
            left = mutable_objects[start];
            right = mutable_objects[start + 1];
        } else {
            left = mutable_objects[start + 1];
            right = mutable_objects[start];
        }
    } else {
        std::sort(mutable_objects.begin() + start, mutable_objects.begin() + end, comparator);

        auto mid = start + object_span / 2;
        left = std::make_shared<BVHNode>(mutable_objects, start, mid);
        right = std::make_shared<BVHNode>(mutable_objects, mid, end);
    }

    AABB box_left, box_right;

    if (!left->bounding_box(box_left) || !right->bounding_box(box_right))
        std::cerr << "No bounding box in bvh_node constructor.\n";

    box = AABB::surrounding_box(box_left, box_right);
}

bool BVHNode::hit(const Ray& ray, double t_min, double t_max, hit_record& record) const {
    if (!box.hit(ray, t_min, t_max))
        return false;

    bool hit_left = left->hit(ray, t_min, t_max, record);
    bool hit_right = right->hit(ray, t_min, hit_left ? record.t : t_max, record);

    return hit_left || hit_right;
}

bool BVHNode::bounding_box(AABB& output_box) const {
    output_box = box;

    return true;
}
