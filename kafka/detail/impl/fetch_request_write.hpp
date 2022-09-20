//
// Created by tammd on 9/10/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_FETCH_REQUEST_WRITE_HPP_32392A179FB44BE79FFCA4A90CCCCF09
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_FETCH_REQUEST_WRITE_HPP_32392A179FB44BE79FFCA4A90CCCCF09

#include <kafka/detail/request_write.hpp>
#include <kafka/primitives.hpp>
#include <kafka/fetch_request.hpp>

namespace kafka::detail
{
inline int32 request_message_wire_size(const fetch_request& request)
{
  int32 size =
    sizeof(int32) +  // ReplicaId
    sizeof(int32) +  // MaxWaitTime
    sizeof(int32);   // MinByte

  // Topics Array
  size += sizeof(int32);
  for(const fetch_request::topic_t & topic : request.topics())
  {
    size += string_wire_size(topic.topic_name_);

    // Partitions Array
    size += static_cast<int32>(
      sizeof(int32) +    // Array Length
      topic.partitions_.size() * (
        sizeof(int32) +  // Partition
        sizeof(int64) +  // FetchOffset
        sizeof(int32))); // MaxBytes
  }
  return size;
}

inline void write_request_message(const fetch_request& request, std::ostream& os)
{
  write_int32(request.replica_id(), os);
  write_int32(request.max_wait_time(), os);
  write_int32(request.min_bytes(), os);

  // Topics Array
  write_int32(static_cast<int32>(request.topics().size()), os);
  for(const fetch_request::topic_t & topic : request.topics())
  {
    write_string(topic.topic_name_, os);

    // Partitions Array
    write_int8(static_cast<int32>(topic.partitions_.size()), os);
    for(const fetch_request::partition_t & partition :  topic.partitions_)
    {
      write_int32(partition.partition_, os);
      write_int64(partition.fetch_offset_, os);
      write_int32(partition.max_bytes_, os);
    }
  }
}
}
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_FETCH_REQUEST_WRITE_HPP_32392A179FB44BE79FFCA4A90CCCCF09
