//
// Created by tammd on 9/7/22.
//

#include <doctest/doctest.h>
#include <kafka/detail/response_read.hpp>
#include <kafka/error.hpp>
#include <kafka/message.hpp>

#include <iostream>
#include <sstream>
#include <vector>

using namespace std::literals;
inline constexpr const std::uint8_t operator"" _us(char s)
{
    return (const std::uint8_t)s;
}
TEST_CASE("response_read_simple")
{
    std::stringstream ss;
    ss << '\x11' << '\x12' << '\x12';
    kafka::int8 int_8 = kafka::detail::read_int8(ss);
    std::cout << std::hex << int_8 << "\n";
    DOCTEST_CHECK_EQ(int_8, 0x11);
    kafka::int16 int_16 = kafka::detail::read_int16(ss);
    DOCTEST_CHECK_EQ(int_16, 0x1212);
    ss << '\x23' << '\x24' << '\x25' << '\x26';
    auto int_32 = kafka::detail::read_int32(ss);
    DOCTEST_CHECK_EQ(int_32, 0x23242526);
    ss << '\x27' << '\x27' << '\x27' << '\x27' << '\x27' << '\x27' << '\x27' << '\x27';
    auto int_64 = kafka::detail::read_int64(ss);
    DOCTEST_CHECK_EQ(int_64, 0x2727272727272727);

    ss << '\x00' << '\x06' << "FOOBAR";
    auto str = kafka::detail::read_string(ss);
    DOCTEST_CHECK_EQ(str, "FOOBAR");

    ss << '\x00' << '\x00' << '\x00' << '\05' << '\x27' << '\x27' << '\x27' << '\x27' << '\x27';
    kafka::bytes r_b;
    kafka::detail::read_bytes(ss, r_b);
    DOCTEST_CHECK_EQ(r_b->size(), 5);
    DOCTEST_CHECK_EQ(*r_b, std::vector { '\x27'_us, '\x27'_us, '\x27'_us, '\x27'_us, '\x27'_us });
}

TEST_CASE("response_read_complex")
{
    // MessageSet that contains 2 messages: `foo` and `bar`
    const unsigned char test_data[58] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11,
                                          0xfa, 0x8b, 0x1b, 0x4c, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
                                          0x00, 0x03, 0x66, 0x6f, 0x6f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                          0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x07, 0xf2, 0xc7, 0x00, 0x00, 0xff,
                                          0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x03, 0x62, 0x61, 0x72 };
    std::stringstream   ss;
    ss.write((const char *)test_data, sizeof(test_data));
    kafka::message_set        sets;
    boost::system::error_code ec;
    kafka::detail::read_message_set(ss, sets, sizeof(test_data), ec);
    // DOCTEST_CHECK_EQ(kafka::client_error::kErrorSuccess, ec);
    DOCTEST_CHECK_EQ(2, sets.size());
    DOCTEST_CHECK_EQ(static_cast< bool >(sets[0].value()), true);
    DOCTEST_CHECK_EQ(static_cast< bool >(sets[1].value()), true);
    std::string message_value_0((const char *)&(*sets[0].value())[0], sets[0].value()->size());
    std::string message_value_1((const char *)&(*sets[1].value())[0], sets[1].value()->size());
    DOCTEST_CHECK_EQ("foo", message_value_0.c_str());
    DOCTEST_CHECK_EQ("bar", message_value_1.c_str());
}