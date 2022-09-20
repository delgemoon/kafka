//
// Created by tammd on 9/12/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_IMPL_METADATA_REQUEST_HPP_8C8F0D7BF930417E99A7302F85300055
#define CONNECTOR_DEPENDENCIES_KAFKA_IMPL_METADATA_REQUEST_HPP_8C8F0D7BF930417E99A7302F85300055

#include <kafka/constants.hpp>
#include <kafka/metadata_request.hpp>

namespace kafka
{
inline int16 metadata_request::ApiKey()
{
  return constants::kApiKeyMetadataRequest;
}

inline const metadata_request::topic_name_vector& metadata_request::topic_names()
const
{
  return topic_names_;
}

inline void metadata_request::add_topic_name(const std::string& topic_name)
{
  topic_names_.push_back(topic_name);
}

inline void metadata_request::clear()
{
  topic_names_.clear();
}


}

#include <kafka/detail/impl/metadata_request_write.hpp>

#endif   // CONNECTOR_DEPENDENCIES_KAFKA_IMPL_METADATA_REQUEST_HPP_8C8F0D7BF930417E99A7302F85300055
