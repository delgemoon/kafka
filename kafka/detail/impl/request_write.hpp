//
// Created by tammd on 9/7/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_REQUEST_WRITE_HPP_7BC33B3218FD49B3928E275873612D5D
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_REQUEST_WRITE_HPP_7BC33B3218FD49B3928E275873612D5D

#include <arpa/inet.h>
#include <kafka/detail/endian.hpp>
#include <kafka/detail/request_write.hpp>

#include <fstream>
#include <iostream>

namespace kafka::detail
{

inline int32
string_wire_size(const std::string &str)
{
    return static_cast< int32 >(sizeof(int16) + str.size());
}

inline int32
bytes_wire_size(const bytes &bytes)
{
    int32 size = sizeof(int32);
    if (bytes)
    {
        size += static_cast< int32 >(bytes->size());
    }
    return size;
}

template < typename TRequest >
int32
request_wire_size(const TRequest &request, const std::string &client_id)
{
    return sizeof(int16) +                         // ApiKey
           sizeof(int16) +                         // ApiVersion
           sizeof(int32) +                         // CorrelationId
           detail::string_wire_size(client_id) +   // ClientId
           request_message_wire_size(request);     // RequestMessage
}

inline void
write_int8(int8 value, std::ostream &os)
{
    os.write(reinterpret_cast< char * >(&value), sizeof(int8));
}

inline void
write_int16(int16 value, std::ostream &os)
{
    value = htons(value);
    os.write(reinterpret_cast< char * >(&value), sizeof(int16));
}

inline void
write_int32(int32 value, std::ostream &os)
{
    value = htonl(value);
    os.write(reinterpret_cast< char * >(&value), sizeof(int32));
}

inline void
write_int64(int64 value, std::ostream &os)
{
    value = host_to_be_64(value);
    os.write(reinterpret_cast< char * >(&value), sizeof(int64));
}

inline void
write_string(const std::string &value, std::ostream &os)
{
    write_int16(static_cast< int16 >(value.size()), os);
    os.write(value.c_str(), value.size());
}

inline void
write_bytes(const bytes &value, std::ostream &os)
{
    if (!value)
    {
        write_int32(-1, os);
        return;
    }
    write_int32(static_cast< int32 >(value->size()), os);
    if (!value->empty())
    {
        os.write(reinterpret_cast< const char * >(&(*value)[0]), value->size());
    }
}

template < typename TRequest >
void
write_request(const TRequest &request, const std::string &client_id, std::ostream &os)
{
    write_int32(request_wire_size(request, client_id), os);
    write_int16(request.api_key(), os);
    write_int16(request.api_version(), os);
    write_int32(request.correlation_id(), os);
    write_string(client_id, os);
    Write_request_message(request, os);
}

}   // namespace kafka::detail
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_REQUEST_WRITE_HPP_7BC33B3218FD49B3928E275873612D5D
