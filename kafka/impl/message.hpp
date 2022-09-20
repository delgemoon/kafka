//
// Created by tammd on 9/9/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_IMPL_MESSAGE_HPP_8F258D1C0238477AA62816B048130BFF
#define CONNECTOR_DEPENDENCIES_KAFKA_IMPL_MESSAGE_HPP_8F258D1C0238477AA62816B048130BFF

#include <kafka/message.hpp>
#include <boost/asio.hpp>
#include <kafka/detail/impl/message_read.hpp>
#include <kafka/detail/impl/message_write.hpp>
#include <kafka/detail/compression.hpp>

namespace kafka
{
inline message::message() :
  attributes_(0),
  nested_message_set_(new message_set())
{
}

inline message::message(const message& orig, bool deep) :
  attributes_(orig.attributes_),
  nested_message_set_(orig.nested_message_set_)
{
  if (deep)
  {
    if (orig.key())
    {
      key_.reset(new bytes::element_type(*orig.key()));
    }
    if (orig.value())
    {
      value_.reset(new bytes::element_type(*orig.value()));
    }
    if (orig.nested_message_set_)
    {
      nested_message_set_.reset(new message_set(*orig.nested_message_set_));
    }
  }
  else
  {
    key_ = orig.key();
    value_ = orig.value();
    nested_message_set_ = orig.nested_message_set_;
  }
}

inline message& message::operator=(const message& rhs)
{
  attributes_ = rhs.attributes_;
  key_ = rhs.key_;
  value_ = rhs.value_;
  nested_message_set_ = rhs.nested_message_set_;
  return *this;
}

inline int8 message::magic_byte() const
{
  return 0;
}

inline int8 message::attributes() const
{
  return attributes_;
}

inline void message::set_attributes(int8 attributes)
{
  attributes_ = attributes;
}

inline const bytes& message::key() const
{
  return key_;
}

inline bytes& message::mutable_key()
{
  return key_;
}

inline const bytes& message::value() const
{
  return value_;
}

inline bytes& message::mutable_value()
{
  return value_;
}

inline const message_set & message::nested_message_set() const
{
  return *nested_message_set_;
}

inline message_set& message::mutable_nested_message_set()
{
  return *nested_message_set_;
}

inline constants::compression message::compression() const
{
  return constants::compression(attributes_ & 0x03);
}

inline message_and_offset::message_and_offset() :
  offset_(0)
{
}

inline message_and_offset::message_and_offset(const message& msg,
                                          int64 offset) :
  message(msg),
  offset_(offset)
{
}

inline int64 message_and_offset::offset() const
{
  return offset_;
}

inline void message_and_offset::set_offset(int64 offset)
{
  offset_ = offset;
}

inline message CompressMessageSet(const message_set& message_set,
                                  constants::compression compression,
                                  boost::system::error_code& ec)
{
  using boost::asio::buffer;
  using boost::asio::buffer_copy;
  using boost::asio::streambuf;
  using boost::system::error_code;
  using detail::write_message_set;
  using detail::compress;

  if (compression == constants::kCompressionNone)
  {
    ec = kErrorCompressionFailed;
    return message();
  }
  streambuf intermediate_buffer;
  std::ostream intermediate_os(&intermediate_buffer);
  write_message_set(message_set, intermediate_os);
  size_t size = intermediate_buffer.size();
  if (size == 0)
  {
    ec = kErrorCompressionFailed;
    return message();
  }
  intermediate_buffer.commit(size);
  bytes uncompressed_value(new bytes::element_type(size));
  buffer_copy(buffer(&(*uncompressed_value)[0], size),
              intermediate_buffer.data());
  message result;
  result.set_attributes(compression);
  result.mutable_value() = compress(uncompressed_value, compression, ec);
  if (ec)
  {
    return message();
  }
  ec = kErrorSuccess;
  return result;
}

}
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_IMPL_MESSAGE_HPP_8F258D1C0238477AA62816B048130BFF
