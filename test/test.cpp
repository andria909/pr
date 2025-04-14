#include "../src/prime_tests.cpp"
#include "test_data.cpp"

using namespace bpm;

TEST(FermatTest, PrimeNumbers) {
  for (int i = 0; i < primes.size(); ++i) {
    for (int j = 0; j < primes[i].size(); ++j) {
      try {
        EXPECT_EQ(ferma_test(primes[i][j], 2 * i + 1),
                  TestStatus::ProbablyPrime);
      } catch (...) {
        std::cout << "ferma test faled " << primes[i][j] << std::endl;
      }
    }
  }

  for (int i = 0; i < big_primes.size(); ++i) {
    try {
      EXPECT_EQ(ferma_test(big_primes[i], 1000), TestStatus::ProbablyPrime);
    } catch (...) {
      std::cout << "ferma test faled " << big_primes[i] << std::endl;
    }
  }
}

TEST(FermatTest, CompositeNumbers) {
  for (int i = 0; i < composite.size(); ++i) {
    for (int j = 0; j < composite[i].size(); ++j) {
      try {
        EXPECT_EQ(ferma_test(composite[i][j], 2 * i + 1),
                  TestStatus::Composite);
      } catch (...) {
        std::cout << "ferma test faled " << composite[i][j] << std::endl;
      }
    }
  }

  for (int i = 0; i < big_composite.size(); ++i) {
    try {
      EXPECT_EQ(ferma_test(big_composite[i], 1000), TestStatus::Composite);
    } catch (...) {
      std::cout << "ferma test faled " << big_composite[i] << std::endl;
    }
  }
}

TEST(FermatTest, Carmichael) {
  for (int i = 0; i < carmichael.size(); ++i) {
    try {
      EXPECT_EQ(ferma_test(carmichael[i], 100), TestStatus::Composite);
    } catch (...) {
      std::cout << "ferma test faled " << carmichael[i] << std::endl;
    }
  }
}

TEST(SolovayStrassenTest, PrimeNumbers) {
  for (int i = 0; i < primes.size(); ++i) {
    for (int j = 0; j < primes[i].size(); ++j) {
      try {
        EXPECT_EQ(solovay_shtressen_test(primes[i][j], 2 * i + 1),
                  TestStatus::ProbablyPrime);
      } catch (...) {
        std::cout << "solovay-strassen test faled " << primes[i][j]
                  << std::endl;
      }
    }
  }

  for (int i = 0; i < big_primes.size(); ++i) {
    try {
      EXPECT_EQ(solovay_shtressen_test(big_primes[i], 1000),
                TestStatus::ProbablyPrime);
    } catch (...) {
      std::cout << "solovay-strassen test faled " << big_primes[i] << std::endl;
    }
  }
}

TEST(SolovayStrassenTest, CompositeNumbers) {
  for (int i = 0; i < composite.size(); ++i) {
    for (int j = 0; j < composite[i].size(); ++j) {
      try {
        EXPECT_EQ(solovay_shtressen_test(composite[i][j], 2 * i + 1),
                  TestStatus::Composite);
      } catch (...) {
        std::cout << "solovay-strassen test faled " << composite[i][j]
                  << std::endl;
      }
    }
  }

  for (int i = 0; i < big_composite.size(); ++i) {
    try {
      EXPECT_EQ(solovay_shtressen_test(big_composite[i], 1000),
                TestStatus::Composite);
    } catch (...) {
      std::cout << "solovay-strassen test faled " << big_composite[i]
                << std::endl;
    }
  }
}

