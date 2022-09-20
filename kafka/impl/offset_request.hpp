//
// Created by tammd on 9/11/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_IMPL_OFFSET_REQUEST_HPP_D7DF6AEC763448679AD4D66EFC19FFF8
#define CONNECTOR_DEPENDENCIES_KAFKA_IMPL_OFFSET_REQUEST_HPP_D7DF6AEC763448679AD4D66EFC19FFF8

#include <kafka/constants.hpp>
#include <kafka/detail/functional.hpp>
#include <kafka/offset_request.hpp>

namespace kafka
{

inline int16 offset_request::ApiKey()
{
  return constants::kApiKeyOffsetRequest;
}

inline int32 offset_request::replica_id() const
{
  return -1;
}

inline const offset_request::topics_t & offset_request::topics() const
{
  return topics_;
}

inline void offset_request::fetch_topic_offset(const std::string& topic_name,
                                            int32 partition,
                                            int64 time,
                                            int32 max_number_of_offsets)
{
  topics_t::iterator topic_iter = detail::find_topic_by_name(topic_name, topics_);
  partitions_t::iterator partition_iter =
    detail::find_topic_partition_by_number(partition, topic_iter->partitions_);
  partition_iter->time_ = time;
  partition_iter->max_number_of_offsets_ = max_number_of_offsets;
}

inline void offset_request::clear()
{
  topics_.clear();
}

}

#include <kafka/detail/impl/offset_request_write.hpp>
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_IMPL_OFFSET_REQUEST_HPP_D7DF6AEC763448679AD4D66EFC19FFF8
