//
// Created by tammd on 9/8/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_IMPL_PRODUCE_RESPONSE_HPP_9A5524865EA2481F834FB58CE66DB753
#define CONNECTOR_DEPENDENCIES_KAFKA_IMPL_PRODUCE_RESPONSE_HPP_9A5524865EA2481F834FB58CE66DB753

#include <kafka/detail/functional.hpp>
#include <kafka/produce_response.hpp>

namespace kafka
{
inline produce_response::topic_t::optional_type produce_response::find_topic(
  const std::string& topic_name) const
{
  topics_t::const_iterator iter = topics_.find(topic_name);
  if (iter != topics_.end())
  {
    return iter->second;
  }
  return topic_t::optional_type();
}

inline produce_response::partition_t::optional_type
produce_response::find_topic_partition(const std::string& topic_name,
                                    int32 partition) const
{
  topic_t::optional_type topic = find_topic(topic_name);
  if (topic)
  {
    partitions_t::const_iterator iter = topic->partitions_.find(partition);
    if (iter != topic->partitions_.end())
    {
      return iter->second;
    }
  }
  return partition_t::optional_type();
}
}
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_IMPL_PRODUCE_RESPONSE_HPP_9A5524865EA2481F834FB58CE66DB753