TEST(MillerRabinTest, PrimeNumbers) {
  for (int i = 0; i < primes.size(); ++i) {
    for (int j = 0; j < primes[i].size(); ++j) {
      try {
        EXPECT_EQ(miller_rabin_test(primes[i][j], 2 * i + 1),
                  TestStatus::ProbablyPrime);
      } catch (...) {
        std::cout << "miller-rabin test faled " << primes[i][j] << std::endl;
      }
    }
  }

  for (int i = 0; i < big_primes.size(); ++i) {
    try {
      EXPECT_EQ(miller_rabin_test(big_primes[i], 1000),
                TestStatus::ProbablyPrime);
    } catch (...) {
      std::cout << "miller-rabin test faled " << big_primes[i] << std::endl;
    }
  }
}

TEST(MillerRabinTest, CompositeNumbers) {
  for (int i = 0; i < composite.size(); ++i) {
    for (int j = 0; j < composite[i].size(); ++j) {
      try {
        EXPECT_EQ(miller_rabin_test(composite[i][j], 2 * i + 1),
                  TestStatus::Composite);
      } catch (...) {
        std::cout << "miller-rabin test faled " << composite[i][j] << std::endl;
      }
    }
  }

  for (int i = 0; i < big_composite.size(); ++i) {
    try {
      EXPECT_EQ(miller_rabin_test(big_composite[i], 1000),
                TestStatus::Composite);
    } catch (...) {
      std::cout << "miller-rabin test faled " << big_composite[i] << std::endl;
    }
  }
}

TEST(AKSTest, PrimeNumbers) {
  for (int i = 0; i < primes.size(); ++i) {
    for (int j = 0; j < primes[i].size(); ++j) {
      try {
        EXPECT_EQ(aks_test(primes[i][j]), TestStatus::Prime);
      } catch (...) {
        std::cout << "AKS test faled " << primes[i][j] << std::endl;
      }
    }
  }

  for (int i = 0; i < big_primes.size(); ++i) {
    try {
      EXPECT_EQ(aks_test(big_primes[i]), TestStatus::Prime);
    } catch (...) {
      std::cout << "AKS test faled " << big_primes[i] << std::endl;
    }
  }
}

TEST(AKSTest, CompositeNumbers) {
  for (int i = 0; i < composite.size(); ++i) {
    for (int j = 0; j < composite[i].size(); ++j) {
      try {
        EXPECT_EQ(aks_test(composite[i][j]), TestStatus::Composite);
      } catch (...) {
        std::cout << "AKS test faled " << composite[i][j] << std::endl;
      }
    }
  }

  for (int i = 0; i < big_composite.size(); ++i) {
    try {
      EXPECT_EQ(aks_test(big_composite[i]), TestStatus::Composite);
    } catch (...) {
      std::cout << "AKS test faled " << big_composite[i] << std::endl;
    }
  }
}

TEST(FactorizationTest, PrimeNumbers) {
  for (int i = 0; i < primes.size(); ++i) {
    for (int j = 0; j < primes[i].size(); ++j) {
      try {
        EXPECT_EQ(factorization_test(primes[i][j]), TestStatus::Prime);
      } catch (...) {
        std::cout << "factorization test faled " << primes[i][j] << std::endl;
      }
    }
  }

  for (int i = 0; i < big_primes.size(); ++i) {
    try {
      EXPECT_EQ(factorization_test(big_primes[i]), TestStatus::Prime);
    } catch (...) {
      std::cout << "factorization test faled " << big_primes[i] << std::endl;
    }
  }
}

TEST(FactorizationTest, CompositeNumbers) {
  for (int i = 0; i < composite.size(); ++i) {
    for (int j = 0; j < composite[i].size(); ++j) {
      try {
        EXPECT_EQ(factorization_test(composite[i][j]), TestStatus::Composite);
      } catch (...) {
        std::cout << "factorization test faled " << composite[i][j]
                  << std::endl;
      }
    }
  }

  for (int i = 0; i < big_composite.size(); ++i) {
    try {
      EXPECT_EQ(factorization_test(big_composite[i]), TestStatus::Composite);
    } catch (...) {
      std::cout << "factorization test faled " << big_composite[i] << std::endl;
    }
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
