#include <iostream>
#include <string>
#include <cmath>
#include "common/common.hpp"

using namespace euler;

// ANSI colors
#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

static int total_tests = 0;
static int passed_tests = 0;

void print_result(const std::string& name, bool pass)
{
    total_tests++;
    if (pass)
    {
        passed_tests++;
        std::cout << "Test: " << name << " " << GREEN << "PASSED" << RESET << "\n";
    }
    else
    {
        std::cout << "Test: " << name << " " << RED << "FAILED" << RESET << "\n";
    }
}

int main()
{
    // -----------------------
    // max / min / clamp
    // -----------------------
    print_result("max", max(3, 5) == 5);
    print_result("min", min(3, 5) == 3);
    print_result("clamp", clamp(10, 0, 5) == 5);

    // -----------------------
    // abs / sign
    // -----------------------
    print_result("abs positive", abs(5) == 5);
    print_result("abs negative", abs(-5) == 5);
    print_result("sign positive", sign(10) == 1);
    print_result("sign negative", sign(-10) == -1);
    print_result("sign zero", sign(0) == 0);

    // -----------------------
    // safe_div
    // -----------------------
    print_result("safe_div normal", safe_div(10, 2) == 5);
    print_result("safe_div zero", safe_div(10, 0) == 0);

    // -----------------------
    // epsilon_equal / is_zero
    // -----------------------
    print_result("epsilon_equal true",
        epsilon_equal(0.1 + 0.2, 0.3, 1e-6));

    print_result("is_zero true",
        is_zero(1e-8, 1e-6));

    // -----------------------
    // lerp / inverse_lerp
    // -----------------------
    print_result("lerp",
        epsilon_equal(lerp(0.0, 10.0, 0.5), 5.0, 1e-6));

    print_result("inverse_lerp",
        epsilon_equal(inverse_lerp(0.0, 10.0, 5.0), 0.5, 1e-6));

    // -----------------------
    // deg <-> rad
    // -----------------------
    print_result("deg_to_rad",
        epsilon_equal(deg_to_rad(180.0), constants<double>::pi, 1e-6));

    print_result("rad_to_deg",
        epsilon_equal(rad_to_deg(constants<double>::pi), 180.0, 1e-6));

    // -----------------------
    // constants
    // -----------------------
    print_result("pi constant",
        epsilon_equal(constants<double>::pi, 3.141592653589793, 1e-12));

    print_result("epsilon constant",
        constants<float>::epsilon > 0);

    // -----------------------
    // nan_v
    // -----------------------
    float nan_test = nan_v<float>;
    print_result("nan_v",
        std::isnan(nan_test));

    // -----------------------
    // float_to_int
    // -----------------------
    print_result("float_to_int<float>",
        std::is_same_v<float_to_int_t<float>, int32_t>);

    print_result("float_to_int<double>",
        std::is_same_v<float_to_int_t<double>, int64_t>);

    // -----------------------
    // floor / ceil
    // -----------------------
    print_result("floor positive", floor(3.7f) == 3);
    print_result("floor negative", floor(-3.7f) == -4);

    print_result("ceil positive", ceil(3.2f) == 4);
    print_result("ceil negative", ceil(-3.2f) == -3);

    // -----------------------
    // FINAL RESULT
    // -----------------------
    std::cout << "\n";

    if (passed_tests == total_tests)
    {
        std::cout << GREEN << "All Tests PASSED (" 
                  << passed_tests << "/" << total_tests << ")" 
                  << RESET << "\n";
    }
    else
    {
        std::cout << RED << "Tests FAILED (" 
                  << passed_tests << "/" << total_tests << ")" 
                  << RESET << "\n";
    }

    return 0;
}
