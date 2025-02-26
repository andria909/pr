#pragma once
#include <boost/multiprecision/cpp_int.hpp>
#include <cmath>
using namespace boost::multiprecision;

cpp_int phi(cpp_int n);
int jacobi(cpp_int q, cpp_int p);
cpp_int gcd(cpp_int a, cpp_int b);
cpp_int fast_pow(cpp_int base, cpp_int exp, cpp_int mod);
cpp_int pow(cpp_int base, cpp_int exp);
cpp_int is_perfect_pow(cpp_int n);
cpp_int find_smallest_r(cpp_int n);
cpp_int log2(cpp_int n);

