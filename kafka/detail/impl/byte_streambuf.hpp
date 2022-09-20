//
// Created by tammd on 9/7/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_BYTE_STREAMBUF_HPP_748D3C44AEA345A08821BA59E9780E3A
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_BYTE_STREAMBUF_HPP_748D3C44AEA345A08821BA59E9780E3A

#include <kafka/detail/byte_streambuf.hpp>

namespace kafka::detail
{

inline byte_streambuf::byte_streambuf(bytes data)
: data_(data)
{
    if (data_ && !data->empty())
    {
        char_type *buffer_begin = reinterpret_cast< char_type * >(&(*data_)[0]);
        char_type *buffer_end   = buffer_begin + data->size();
        setg(buffer_begin, buffer_begin, buffer_end);
    }
}

inline bytes
byte_streambuf::data() const
{
    return data_;
}

}   // namespace kafka::detail
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_BYTE_STREAMBUF_HPP_748D3C44AEA345A08821BA59E9780E3A
