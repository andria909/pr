#include "../src/main.cpp"
#include <boost/multiprecision/cpp_int.hpp>
#include <gtest/gtest.h>

using namespace boost::multiprecision;
using namespace std::chrono;



TEST(FermatTest, PrimeNumbers) {
    Random ferma;
    EXPECT_EQ(fermat_test(7, 10, ferma), TestStatus::ProbablyPrime);
    EXPECT_EQ(fermat_test(13, 10, ferma), TestStatus::ProbablyPrime);
    EXPECT_EQ(fermat_test(static_cast<cpp_int>("8683317618811886495518194401279999999"), 1000, ferma), TestStatus::ProbablyPrime);
}

TEST(FermatTest, CompositeNumbers) {
    Random ferma;
    EXPECT_EQ(fermat_test(9, 10, ferma), TestStatus::Composite);
    EXPECT_EQ(fermat_test(15, 10, ferma), TestStatus::Composite);
    EXPECT_EQ(fermat_test(static_cast<cpp_int>("8683317618811886495518194401279999999") * 7, 1000, ferma), TestStatus::Composite);
}

TEST(SolovayStrassenTest, PrimeNumbers) {
    Random solovay;
    EXPECT_EQ(solovay_shtressen_test(7, 10, solovay), TestStatus::ProbablyPrime);
    EXPECT_EQ(solovay_shtressen_test(13, 10, solovay), TestStatus::ProbablyPrime);
    EXPECT_EQ(solovay_shtressen_test(static_cast<cpp_int>("8683317618811886495518194401279999999"), 1000, solovay), TestStatus::ProbablyPrime);
}

TEST(SolovayStrassenTest, CompositeNumbers) {
    Random solovay;
    EXPECT_EQ(solovay_shtressen_test(9, 10, solovay), TestStatus::Composite);
    EXPECT_EQ(solovay_shtressen_test(15, 10, solovay), TestStatus::Composite);
    EXPECT_EQ(solovay_shtressen_test(static_cast<cpp_int>("8683317618811886495518194401279999999") * 7, 1000, solovay), TestStatus::Composite);
}

TEST(MillerRabinTest, PrimeNumbers) {
    Random miller;
    EXPECT_EQ(miller_rabin_test(7, 10, miller), TestStatus::ProbablyPrime);
    EXPECT_EQ(miller_rabin_test(13, 10, miller), TestStatus::ProbablyPrime);
    EXPECT_EQ(miller_rabin_test(static_cast<cpp_int>("8683317618811886495518194401279999999"), 1000, miller), TestStatus::ProbablyPrime);
}

TEST(MillerRabinTest, CompositeNumbers) {
    Random miller;
    EXPECT_EQ(miller_rabin_test(9, 10, miller), TestStatus::Composite);
    EXPECT_EQ(miller_rabin_test(15, 10, miller), TestStatus::Composite);
    EXPECT_EQ(miller_rabin_test(static_cast<cpp_int>("100003") * 100019, 1000, miller), TestStatus::Composite);
}

TEST(FactorizationTest, All) {
    EXPECT_EQ(factorization_test(static_cast<cpp_int>("997")), TestStatus::ProbablyPrime);
    EXPECT_EQ(factorization_test(static_cast<cpp_int>("10000079") * 1000003), TestStatus::Composite);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

