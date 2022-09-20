//
// Created by tammd on 9/10/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_OFFSET_FETCH_REQUEST_WRITE_HPP_35B54CFD3CD943DF82571527D4BC38E7
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_OFFSET_FETCH_REQUEST_WRITE_HPP_35B54CFD3CD943DF82571527D4BC38E7

#include <kafka/detail/request_write.hpp>
#include <kafka/offset_fetch_request.hpp>
namespace kafka::detail
{
inline int32 write_request_message(const offset_fetch_request& request)
{
  int32 size = string_wire_size(request.consumer_group());
  // Topics Array
  size += sizeof(int32);
  for(const offset_fetch_request::topic_t & topic : request.topics())
  {
    size += string_wire_size(topic.topic_name_);
    // Partitions Array
    size += sizeof(int32);
    size += static_cast<int32>(topic.partitions_.size()) * sizeof(int32);
  }
  return size;
}

inline void write_request_message(const offset_fetch_request& request,
                                std::ostream& os)
{
  write_string(request.consumer_group(), os);
  // Topics Array
  write_int32(static_cast<int32>(request.topics().size()), os);
  for(const offset_fetch_request::topic_t & topic: request.topics())
  {
    write_string(topic.topic_name_, os);
    // Partitions Array
    write_int32(static_cast<int32>(topic.partitions_.size()), os);
    for(const offset_fetch_request::partition_t partition :
                  topic.partitions_)
    {
      write_int32(partition.partition_, os);
    }
  }
}
}
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_OFFSET_FETCH_REQUEST_WRITE_HPP_35B54CFD3CD943DF82571527D4BC38E7
