//
// Created by tammd on 9/12/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_IMPL_FETCH_RESPONSE_HPP_3F37803799204CF89065B6F1B01621E7
#define CONNECTOR_DEPENDENCIES_KAFKA_IMPL_FETCH_RESPONSE_HPP_3F37803799204CF89065B6F1B01621E7

#include <kafka/fetch_response.hpp>

namespace kafka
{
inline const fetch_response::topics_t& fetch_response::topics() const
{
  return topics_;
}

inline fetch_response::topics_t& mutable_fetch_response::mutable_topics()
{
  return response_.topics_;
}

inline fetch_response::const_iterator fetch_response::begin() const
{
  return const_iterator(topics_);
}

inline fetch_response::const_iterator fetch_response::end() const
{
  return const_iterator();
}

}


#include <kafka/detail/impl/fetch_response_read.hpp>

#endif   // CONNECTOR_DEPENDENCIES_KAFKA_IMPL_FETCH_RESPONSE_HPP_3F37803799204CF89065B6F1B01621E7
