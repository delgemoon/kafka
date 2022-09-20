//
// Created by tammd on 9/12/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_IMPL_METADATA_RESPONSE_HPP_B82CA90740BF49A99AE7C16BAF7B5005
#define CONNECTOR_DEPENDENCIES_KAFKA_IMPL_METADATA_RESPONSE_HPP_B82CA90740BF49A99AE7C16BAF7B5005

#include <kafka/metadata_response.hpp>
#include <kafka/detail/functional.hpp>

namespace kafka
{
inline const metadata_response::broker_vector_t & metadata_response::brokers() const
{
  return brokers_;
}

inline const metadata_response::topics_t& metadata_response::topics() const
{
  return topics_;
}

inline metadata_response::broker_vector_t &
mutable_metadata_response::mutable_brokers()
{
  return response_.brokers_;
}

inline metadata_response::topics_t& mutable_metadata_response::mutable_topics()
{
  return response_.topics_;
}

inline metadata_response::broker_s::optional_type
metadata_response::partition_leader(const std::string& topic, int32 partition) const
{
  topics_t::const_iterator topic_iter = topics_.find(topic);
  if (topic_iter == topics_.end())
  {
    return broker_s::optional_type();
  }
  partitions_t::const_iterator partition_iter =
    topic_iter->second.partitions_.find(partition);
  if (partition_iter == topic_iter->second.partitions_.end() ||
      partition_iter->second.leader_ == constants::kMetadataLeaderUndecided)
  {
    return broker_s::optional_type();
  }
  broker_vector_t::const_iterator broker_iter =
    detail::find_broker_by_id(partition_iter->second.leader_, brokers_);
  if (broker_iter != brokers_.end())
  {
    return *broker_iter;
  }
  return broker_s::optional_type();
}

}
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_IMPL_METADATA_RESPONSE_HPP_B82CA90740BF49A99AE7C16BAF7B5005
