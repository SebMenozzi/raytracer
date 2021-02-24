#include "tests.h"
#include "vector3.h"
#include "utils.h"

// Operator vector & scalar

void Tests::test_add_vector3_scalar() {
    auto vec1 = Vector3(0, 0, 0) + 1;
    auto result = (vec1 == Vector3(1, 1, 1));
    print_result(result, __FUNCTION__);
}

void Tests::test_add_scalar_vector3() {
    auto vec1 = 42 + Vector3(0, 0, 0);
    auto result = (vec1 == Vector3(42, 42, 42));
    print_result(result, __FUNCTION__);
}

void Tests::test_sub_vector3_scalar() {
    auto vec1 = Vector3(0, 0, 0) - 1.0;
    auto result = (vec1 == Vector3(-1, -1, -1));
    print_result(result, __FUNCTION__);
}

void Tests::test_sub_scalar_vector3() {
    auto vec1 = -42 + Vector3(0, 0, 0);
    auto result = (vec1 == Vector3(-42, -42, -42));
    print_result(result, __FUNCTION__);
}

void Tests::test_mult_vector3_scalar() {
    auto vec1 = Vector3(2, 2, 2) * 2;
    auto result = (vec1 == Vector3(4, 4, 4));
    print_result(result, __FUNCTION__);
}

void Tests::test_mult_scalar_vector3() {
    auto vec1 = -12 * Vector3(2, 2, 2);
    auto result = (vec1 == Vector3(-24, -24, -24));
    print_result(result, __FUNCTION__);
}

void Tests::test_div_vector3_scalar() {
    auto vec1 = Vector3(4, 4, 4) / 2;
    auto result = (vec1 == Vector3(2, 2, 2));
    print_result(result, __FUNCTION__);
}

void Tests::test_div_scalar_vector3() {
    auto vec1 = -1 / Vector3(2, 2, 2);
    auto result = (vec1 == Vector3(-0.5, -0.5, -0.5));
    print_result(result, __FUNCTION__);
}

// Operator vector & vector

void Tests::test_add_vector3_vector3() {
    auto vec1 = Vector3(1, 2, 1);
    auto vec2 = Vector3(1, 3, 2);
    auto result = ((vec1 + vec2) == Vector3(2, 5, 3));
    print_result(result, __FUNCTION__);
}

void Tests::test_sub_vector3_vector3() {
    auto vec1 = Vector3(1, 2, 1);
    auto vec2 = Vector3(1, 3, 2);
    auto result = ((vec1 - vec2) == Vector3(0, -1, -1));
    print_result(result, __FUNCTION__);
}

void Tests::test_mult_vector3_vector3() {
    auto vec1 = Vector3(1, 2, 1);
    auto vec2 = Vector3(1, 3, 2);
    auto result = ((vec1 * vec2) == Vector3(1, 6, 2));
    print_result(result, __FUNCTION__);
}

void Tests::test_div_vector3_vector3() {
    auto vec1 = Vector3(1, 6, 8);
    auto vec2 = Vector3(1, 2, 4);
    auto result = ((vec1 / vec2) == Vector3(1, 3, 2));
    print_result(result, __FUNCTION__);
}

// Operator ?= with vector

void Tests::test_plus_equal_vector3() {
    auto vec1 = Vector3(2, 2, 2);
    vec1 += Vector3(1, 1, 1);
    auto result = (vec1 == Vector3(3, 3, 3));
    print_result(result, __FUNCTION__);
}

void Tests::test_minus_equal_vector3() {
    auto vec1 = Vector3(4, 4, 4);
    vec1 -= Vector3(1, 1, 1);
    auto result = (vec1 == Vector3(3, 3, 3));
    print_result(result, __FUNCTION__);
}

void Tests::test_mult_equal_vector3() {
    auto vec1 = Vector3(2, 2, 2);
    vec1 *= Vector3(4, 4, 4);
    auto result = (vec1 == Vector3(8, 8, 8));
    print_result(result, __FUNCTION__);
}

void Tests::test_div_equal_vector3() {
    auto vec1 = Vector3(8, 8, 8);
    vec1 /= -Vector3(4, 4, 4);
    auto result = (vec1 == -Vector3(2, 2, 2));
    print_result(result, __FUNCTION__);
}

// Operator ?= with scalar

void Tests::test_plus_equal_scalar() {
    auto vec1 = Vector3(2, 2, 2);
    vec1 += 1;
    auto result = (vec1 == Vector3(3, 3, 3));
    print_result(result, __FUNCTION__);
}

void Tests::test_minus_equal_scalar() {
    auto vec1 = Vector3(4, 4, 4);
    vec1 -= 1;
    auto result = (vec1 == Vector3(3, 3, 3));
    print_result(result, __FUNCTION__);
}

void Tests::test_mult_equal_scalar() {
    auto vec1 = Vector3(2, 2, 2);
    vec1 *= 4;
    auto result = (vec1 == Vector3(8, 8, 8));
    print_result(result, __FUNCTION__);
}

void Tests::test_div_equal_scalar() {
    auto vec1 = Vector3(8, 8, 8);
    vec1 /= -4;
    auto result = (vec1 == -Vector3(2, 2, 2));
    print_result(result, __FUNCTION__);
}

// Other methods

void Tests::test_squared_length() {
    auto vec1 = Vector3(2, 3, 3);
    auto result = (vec1.squared_length() == 22);
    print_result(result, __FUNCTION__);
}

void Tests::test_length() {
    auto vec1 = Vector3(std::sqrt(8), 2, 2);
    auto result = (vec1.length() == 4);
    print_result(result, __FUNCTION__);
}

void Tests::test_unit_vector() {
    auto vec1 = Vector3(42, 42, 42);
    auto vec2 = vec1.unit_vector();
    auto result = (vec2.length() == 1);
    print_result(result, __FUNCTION__);
}

void Tests::check_vector3() {
    print_info("Checking Vector3...");

    // Operator vector & scalar
    test_add_vector3_scalar();
    test_add_scalar_vector3();
    test_sub_vector3_scalar();
    test_sub_scalar_vector3();
    test_mult_vector3_scalar();
    test_mult_scalar_vector3();
    test_div_vector3_scalar();
    test_div_scalar_vector3();

    // Operator vector & vector
    test_add_vector3_vector3();
    test_sub_vector3_vector3();
    test_mult_vector3_vector3();
    test_div_vector3_vector3();

    // Operator ?= with vector
    test_plus_equal_vector3();
    test_minus_equal_vector3();
    test_mult_equal_vector3();
    test_div_equal_vector3();

    // Operator ?= with scalar
    test_plus_equal_scalar();
    test_minus_equal_scalar();
    test_mult_equal_scalar();
    test_div_equal_scalar();

    // Other methods
    test_squared_length();
    test_length();
    test_unit_vector();
}
