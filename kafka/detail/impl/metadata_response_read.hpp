//
// Created by tammd on 9/10/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_METADATA_RESPONSE_READ_HPP_0F249A3B9B7A4C5AA078F039DAB8BA22
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_METADATA_RESPONSE_READ_HPP_0F249A3B9B7A4C5AA078F039DAB8BA22


#include <kafka/primitives.hpp>
#include <kafka/metadata_response.hpp>
#include <kafka/error.hpp>
#include <kafka/response.hpp>
#include <kafka/detail/response_read.hpp>

namespace kafka::detail
{

inline void read_response_message(std::istream& is,
                                mutable_metadata_response& response,
                                boost::system::error_code& ec)
{
  // error code not used
  (void)ec;
  // Brokers
  response.mutable_brokers().resize(read_int_32(is));
  for(metadata_response::broker_s& broker: response.mutable_brokers())
  {
    broker.node_id_ = read_int_32(is);
    broker.host_ = read_string(is);
    broker.port_ = read_int_32(is);
  }

  // Topic Metadata
  int topic_count = read_int_32(is);
  for (int t = 0; t < topic_count; ++t)
  {
    metadata_response::topics_t::key_type key;
    metadata_response::topics_t::mapped_type topic;
    topic.error_code_ = read_int_16(is);
    key = read_string(is);

    int partition_count = read_int_32(is);
    for (int p = 0; p < partition_count; ++p)
    {
      metadata_response::partitions_t ::key_type key;
      metadata_response::partitions_t::mapped_type partition;
      partition.error_code_ = read_int_16(is);
      key = read_int_32(is);
      partition.leader_ = read_int_32(is);

      int32 replicas_size = read_int_32(is);
      for (int32 k = 0; k < replicas_size; ++k)
      {
        partition.replicas_.push_back(read_int_32(is));
      }

      int32 isr_size = read_int_32(is);
      for (int32 k = 0; k < isr_size; ++k)
      {
        partition.isr_.push_back(read_int_32(is));
      }
      topic.partitions_.insert(std::make_pair(key, partition));
    }
    response.mutable_topics().insert(std::make_pair(key, topic));
  }
}

}
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_METADATA_RESPONSE_READ_HPP_0F249A3B9B7A4C5AA078F039DAB8BA22
