//
// Created by tammd on 9/9/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_MESSAGE_READ_HPP_CEA49B04B1E84BF988DCAE20CF967783
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_MESSAGE_READ_HPP_CEA49B04B1E84BF988DCAE20CF967783

#include <boost/asio.hpp>
#include <kafka/detail/byte_streambuf.hpp>
#include <iostream>
#include <kafka/message.hpp>
#include <boost/system.hpp>
#include <kafka/detail/compression.hpp>
#include <kafka/primitives.hpp>
#include <kafka/detail/response_read.hpp>

namespace kafka::detail
{
inline void read_message(std::istream& is,
                        message& message,
                        boost::system::error_code& ec)
{
  int32 crc = read_int32(is);
  int8 magic_byte = read_int8(is);
  // discarding results of above reads
  (void)crc;
  (void)magic_byte;

  message.set_attributes(read_int8(is));
  read_bytes(is, message.mutable_key());
  read_bytes(is, message.mutable_value());
  bytes data = decompress(message.value(), message.compression(), ec);
  if (!ec && data && !data->empty())
  {
    byte_streambuf intermediate_buffer(data);
    std::istream intermediate_is(&intermediate_buffer);
    read_message_set(intermediate_is, message.mutable_nested_message_set(),
                   data->size(), ec);
  }
}

inline void read_message_set(std::istream& is,
                           message_set & message_set,
                           size_t size,
                           boost::system::error_code& ec)
{
  size_t read_count = 0;
  while (read_count < size)
  {
    message_and_offset message;
    message.set_offset(read_int64(is));
    int32 message_size = read_int32(is);
    if ((int32) (size - read_count) < message_size)
    {
      // Ignore partial messages
      is.seekg(size - read_count, std::ios::cur);
      read_count = size;
    }
    else
    {
      read_message(is, message, ec);
      message_set.push_back(message);
      read_count += sizeof(int64) + sizeof(int32) + message_size;
    }
  }
}
}
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_MESSAGE_READ_HPP_CEA49B04B1E84BF988DCAE20CF967783
