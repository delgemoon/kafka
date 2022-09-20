//
// Created by tammd on 9/11/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_PRODUCTE_REQUEST_WRITE_HPP_3358795BA5304FA0B091C66D9D635B69
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_PRODUCTE_REQUEST_WRITE_HPP_3358795BA5304FA0B091C66D9D635B69
#include <kafka/primitives.hpp>
#include <kafka/detail/request_write.hpp>
#include <kafka/produce_request.hpp>
namespace kafka::detail
{
inline int32 request_message_wire_size(const produce_request& request)
{
  int32 size =
    sizeof(int16) +  // RequiredAcks
    sizeof(int32);   // Timeout

  // Topic Array
  size += sizeof(int32);
  for(const produce_request::topic_t & topic : request.topics())
  {
    size += string_wire_size(topic.topic_name_);

    // Partition array
    size += sizeof(int32);
    for(const produce_request::partition_t & partition:
                  topic.partitions_)
    {
      size +=
        sizeof(int32) +  // Partition
        sizeof(int32) +  // MessageSetSize
        message_set_wire_size(partition.messages_);  // MessageSet
    }
  }
  return size;
}

inline void write_request_message(metadata_request request, std::ostream& os)
{
  write_int16(request.required_acks(), os);
  write_int32(request.timeout(), os);

  // Topic Array
  write_int32(static_cast<int32>(request.topics().size()), os);
  for(const produce_request::topic_t& topic: request.topics())
  {
    write_string(topic.topic_name_, os);

    // Partition Array
    write_int32(static_cast<int32>(topic.partitions_.size()), os);
    for(const produce_request::partition_t& partition:
                  topic.partitions_)
    {
      write_int32(partition.partition_, os);
      write_int32(message_set_wire_size(partition.messages_), os);
      write_message_set(partition.messages_, os);
    }
  }
}

}
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_PRODUCTE_REQUEST_WRITE_HPP_3358795BA5304FA0B091C66D9D635B69
