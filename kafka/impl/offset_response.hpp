//
// Created by tammd on 9/12/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_IMPL_OFFSET_RESPONSE_HPP_E8CDC75C186946D98B05B9F9EF497AB3
#define CONNECTOR_DEPENDENCIES_KAFKA_IMPL_OFFSET_RESPONSE_HPP_E8CDC75C186946D98B05B9F9EF497AB3

#include <kafka/detail/functional.hpp>
#include <kafka/offset_response.hpp>

namespace kafka
{

inline const offset_response::topics_t& offset_response::topics() const
{
  return topics_;
}

inline offset_response::partition_t::optional_type
offset_response::topic_partition_offset(const std::string& topic_name,
                                     int32 partition) const
{
  topics_t::const_iterator topic_iter = topics_.find(topic_name);
  if (topic_iter == topics_.end())
  {
    return partition_t::optional_type ();
  }
  partitions_t::const_iterator partition_iter =
    topic_iter->second.partitions_.find(partition);
  if (partition_iter == topic_iter->second.partitions_.end())
  {
    return partition_t::optional_type();
  }
  return partition_iter->second;
}

inline offset_response::topics_t& mutable_offset_response::mutable_topics()
{
  return response_.topics_;
}

}
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_IMPL_OFFSET_RESPONSE_HPP_E8CDC75C186946D98B05B9F9EF497AB3
