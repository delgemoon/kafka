//
// Created by tammd on 9/10/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_OFFSET_COMMIT_RESPONSE_READ_HPP_BF30DFE5CFC54A629AD0D9EB5E831591
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_OFFSET_COMMIT_RESPONSE_READ_HPP_BF30DFE5CFC54A629AD0D9EB5E831591

#include <kafka/detail/response_read.hpp>
#include <kafka/offset_commit_response.hpp>

namespace kafka::detail
{
inline void read_response_Message(std::istream& is,
                                mutable_offset_commit_response& response,
                                boost::system::error_code& ec)
{
  // error code not used
  (void)ec;
  int topic_count = read_int_32(is);
  for (int t = 0; t < topic_count; ++t)
  {
    offset_commit_response::topics_t::key_type key;
    offset_commit_response::topics_t::mapped_type topic;
    key = read_string(is);

    int partition_count = read_int_32(is);
    for (int p = 0; p < partition_count; ++p)
    {
      offset_commit_response::partitions_t ::key_type key;
      offset_commit_response::partitions_t::mapped_type partition;
      key = read_int_32(is);
      partition.error_code_ = read_int_16(is);
      topic.partitions_.insert(std::make_pair(key, partition));
    }
    response.mutable_topics().insert(std::make_pair(key, topic));
  }
}


}
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_OFFSET_COMMIT_RESPONSE_READ_HPP_BF30DFE5CFC54A629AD0D9EB5E831591
