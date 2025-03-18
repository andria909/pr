#pragma once
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <cmath>
#include <random>

using namespace boost::multiprecision;

cpp_int phi(cpp_int n);
cpp_int make_free_of(cpp_int p, cpp_int &n);
cpp_int jacobi(cpp_int q, cpp_int p);
cpp_int gcd(cpp_int a, cpp_int b);
cpp_int fast_pow(cpp_int base, cpp_int exp, cpp_int mod);

cpp_int poww(cpp_int base, cpp_int exp);
cpp_int is_perfect_pow(cpp_int n);
cpp_int find_smallest_r(cpp_int n);
cpp_int log2(cpp_int n);

cpp_int formula(cpp_dec_float_50 x);
std::vector<cpp_int> make_base(cpp_int P, cpp_int n);
void decomposition(std::unordered_map<cpp_int, cpp_int> &f,
                   std::unordered_map<cpp_int, std::vector<bool>> &vec_fact,
                   std::vector<cpp_int> &S);

void gauss(std::vector<std::vector<bool>> &A);
int find_pivot_row(const std::vector<std::vector<bool>>& mat, int col, int start_row);
void xor_rows(std::vector<bool>& target, const std::vector<bool>& source);
int find_pivot_col(const std::vector<std::vector<bool>>& mat, int row);
std::vector<std::vector<bool>>
find_basis(std::vector<std::vector<bool>> &A); 
std::vector<std::vector<bool>>
transpose(const std::vector<std::vector<bool>> &A);
std::vector<int>
find_leading_columns(const std::vector<std::vector<bool>> &A);
std::vector<bool>
create_basis_vector(int col, const std::vector<int> &leading,
                    const std::vector<std::vector<bool>> &At);
                       
cpp_int my_sqrt(std::vector<cpp_int> &S, cpp_int n);


class Random {
public:
  explicit Random(int seed = k_default_seed_);
  cpp_int uniform(cpp_int a, cpp_int b);

private:
  static constexpr int k_default_seed_ = 42;
  std::mt19937 generator_;

  cpp_int get_random(const cpp_int &range);
};