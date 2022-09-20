//
// Created by tammd on 9/1/22.
//

#ifndef CONNECTOR_LIB_KAFKA_DETAIL_RESPONSE_READ_HPP_23A67F2138D3407BB432E92A297E6F5D
#define CONNECTOR_LIB_KAFKA_DETAIL_RESPONSE_READ_HPP_23A67F2138D3407BB432E92A297E6F5D

#include <boost/system/error_code.hpp>
#include <kafka/message_fwd.hpp>
#include <kafka/primitives.hpp>
#include <kafka/response.hpp>

#include <iostream>

namespace kafka
{

struct mutable_metadata_response;

struct mutable_produce_response;

struct mutable_fetch_response;

struct mutable_offset_response;

struct mutable_consumer_metadata_response;

struct mutable_offset_commit_response;

struct mutable_offset_fetch_response;
namespace detail
{
    int8
    read_int8(std::istream &is);

    int16
    read_int16(std::istream &is);

    int32
    read_int32(std::istream &is);

    int64
    read_int64(std::istream &is);

    std::string
    read_string(std::istream &is);

    void
    read_bytes(std::istream &is, bytes &bytes);

    void
    read_message(std::istream &is, message &message, boost::system::error_code &ec);

    void
    read_message_set(std::istream &is, message_set &message_set, size_t size, boost::system::error_code &ec);

    template < typename TMutableResponse >
    void
    read_response(std::istream &is, TMutableResponse &response, boost::system::error_code &ec);

    void
    read_response_message(std::istream &is, mutable_metadata_response &response, boost::system::error_code &ec);

    void
    read_response_message(std::istream &is, mutable_produce_response &response, boost::system::error_code &ec);

    void
    read_response_message(std::istream &is, mutable_fetch_response &response, boost::system::error_code &ec);

    void
    read_response_message(std::istream &is, mutable_offset_response &response, boost::system::error_code &ec);

    void
    read_response_message(std::istream                       &is,
                          mutable_consumer_metadata_response &response,
                          boost::system::error_code          &ec);

    void
    read_response_message(std::istream &is, mutable_offset_commit_response &response, boost::system::error_code &ec);

    void
    read_response_message(std::istream &is, mutable_offset_fetch_response &response, boost::system::error_code &ec);

}   // namespace detail
}   // namespace kafka


#include <kafka/detail/impl/response_read.hpp>

#endif   // CONNECTOR_LIB_KAFKA_DETAIL_RESPONSE_READ_HPP_23A67F2138D3407BB432E92A297E6F5D
