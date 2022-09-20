//
// Created by tammd on 9/7/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_REQUEST_READ_HPP_2AD9182F26364A4397B65CDD3A836D91
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_REQUEST_READ_HPP_2AD9182F26364A4397B65CDD3A836D91
#include <kafka/detail/endian.hpp>
#include <kafka/detail/response_read.hpp>
#include <kafka/primitives.hpp>
#include <kafka/response.hpp>

namespace kafka::detail
{

inline int8
read_int8(std::istream &is)
{
    int8 result = 0;
    is.read(reinterpret_cast< char * >(&result), sizeof(int8));
    return result;
}

inline int16
read_int16(std::istream &is)
{
    int16 result = 0;
    is.read(reinterpret_cast< char * >(&result), sizeof(int16));
    result = ntohs(result);
    return result;
}

inline int32
read_int32(std::istream &is)
{
    int32 result = 0;
    is.read(reinterpret_cast< char * >(&result), sizeof(int32));
    result = ntohl(result);
    return result;
}

inline int64
read_int64(std::istream &is)
{
    int64 result = 0;
    is.read(reinterpret_cast< char * >(&result), sizeof(int64));
    result = be_to_host_64(result);
    return result;
}

inline std::string
read_string(std::istream &is)
{
    int16 length = read_int16(is);
    if (length > 0)
    {
        std::string result(length, '\0');
        is.read(&result[0], length);
        return result;
    }
    return "";
}

inline void
read_bytes(std::istream &is, bytes &bytes)
{
    int32 length = read_int32(is);
    if (length > 0)
    {
        bytes.reset(new bytes::element_type(length, 0));
        is.read(reinterpret_cast< char * >(&(*bytes)[0]), length);
    }
}

template < typename TMutableResponse >
void
read_response(std::istream &is, TMutableResponse &response, boost::system::error_code &ec)
{
    response.set_correlation_id(read_int32(is));
    read_response_message(is, response, ec);
}

}   // namespace kafka::detail

#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_REQUEST_READ_HPP_2AD9182F26364A4397B65CDD3A836D91
