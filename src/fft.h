#pragma once
#include "longnum.h"
#include <complex>
#include <vector>


namespace bpm {
using base = std::complex<LongDouble>;

LongDouble factorial(int n);
LongDouble my_sin(LongDouble x);
LongDouble my_cos(LongDouble x);

void fft(std::vector<base> &a, bool invert);
std::vector<LongInt> multiply(const std::vector<LongInt> &a,
                              const std::vector<LongInt> &b,
                              const LongInt &mod_n);

std::vector<LongInt> power_mod(const std::vector<LongInt> &base,
                               LongInt exponent, const LongInt &r,
                               const LongInt &mod_n);
bool check_congruence(const LongInt &a, const LongInt &n, const LongInt &r);
} // namespace bpm