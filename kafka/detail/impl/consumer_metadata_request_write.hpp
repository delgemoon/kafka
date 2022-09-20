//
// Created by tammd on 9/7/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_CONSUMER_METADATA_REQUEST_WRITE_HPP_228C91A6B9B0485D87957BC0F7FD111A
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_CONSUMER_METADATA_REQUEST_WRITE_HPP_228C91A6B9B0485D87957BC0F7FD111A

#include <kafka/consumer_metadata_request.hpp>
#include <kafka/detail/request_write.hpp>
#include <kafka/error.hpp>
#include <kafka/primitives.hpp>

namespace kafka::detail
{

inline int32
request_message_wire_size(const consumer_metadata_request &request)
{
    return string_wire_size(request.consumer_group());
}

inline void
write_request_message(const consumer_metadata_request &request, std::ostream &os)
{
    write_string(request.consumer_group(), os);
}

}   // namespace kafka::detail
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_CONSUMER_METADATA_REQUEST_WRITE_HPP_228C91A6B9B0485D87957BC0F7FD111A
