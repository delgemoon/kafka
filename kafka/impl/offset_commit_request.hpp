//
// Created by tammd on 9/12/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_IMPL_OFFSET_COMMIT_REQUEST_HPP_AC773E98E2B44BE5824CAD83DA288C4C
#define CONNECTOR_DEPENDENCIES_KAFKA_IMPL_OFFSET_COMMIT_REQUEST_HPP_AC773E98E2B44BE5824CAD83DA288C4C

#include <kafka/constants.hpp>
#include <kafka/detail/functional.hpp>
#include <kafka/offset_commit_request.hpp>

namespace kafka
{

inline int16 offset_commit_request::ApiKey()
{
  return constants::kApiKeyOffsetCommitRequest;
}

inline const std::string& offset_commit_request::consumer_group() const
{
  return consumer_group_;
}

inline const offset_commit_request::topics_t& offset_commit_request::topics() const
{
  return topics_;
}

inline void offset_commit_request::set_consumer_group(
  const std::string& consumer_group)
{
  consumer_group_ = consumer_group;
}

inline void offset_commit_request::commit_offset(const std::string& topic_name,
                                              int32 partition,
                                              int64 offset,
                                              int64 timestamp,
                                              const std::string& metadata)
{
  topics_t::iterator topic_iter = detail::find_topic_by_name(topic_name, topics_);
  partitions_t::iterator partition_iter =
    detail::find_topic_partition_by_number(partition, topic_iter->partitions_);
  partition_iter->offset_ = offset;
  partition_iter->timestamp_ = timestamp;
  partition_iter->metadata_ = metadata;
}

inline void offset_commit_request::clear()
{
  topics_.clear();
}

}
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_IMPL_OFFSET_COMMIT_REQUEST_HPP_AC773E98E2B44BE5824CAD83DA288C4C
