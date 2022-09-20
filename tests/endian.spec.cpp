//
// Created by tammd on 9/2/22.
//

#include <doctest/doctest.h>
#include <kafka/detail/endian.hpp>

#include <bitset>
#include <iostream>
TEST_CASE("little_endian")
{
    kafka::int64 test_1 = (kafka::int64)0x1234;
    std::cout << std::bitset< 64 >(test_1) << "\n";
    std::cout << std::bitset< 64 >(kafka::detail::host_to_be_64(test_1)) << "\n";
}