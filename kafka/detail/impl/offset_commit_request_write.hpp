//
// Created by tammd on 9/10/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_OFFSET_COMMIT_REQUEST_WRITE_HPP_D2778E7F5B344A0BBEB8D3AA093D9AC7
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_OFFSET_COMMIT_REQUEST_WRITE_HPP_D2778E7F5B344A0BBEB8D3AA093D9AC7

#include <kafka/detail/request_write.hpp>
#include <kafka/offset_commit_request.hpp>

namespace kafka::detail
{
inline int32 request_message_wire_size(const offset_commit_request& request)
{
  int32 size = string_wire_size(request.consumer_group());

  // Topics Array
  size += sizeof(int32);
  for(const offset_commit_request::topic_t & topic : request.topics())
  {
    // Partitions Array
    size += sizeof(int32);
    for(const offset_commit_request::partition_t & partition :
                  topic.partitions_)
    {
      size +=
        sizeof(int32) +  // Partition
        sizeof(int64) +  // Offset
        sizeof(int64) +  // Timestamp
        string_wire_size(partition.metadata_);  // Metadata
    }
  }
  return size;
}

inline void write_request_message(const offset_commit_request& request,
                                std::ostream& os)
{
  write_string(request.consumer_group(), os);

  // Topics Array
  write_int32(static_cast<int32>(request.topics().size()), os);
  for(const offset_commit_request::topic_t& topic : request.topics())
  {
    write_string(topic.topic_name_, os);

    // Partitions Array
    write_int32(static_cast<int32>(topic.partitions_.size()), os);
    for(const offset_commit_request::partition_t & partition:
                  topic.partitions_)
    {
      write_int32(partition.partition_, os);
      write_int64(partition.offset_, os);
      write_int64(partition.timestamp_, os);
      write_string(partition.metadata_, os);
    }
  }
}
}
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_OFFSET_COMMIT_REQUEST_WRITE_HPP_D2778E7F5B344A0BBEB8D3AA093D9AC7
