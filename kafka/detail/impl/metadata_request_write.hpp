//
// Created by tammd on 9/10/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_METADATA_REQUEST_WRITE_HPP_8E660AC1D74D4F1BA3ECB7B1AA812A52
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_METADATA_REQUEST_WRITE_HPP_8E660AC1D74D4F1BA3ECB7B1AA812A52

#include <kafka/primitives.hpp>
#include <kafka/metadata_request.hpp>

namespace kafka::detail
{

inline int32 request_message_wire_size(const metadata_request& request)
{
  int32 size = sizeof(int32);
  for(const std::string& topic_name: request.topic_names())
  {
    size += string_wire_size(topic_name);
  }
  return size;
}

inline void write_request_message(const metadata_request& request,
                                std::ostream& os)
{
  // Topic Names
  write_int32(static_cast<int32>(request.topic_names().size()), os);
  for(const std::string& topic_name: request.topic_names())
  {
    write_string(topic_name, os);
  }
}

}
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_METADATA_REQUEST_WRITE_HPP_8E660AC1D74D4F1BA3ECB7B1AA812A52
