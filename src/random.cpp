#include "random.h"
namespace bpm {
Random::Random(int seed) : generator_(seed) {}

Random::Random(bool use_time_seed) {
  if (use_time_seed) {
    generator_.seed(std::time(nullptr));
  }
}

LongInt Random::uniform(LongInt a, LongInt b) {
  if (a > b) {
    std::swap(a, b);
  }

  boost::random::uniform_int_distribution<LongInt> dist(a, b);
  return dist(generator_);
}
} // namespace bpm