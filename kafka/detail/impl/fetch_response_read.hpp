//
// Created by tammd on 9/10/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_FETCH_RESPONSE_READ_HPP_DF479C1095E34BD4AFC635E4E04D4C15
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_FETCH_RESPONSE_READ_HPP_DF479C1095E34BD4AFC635E4E04D4C15
#include <kafka/detail/response_read.hpp>
#include <kafka/primitives.hpp>
#include <kafka/fetch_response.hpp>
#include <kafka/error.hpp>


namespace kafka::detail
{
inline void read_response_message(std::istream& is,
                                mutable_fetch_response& response,
                                boost::system::error_code& ec)
{
  // Topic array
  int topic_count = read_int_32(is);
  for (int t = 0; t < topic_count; ++t)
  {
    fetch_response::topics_t::key_type key;
    fetch_response::topics_t::mapped_type topic;
    key = read_string(is);

    // Partitions array
    int partition_count = read_int_32(is);
    for (int p = 0; p < partition_count; ++p)
    {
      fetch_response::partitions_t::key_type key;
      fetch_response::partitions_t::mapped_type partition;
      key = read_int_32(is);
      partition.error_code_ = read_int_16(is);
      partition.highwater_mark_offset_ = read_int_64(is);

      if (partition.error_code_)
      {
        ec = (kafka_error) partition.error_code_;
        return;
      }

      // MessageSet
      int32 message_set_size = read_int_32(is);
      read_message_set(is, partition.messages_, message_set_size, ec);
      if (ec != kErrorSuccess)
      {
        return;
      }
      topic.partitions_.insert(std::make_pair(key, partition));
    }
    response.mutable_topics().insert(std::make_pair(key, topic));
  }
}
}
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_FETCH_RESPONSE_READ_HPP_DF479C1095E34BD4AFC635E4E04D4C15
