#include <iostream>
#include <cmath>
#include <string>

#include "common/common.hpp"
#include "vector/vec.hpp"
#include "vector/vec2.hpp"

using namespace euler;

// ---------- COLORS ----------
#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

// ---------- TEST STATE ----------
static int passed = 0;
static int failed = 0;

void test_result(const std::string& name, bool ok)
{
    if (ok)
    {
        std::cout << "Test: " << name << " " << GREEN << "PASSED" << RESET << "\n";
        ++passed;
    }
    else
    {
        std::cout << "Test: " << name << " " << RED << "FAILED" << RESET << "\n";
        ++failed;
    }
}

#define TEST(name, expr) test_result(name, (expr))

// ---------- TESTS ----------

// Basic
void test_init()
{
    vec<int, 3> v;
    TEST("init zero", v[0]==0 && v[1]==0 && v[2]==0);
}

// Dot / length
void test_dot_length()
{
    vec<int,3> a; vec<int,3> b;
    a[0]=1; a[1]=2; a[2]=3;
    b[0]=4; b[1]=5; b[2]=6;

    TEST("dot", dot(a,b) == 32);

    vec<float,2> v;
    v[0]=3; v[1]=4;

    TEST("length", equal_epsilon(length(v), 5.0f));
    TEST("length_sq", length_sq(v) == 25);
}

// Scale
void test_scale()
{
    vec<int,2> v; v[0]=2; v[1]=3;

    auto r = scale(v, 2);
    TEST("scale same type", r[0]==4 && r[1]==6);

    auto r2 = scale(v, 2.5f);
    TEST("scale mixed type", equal_epsilon(r2[0],5.0f));
}

// Normalize
void test_normalize()
{
    vec<float,2> v; v[0]=3; v[1]=4;

    auto n = normalize(v);
    TEST("normalize", equal_epsilon(length(n), 1.0f));

    auto sn = safe_normalize(vec<float,2>());
    TEST("safe normalize zero", sn[0]==0 && sn[1]==0);
}

// Abs / floor / ceil / frac
void test_math_ops()
{
    vec<float,2> v; v[0]=-1.5f; v[1]=2.3f;

    auto a = abs(v);
    TEST("abs", a[0]==1.5f && a[1]==2.3f);

    auto f = floor(v);
    TEST("floor", f[0]==-2 && f[1]==2);

    auto c = ceil(v);
    TEST("ceil", c[0]==-1 && c[1]==3);

    auto fr = frac(v);
    TEST("frac", equal_epsilon(fr[0],0.5f));
}

// Sum / product / mean
void test_reduction()
{
    vec<int,3> v; v[0]=1; v[1]=2; v[2]=3;

    TEST("sum", sum(v)==6);
    TEST("product", product(v)==6);
    TEST("mean", equal_epsilon(mean(v), 2.0));
}

// Min / max components
void test_min_max_component()
{
    vec<int,3> v; v[0]=1; v[1]=5; v[2]=3;

    TEST("max_component", max_component(v)==5);
    TEST("min_component", min_component(v)==1);
}

// Add / mult
void test_variadic_ops()
{
    vec<int,3> a,b,c;
    a[0]=1; b[0]=2; c[0]=3;
    a[1]=1; b[1]=2; c[1]=3;
    a[2]=1; b[2]=2; c[2]=3;

    auto r = add(a,b,c);
    TEST("add variadic", r[0]==6);

    auto m = mult(a,b,c);
    TEST("mult variadic", m[0]==6);
}

// Sub / diff
void test_sub_diff()
{
    vec<int,2> a,b;
    a[0]=5; a[1]=7;
    b[0]=2; b[1]=3;

    auto s = sub(a,b);
    TEST("sub", s[0]==3 && s[1]==4);

    auto d = diff(a,b);
    TEST("diff", d[0]==3 && d[1]==4);
}

// Distance
void test_distance()
{
    vec<int,2> a,b;
    a[0]=0; a[1]=0;
    b[0]=3; b[1]=4;

    TEST("distance", equal_epsilon(distance(a,b), 5.0));
    TEST("distance_sq", distance_sq(a,b)==25);
}

// Angles
void test_angles()
{
    vec<float,2> a,b;
    a[0]=1; a[1]=0;
    b[0]=0; b[1]=1;

    auto c = cos_angle_bw(a,b);
    TEST("cos_angle", equal_epsilon(c,0.0f));

    auto ang = angle_bw(a,b);
    TEST("angle", equal_epsilon(ang, static_cast<float>(M_PI/2)));
}

// Projection / rejection
void test_projection()
{
    vec<float,2> a,b;
    a[0]=3; a[1]=4;
    b[0]=1; b[1]=0;

    auto p = project(a,b);
    TEST("project", equal_epsilon(p[0],3.0f) && equal_epsilon(p[1],0.0f));

    auto r = reject(a,b);
    TEST("reject", equal_epsilon(r[0],0.0f) && equal_epsilon(r[1],4.0f));
}

// Lerp
void test_lerp()
{
    vec<float,2> a,b;
    a[0]=0; a[1]=0;
    b[0]=10; b[1]=10;

    auto r = lerp(a,b,0.5f);
    TEST("lerp", equal_epsilon(r[0],5.0f));
}

// Vec2
void test_vec2()
{
    vec2<int> v(3,4);

    TEST("vec2 access", v.x()==3 && v.y()==4);

    auto p = perp(v);
    TEST("vec2 perp", p.x()==4 && p.y()==-3);

    vec2<int> a(1,2), b(3,4);
    TEST("vec2 cross", cross(a,b)==-2);
}

// ---------- MAIN ----------
int main()
{
    std::cout << "Running FULL Euler Tests...\n\n";

    test_init();
    test_dot_length();
    test_scale();
    test_normalize();
    test_math_ops();
    test_reduction();
    test_min_max_component();
    test_variadic_ops();
    test_sub_diff();
    test_distance();
    test_angles();
    test_projection();
    test_lerp();
    test_vec2();

    std::cout << "\n-----------------------------\n";

    if (failed == 0)
    {
        std::cout << GREEN << "ALL TESTS PASSED (" << passed << ")" << RESET << "\n";
    }
    else
    {
        std::cout << RED
                  << "Passed: " << passed << " | Failed: " << failed
                  << RESET << "\n";
    }

    return failed == 0 ? 0 : 1;
}
