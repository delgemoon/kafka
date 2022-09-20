//
// Created by tammd on 9/10/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_OFFSET_FETCH_RESPONSE_READ_HPP_E18011BF16D840D38E09C8E041288B69
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_OFFSET_FETCH_RESPONSE_READ_HPP_E18011BF16D840D38E09C8E041288B69
#include <kafka/offset_fetch_response.hpp>
#include <kafka/error.hpp>
#include <kafka/detail/response_read.hpp>

namespace kafka::detail
{

inline void read_response_message(std::istream& is,
                                mutable_offset_fetch_response& response,
                                boost::system::error_code& ec)
{
  // error code not used
  (void)ec;
  int topic_count = read_int_32(is);
  for (int t = 0; t < topic_count; ++t)
  {
    offset_fetch_response::topics_t ::key_type key;
    offset_fetch_response::topics_t::mapped_type topic;
    key = read_string(is);

    int partition_count = read_int_32(is);
    for (int p = 0; p < partition_count; ++p)
    {
      offset_fetch_response::partitions_t ::key_type key;
      offset_fetch_response::partitions_t::mapped_type partition;
      key = read_int_32(is);
      partition.offset_ = read_int_64(is);
      partition.metadata_ = read_string(is);
      partition.error_code_ = read_int_16(is);
      topic.partitions_.insert(std::make_pair(key, partition));
    }
    response.mutable_topics().insert(std::make_pair(key, topic));
  }
}

}
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_OFFSET_FETCH_RESPONSE_READ_HPP_E18011BF16D840D38E09C8E041288B69
