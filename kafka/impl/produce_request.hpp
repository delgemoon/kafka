//
// Created by tammd on 9/11/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_IMPL_PRODUCE_REQUEST_HPP_CCF3C4634E8641D1971EDB6DAB1A572E
#define CONNECTOR_DEPENDENCIES_KAFKA_IMPL_PRODUCE_REQUEST_HPP_CCF3C4634E8641D1971EDB6DAB1A572E


#include <algorithm>
#include <boost/bind/bind.hpp>
#include <kafka/constants.hpp>
#include <kafka/produce_request.hpp>
#include <kafka/detail/functional.hpp>
#include <kafka/message.hpp>

namespace kafka
{
inline int16 produce_request::ApiKey()
{
  return constants::kApiKeyProduceRequest;
}

inline produce_request::produce_request() :
  required_acks_(constants::kDefaultProduceRequiredAcks),
  timeout_(constants::kDefaultProduceTimeout)
{
}

inline int16 produce_request::required_acks() const
{
  return required_acks_;
}

inline int32 produce_request::timeout() const
{
  return timeout_;
}

inline const produce_request::topics_t& produce_request::topics() const
{
  return topics_;
}

inline void produce_request::set_required_acks(int16 required_acks)
{
  required_acks_ = required_acks;
}

inline void produce_request::set_timeout(int32 timeout)
{
  timeout_ = timeout;
}

inline void produce_request::add_value(const bytes& value,
                                     const std::string& topic_name,
                                     int32 partition)
{
  message message;
  message.mutable_value() = value;
  add_message(message, topic_name, partition);
}

inline void produce_request::add_value(const std::string& value,
                                     const std::string& topic_name,
                                     int32 partition)
{
  message message;
  message.mutable_value().reset(
    new bytes::element_type(value.begin(), value.end()));
  add_message(message, topic_name, partition);
}

inline void produce_request::add_message(const message& message,
                                       const std::string& name,
                                       int32 partition)
{
  auto topic_iter = detail::find_topic_by_name(name, topics_);
  partitions_t::iterator partition_iter =
    detail::find_topic_partition_by_number(partition, topic_iter->partitions_);
  message_and_offset msg(message, 0);
  partition_iter->messages_.push_back(msg);
}

inline void produce_request::add_message_set(const message_set& message_set,
                                          const std::string& topic_name,
                                          int32 partition)
{
  std::for_each(message_set.begin(), message_set.end(),
                boost::bind(&produce_request::add_message,
                            this, boost::placeholders::_1, topic_name, partition));
}

inline void produce_request::clear()
{
  topics_.clear();
}

inline void produce_request::clear_topic(const std::string& topic_name)
{
  topics_.erase(std::remove_if(topics_.begin(),
                               topics_.end(),
                               is_topic_with_name_f (topic_name)),
                topics_.end());
}

inline void produce_request::clear_topic_partition(const std::string& topic_name,
                                                int32 partition)
{
  topics_t::iterator topic_iter = std::find_if(topics_.begin(),
                                             topics_.end(),
                                             is_topic_with_name_f (topic_name));
  if (topic_iter != topics_.end())
  {
    topic_iter->partitions_.erase(std::remove_if(topic_iter->partitions_.begin(),
                                                topic_iter->partitions_.end(),
                                                is_topic_partition_f (partition)),
                                 topic_iter->partitions_.end());
  }
}

inline bool produce_request::response_expected() const
{
  return required_acks_ != 0;
}

}
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_IMPL_PRODUCE_REQUEST_HPP_CCF3C4634E8641D1971EDB6DAB1A572E
