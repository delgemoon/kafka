//
// Created by tammd on 9/7/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_CONSUMER_METADATA_RESPONSE_READ_HPP_4A439F758FB241D2B108313E00BCABCE
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_CONSUMER_METADATA_RESPONSE_READ_HPP_4A439F758FB241D2B108313E00BCABCE
#include <kafka/consumer_metadata_response.hpp>
#include <kafka/detail/response_read.hpp>
#include <kafka/error.hpp>
#include <kafka/primitives.hpp>

namespace kafka::detail
{

inline void
read_response_message(std::istream &is, mutable_consumer_metadata_response &response, boost::system::error_code &ec)
{
    response.set_error_code(read_int_16(is));
    response.set_coordinator_id(read_int_32(is));
    response.set_coordinator_host(read_string(is));
    response.set_coordinator_port(read_int_32(is));
    if (response.response().error_code())
    {
        // ec = (kafka_error) response.response().error_code();
    }
}

}   // namespace kafka::detail

#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_CONSUMER_METADATA_RESPONSE_READ_HPP_4A439F758FB241D2B108313E00BCABCE
