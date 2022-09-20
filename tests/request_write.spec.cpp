//
// Created by tammd on 9/8/22.
//
#include <doctest/doctest.h>
#include <kafka/detail/request_write.hpp>
#include <kafka/detail/response_read.hpp>

#include <iostream>
#include <list>
#include <set>
#include <sstream>
#include <vector>

using namespace std::literals;
using namespace std;
inline constexpr const std::uint8_t operator"" _us(char s)
{
    return (const std::uint8_t)s;
}
TEST_CASE("response_read_simple")
{
    std::stringstream ss;
    kafka::detail::write_int8('\x23', ss);
    auto int_8_value = kafka::detail::read_int8(ss);
    DOCTEST_CHECK_EQ(int_8_value, '\x23');

    kafka::detail::write_int16(0x1234, ss);
    auto int_16_value = kafka::detail::read_int16(ss);
    DOCTEST_CHECK_EQ(int_16_value, 0x1234);

    kafka::detail::write_int32(0x12345678, ss);
    auto int_32_value = kafka::detail::read_int32(ss);
    DOCTEST_CHECK_EQ(int_32_value, 0x12345678);
}
