//
// Created by tammd on 9/10/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_OFFSET_REQUEST_READ_HPP_2204A871B8984C5FB4C93AB2CC352711
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_OFFSET_REQUEST_READ_HPP_2204A871B8984C5FB4C93AB2CC352711


#include <kafka/primitives.hpp>
#include <kafka/detail/request_write.hpp>
#include <kafka/offset_request.hpp>


namespace kafka::detail
{

inline int32 request_message_wire_size(const offset_request& request)
{
  int32 size = sizeof(int32);  // ReplicaId

  // Topics array
  size += sizeof(int32);
  for(const offset_request::topic_t & topic: request.topics())
  {
    size += string_wire_size(topic.topic_name_);

    // Partitions array
    size += sizeof(int32);
    size += static_cast<int32>(topic.partitions_.size() * (
      sizeof(int32) +  // Partition
      sizeof(int64) +  // Time
      sizeof(int32))); // MaxNumberOfOffsets
  }
  return size;
}

inline void write_request_message(const offset_request& request, std::ostream& os)
{
  write_int32(request.replica_id(), os);

  // Topics array
  write_int32(static_cast<int32>(request.topics().size()), os);
  for(const offset_request::topic_t& topic: request.topics())
  {
    write_string(topic.topic_name_, os);

    // Partitions array
    write_int32(static_cast<int32>(topic.partitions_.size()), os);
    for(const offset_request::partition_t& partition : topic.partitions_)
    {
      write_int32(partition.partition_, os);
      write_int64(partition.time_, os);
      write_int32(partition.max_number_of_offsets_, os);
    }
  }
}
}
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_OFFSET_REQUEST_READ_HPP_2204A871B8984C5FB4C93AB2CC352711
