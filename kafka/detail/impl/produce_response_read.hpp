//
// Created by tammd on 9/11/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_PRODUCE_RESPONSE_READ_HPP_D3212112F23544129EA82AB8A9647C3B
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_PRODUCE_RESPONSE_READ_HPP_D3212112F23544129EA82AB8A9647C3B

#include <kafka/error.hpp>
#include <kafka/primitives.hpp>
#include <kafka/detail/response_read.hpp>
#include <kafka/produce_response.hpp>

namespace kafka::detail
{
inline void read_response_message(std::istream& is,
                                mutable_produce_response& response,
                                boost::system::error_code& ec)
{
  int topic_count = read_int_32(is);
  for (int t = 0; t < topic_count; ++t)
  {
    produce_response::topics_t::key_type key;
    produce_response::topics_t::mapped_type topic;
    key = read_string(is);

    int partition_count = read_int_32(is);
    for (int p = 0; p < partition_count; ++p)
    {
      produce_response::partitions_t::key_type key;
      produce_response::partitions_t::mapped_type partition;
      key = read_int_32(is);
      partition.error_code_ = read_int_16(is);
      partition.offset_ = read_int_64(is);

      if (partition.error_code_)
      {
        ec = (kafka_error) partition.error_code_;
        return;
      }
      topic.partitions_.insert(std::make_pair(key, partition));
    }
    response.mutable_topics().insert(std::make_pair(key, topic));
  }
}
}
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_PRODUCE_RESPONSE_READ_HPP_D3212112F23544129EA82AB8A9647C3B
