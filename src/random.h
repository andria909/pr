#pragma once
#include "longnum.h"
#include <boost/random.hpp>
#include <ctime>
#include <stdexcept>

namespace bpm {
class Random {
public:
  explicit Random(int seed = k_default_seed_);
  Random(bool use_time_seed);

  LongInt uniform(LongInt a, LongInt b);

private:
  static constexpr int k_default_seed_ = 42;
  boost::random::mt19937 generator_;
};
} // namespace bpm
