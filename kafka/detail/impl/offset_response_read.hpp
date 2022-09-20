//
// Created by tammd on 9/10/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_OFFSET_REQUEST_WRITE_HPP_9D113366A01C478CABAD84A960E904B0
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_OFFSET_REQUEST_WRITE_HPP_9D113366A01C478CABAD84A960E904B0

#include <kafka/detail/response_read.hpp>
#include <kafka/offset_response.hpp>
#include <kafka/error.hpp>
namespace kafka::detail
{
inline void read_response_message(std::istream& is,
                                mutable_offset_response& response,
                                boost::system::error_code& ec)
{
  int topic_count = read_int_32(is);
  for (int t = 0; t < topic_count; ++t)
  {
    offset_response::topics_t::key_type key;
    offset_response::topics_t::mapped_type topic;
    key = read_string(is);

    int partition_count = read_int_32(is);
    for (int p = 0; p < partition_count; ++p)
    {
      offset_response::partitions_t ::key_type key;
      offset_response::partitions_t::mapped_type partition;
      key = read_int_32(is);
      partition.error_code_ = read_int_16(is);
      if (partition.error_code_)
      {
        ec = (kafka_error) partition.error_code_;
        return;
      }
      int32 offsets_size = read_int_32(is);
      for (int32 k = 0; k < offsets_size; ++k)
      {
        partition.offsets_.push_back(read_int_64(is));
      }
      topic.partitions_.insert(std::make_pair(key, partition));
    }
    response.mutable_topics().insert(std::make_pair(key, topic));
  }
}
}
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_OFFSET_REQUEST_WRITE_HPP_9D113366A01C478CABAD84A960E904B0
