#include <boost/multiprecision/cpp_int.hpp>
#include <chrono>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include "utils.h"
 
using namespace boost::multiprecision;

#include <chrono>
#include <utility>

bool fermat_test(cpp_int n, int k) {
  if (n <= 1)
    return false;
  if (n <= 3)
    return true;
 
  for (int i = 0; i < k; ++i) {
    cpp_int a = 2 + rand() % (n - 3);
    cpp_int x = fast_pow(a, n - 1, n);
    if (x != 1) {
      return false;
    }
  }
  return true;
}
 
bool solovay_shtressen_test(cpp_int n, int k) {
  if (n <= 1) return false;
  if (n <= 3) return true;

  for (int i = 0; i < k; ++i) {
      cpp_int a = 2 + rand() % (n - 3);
      if (gcd(a, n) > 1) {
          return false;
      }
      if ((fast_pow(a, (n - 1) / 2, n) + n) % n != (jacobi(a, n) + n) % n) {
          return false;
      }
  }
  return true;
}
 
bool miller_rabin_test(cpp_int n, int k) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
  
    cpp_int t = n - 1;
    int s = 0;
    while (t % 2 == 0) {
      t /= 2;
      ++s;
    }
    for (int i = 0; i < k; ++i) {
      cpp_int a = 2 + rand() % (n - 4);
      cpp_int x = fast_pow(a, t, n);
      
      if (x != 1 && x != n - 1) {
        bool fl = true;
        for (int j = 0; j < s && fl; ++j) {
          x = (x * x) % n;
          if (x == 1) return false;
          if (x == n - 1) fl = false;
        }
        if (fl) return false;
      }
    }
    return true;
  }

  bool aks_test(cpp_int n) {
    if (n < 2) return false;
    if (is_perfect_pow(n)) return false;
    cpp_int r = find_smallest_r(n);
    for (cpp_int a = 2; a <= r; ++a) {
        if (gcd(a, n) > 1 && gcd(a, n) < n) return false;
    }
    if (n <= r) return true;
    cpp_int limit = sqrt(phi(r)) * log2(n);
    for (cpp_int a = 1; a <= limit; ++a) {
        if (fast_pow(a, n, n) != a % n) return false;
    }
    return true;
}


 