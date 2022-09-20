//
// Created by tammd on 9/12/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_IMPL_OFFSET_FETCH_REQUEST_HPP_D82C5ED01EEF42ED9EE68A047F2F6BD5
#define CONNECTOR_DEPENDENCIES_KAFKA_IMPL_OFFSET_FETCH_REQUEST_HPP_D82C5ED01EEF42ED9EE68A047F2F6BD5
#include <kafka/constants.hpp>
#include <kafka/detail/functional.hpp>
#include <kafka/offset_fetch_request.hpp>
namespace kafka
{
inline int16 offset_fetch_request::ApiKey()
{
  return constants::kApiKeyOffsetFetchRequest;
}

inline const std::string& offset_fetch_request::consumer_group() const
{
  return consumer_group_;
}

inline const offset_fetch_request::topics_t& offset_fetch_request::topics() const
{
  return topics_;
}

inline void offset_fetch_request::set_consumer_group(const std::string& consumer_group)
{
  consumer_group_ = consumer_group;
}

inline void offset_fetch_request::fetch_offset(const std::string& topic_name,
                                            int32 partition)
{
  topics_t::iterator topic_iter = detail::find_topic_by_name(topic_name, topics_);
  partitions_t::iterator partition_iter =
    detail::find_topic_partition_by_number(partition, topic_iter->partitions_);
}
}
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_IMPL_OFFSET_FETCH_REQUEST_HPP_D82C5ED01EEF42ED9EE68A047F2F6BD5
