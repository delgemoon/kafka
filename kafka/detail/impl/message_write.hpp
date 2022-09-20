//
// Created by tammd on 9/9/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_MESSAGE_WRITE_HPP_5ED0232AD49B4038BDC6E5948087A860
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_MESSAGE_WRITE_HPP_5ED0232AD49B4038BDC6E5948087A860
#include <boost/asio.hpp>
#include <kafka/primitives.hpp>
#include <kafka/message.hpp>
#include <kafka/detail/request_write.hpp>
#include <boost/crc.hpp>

namespace kafka::detail
{

inline int32 message_wire_size(const message& message)
{
  return
    sizeof(int32) +  // Crc
    sizeof(int8) +   // MagicByte
    sizeof(int8) +   // Attributes
    bytes_wire_size( message.key() ) +  // Key
    bytes_wire_size( message.value() );  // Value
}

inline int32 message_set_wire_size(const message_set & message_set)
{
  int32 size = 0;
  for(const message_and_offset &message : message_set)
  {
    size +=
      sizeof(int64) +  // Offset
      sizeof(int32) +  // MessageSize
      message_wire_size(message);  // Message
  }
  return size;
}

inline void write_message(const message& value, std::ostream& os)
{
  using boost::asio::buffer_cast;

  // Write everything (except crc) to an intermediate buffer
  boost::asio::streambuf intermediate_buffer;
  std::ostream intermediate_os(&intermediate_buffer);
  write_int8(value.magic_byte(), intermediate_os);
  write_int8(value.attributes(), intermediate_os);
  write_bytes(value.key(), intermediate_os);
  write_bytes(value.value(), intermediate_os);

  size_t size = intermediate_buffer.size();
  intermediate_buffer.commit(size);

  // Calculate crc
  boost::crc_32_type crc;
  crc.process_bytes(buffer_cast<void const*>(intermediate_buffer.data()), size);

  // Write to the real stream
  write_int32(crc.checksum(), os);
  os.write(buffer_cast<const char*>(intermediate_buffer.data()), size);
}

inline void write_message_set(const message_set & value, std::ostream& os)
{
  for(const message_and_offset &message: value)
  {
    write_int64(message.offset(), os);
    write_int32(message_wire_size(message), os);
    write_message(message, os);
  }
}

}
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_MESSAGE_WRITE_HPP_5ED0232AD49B4038BDC6E5948087A860
