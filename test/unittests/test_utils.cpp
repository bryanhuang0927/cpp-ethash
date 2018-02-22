// Copyright 2018 Pawel Bylica.
// Licensed under the Apache License, Version 2.0. See the LICENSE file.

#include <ethash/utils.hpp>

#include <gtest/gtest.h>


class is_prime_positive_test : public ::testing::TestWithParam<size_t>
{
};

class is_prime_negative_test : public ::testing::TestWithParam<size_t>
{
};

TEST_P(is_prime_positive_test, primes)
{
    const size_t number = GetParam();
    EXPECT_TRUE(ethash::is_prime(number));
}
INSTANTIATE_TEST_CASE_P(primes, is_prime_positive_test,
    testing::Values(2, 3, 17, 19, 577, 2069, 3011, 7919, 142540787, 2147483647, 4294967291));

TEST_P(is_prime_negative_test, nonprimes)
{
    const size_t number = GetParam();
    EXPECT_FALSE(ethash::is_prime(number));
}
INSTANTIATE_TEST_CASE_P(nonprimes, is_prime_negative_test,
    testing::Values(0, 1, 4, 6, 8, 9, 10, 12, 14, 15, 16, 18, 32, 512, 2048, 8192));


class find_largest_prime_test : public ::testing::TestWithParam<std::pair<size_t, size_t>>
{
};

TEST_P(find_largest_prime_test, test)
{
    size_t upper_bound;
    size_t expected_prime;

    std::tie(upper_bound, expected_prime) = GetParam();

    size_t prime = ethash::find_largest_prime(upper_bound);
    EXPECT_EQ(prime, expected_prime);
}

/// Test pairs for find_largest_prime() are taken from generated ethash
/// light cache and full dataset sizes, picked 50 at random from each collection.
/// See https://github.com/ethereum/wiki/wiki/Ethash#data-sizes.
static std::pair<size_t, size_t> test_pairs[] = {{262144, 262139}, {415744, 415729},
    {440320, 440311}, {505856, 505823}, {593920, 593903}, {667648, 667643}, {970752, 970747},
    {972800, 972799}, {1064960, 1064957}, {1083392, 1083391}, {1112064, 1112057},
    {1122304, 1122287}, {1220608, 1220599}, {1335296, 1335289}, {1464320, 1464299},
    {1517568, 1517567}, {1638400, 1638353}, {1679360, 1679351}, {1873920, 1873889},
    {1949696, 1949657}, {1984512, 1984511}, {1994752, 1994743}, {2131968, 2131951},
    {2156544, 2156537}, {2385920, 2385919}, {2529280, 2529269}, {2535424, 2535413},
    {2568192, 2568191}, {2588672, 2588671}, {2600960, 2600957}, {2650112, 2650093},
    {2717696, 2717683}, {2727936, 2727919}, {2779136, 2779129}, {2828288, 2828281},
    {2865152, 2865131}, {3057664, 3057661}, {3250176, 3250157}, {3299328, 3299323},
    {3551232, 3551227}, {3575808, 3575783}, {3592192, 3592109}, {3719168, 3719167},
    {3813376, 3813353}, {3825664, 3825649}, {3887104, 3887083}, {3942400, 3942397},
    {4028416, 4028413}, {4098048, 4098043}, {4288512, 4288489}, {4345856, 4345849},
    {4454400, 4454399}, {8388608, 8388593}, {9633792, 9633787}, {10027008, 10026979},
    {10289152, 10289141}, {11337728, 11337727}, {20447232, 20447191}, {22216704, 22216673},
    {25755648, 25755619}, {29491200, 29491193}, {33488896, 33488891}, {35717120, 35717111},
    {36241408, 36241397}, {38273024, 38273023}, {39321600, 39321599}, {39452672, 39452671},
    {40828928, 40828927}, {41025536, 41025499}, {41484288, 41484271}, {46530560, 46530557},
    {50200576, 50200573}, {50724864, 50724859}, {52297728, 52297717}, {54394880, 54394877},
    {54788096, 54788089}, {61997056, 61997053}, {63242240, 63242239}, {65470464, 65470453},
    {65732608, 65732599}, {69009408, 69009371}, {70582272, 70582271}, {75104256, 75104243},
    {84279296, 84279277}, {88932352, 88932341}, {90963968, 90963967}, {92930048, 92930039},
    {93388800, 93388759}, {95354880, 95354879}, {96272384, 96272383}, {96534528, 96534523},
    {103022592, 103022537}, {103284736, 103284733}, {108265472, 108265459}, {109772800, 109772797},
    {110297088, 110297069}, {126287872, 126287809}, {129040384, 129040367}, {129171456, 129171439},
    {130482176, 130482173}, {131203072, 131203069}, {139264000, 139263953}, {140705792, 140705779},
    {142540800, 142540787}};
INSTANTIATE_TEST_CASE_P(test_pairs, find_largest_prime_test, testing::ValuesIn(test_pairs));

static std::pair<size_t, size_t> edge_cases[] = {
    {3, 3}, {4, 3}, {std::numeric_limits<uint32_t>::max(), 4294967291}};
INSTANTIATE_TEST_CASE_P(edge_cases, find_largest_prime_test, testing::ValuesIn(edge_cases));