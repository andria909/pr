#pragma once
#include "longnum.h"
#include <cmath>
#include <random>

namespace bpm {
LongInt phi(LongInt n);
LongInt make_free_of(LongInt p, LongInt &n);
LongInt jacobi(LongInt q, LongInt p);
LongInt gcd(LongInt a, LongInt b);
LongInt fast_pow(LongInt base, LongInt exp, LongInt mod);

LongInt poww(LongInt base, LongInt exp);
bool is_perfect_pow(LongInt n);
LongInt find_smallest_ord(LongInt n);
LongInt log2(LongInt n);
LongInt my_sqrt(std::vector<LongInt> &S, LongInt n);

std::vector<LongInt> compute_args(LongDouble x);
void creating_objects(std::unordered_map<LongInt, LongInt>& f, std::unordered_map<LongInt, std::vector<bool>>& vec_fact, LongInt A, LongInt T, LongInt n, int m);

std::vector<LongInt> make_base(LongInt P, LongInt n);
void decomposition(std::unordered_map<LongInt, LongInt> &f,
                   std::unordered_map<LongInt, std::vector<bool>> &vec_fact,
                   std::vector<LongInt> &S);

} // namespace bpm
