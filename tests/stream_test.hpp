//
// Created by tammd on 9/17/22.
//

#ifndef CONNECTOR_APPS_KAFKA_TEST_STREAM_TEST_HPP_0520166F074A458180872F8CF060D026
#define CONNECTOR_APPS_KAFKA_TEST_STREAM_TEST_HPP_0520166F074A458180872F8CF060D026

#include <boost/asio/streambuf.hpp>
#include <boost/shared_ptr.hpp>
#include <kafka/primitives.hpp>

#include <iostream>

// Little helper for testing stream based operations
struct stream_test
{
    void
    reset_stream()
    {
        streambuf.reset(new boost::asio::streambuf());
        stream.reset(new std::iostream(streambuf.get()));
    }

    kafka::bytes
    read_everything()
    {
        using kafka::bytes;
        bytes result(new bytes::element_type());
        while (stream->good())
        {
            char c = 0;
            stream->get(c);
            if (stream->good())
            {
                result->push_back(c);
            }
        }
        return result;
    }

    using stream_buf_type = boost::shared_ptr< boost::asio::streambuf >;
    using stream_type     = boost::shared_ptr< std::iostream >;
    stream_buf_type streambuf;
    stream_type     stream;
};

#endif   // CONNECTOR_APPS_KAFKA_TEST_STREAM_TEST_HPP_0520166F074A458180872F8CF060D026
