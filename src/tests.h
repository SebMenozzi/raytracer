#pragma once

class Tests
{
    public:
        static void check_vector3();

    private:
        // Operator vector & scalar
        static void test_add_vector3_scalar();
        static void test_add_scalar_vector3();
        static void test_sub_vector3_scalar();
        static void test_sub_scalar_vector3();
        static void test_mult_vector3_scalar();
        static void test_mult_scalar_vector3();
        static void test_div_vector3_scalar();
        static void test_div_scalar_vector3();

        // Operator vector & vector
        static void test_add_vector3_vector3();
        static void test_sub_vector3_vector3();
        static void test_mult_vector3_vector3();
        static void test_div_vector3_vector3();

        // Operator ?= with vector
        static void test_plus_equal_vector3();
        static void test_minus_equal_vector3();
        static void test_mult_equal_vector3();
        static void test_div_equal_vector3();

        // Operator ?= with scalar
        static void test_plus_equal_scalar();
        static void test_minus_equal_scalar();
        static void test_mult_equal_scalar();
        static void test_div_equal_scalar();

        // Other methods
        static void test_squared_length();
        static void test_length();
        static void test_unit_vector();
};
