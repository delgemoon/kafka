//
// Created by tammd on 9/17/22.
//

#include "stream_test.hpp"

#include <doctest/doctest.h>
#include <kafka/kafka.hpp>

using kafka::metadata_request;

TEST_CASE("metadata_request_test_simple")
{
    stream_test stream;
    stream.reset_stream();
    metadata_request request;
    request.add_topic_name("Foo");
    request.add_topic_name("Bar");
    request.add_topic_name("Hello World!");
    kafka::detail::write_request_message(request, *(stream.stream));

    using namespace kafka::detail;
    CHECK_EQ(3, read_int32(*stream.stream));   // Topic array size
    CHECK_EQ("Foo", read_string(*stream.stream));
    CHECK_EQ("Bar", read_string(*stream.stream));
    CHECK_EQ("Hello World!", read_string(*stream.stream));

    // Nothing else ...
    CHECK_EQ(0, stream.streambuf->size());
}

TEST_CASE("metadata_request_test_empty")
{
    stream_test stream;
    stream.reset_stream();
    metadata_request request;
    kafka::detail::write_request_message(request, *stream.stream);

    using namespace kafka::detail;
    CHECK_EQ(0, read_int32(*stream.stream));   // Topic array size

    // Nothing else ...
    CHECK_EQ(0, stream.streambuf->size());
}
