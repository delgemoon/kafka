//
// Created by tammd on 9/6/22.
//

#ifndef CONNECTOR_LIB_KAFKA_OFFSET_RESPONSE_HPP_A2AA97B0CB644C358EA30917F85CC9FA
#define CONNECTOR_LIB_KAFKA_OFFSET_RESPONSE_HPP_A2AA97B0CB644C358EA30917F85CC9FA

#include <kafka/detail/topics_partitions.hpp>
#include <kafka/primitives.hpp>
#include <kafka/response.hpp>

#include <vector>

namespace kafka
{
struct mutable_offset_response;

// Kafka Offset API response
struct offset_response : public response< offset_response >
{
    friend class mutable_offset_response;

    struct partition_properties
    {
        using offset_vector = std::vector< int64 >;
        int16         error_code_;
        offset_vector offsets_;
    };

    using topics_artitions_t = detail::topics_partitions_map< detail::empty_properties, partition_properties >;

  public:
    using topic_t      = topics_artitions_t::topic_type;
    using partition_t  = topics_artitions_t::partition_type;
    using topics_t     = topics_artitions_t::topics_type;
    using partitions_t = topics_artitions_t::partitions_type;

    const topics_t &
    topics() const;

    // Search for offset data inside this response object for the given topic
    // and partition. If no such data can be found, the return value is empty.
    partition_t::optional_type
    topic_partition_offset(const std::string &topic_name, int32 partition) const;

  private:
    topics_t topics_;
};

struct mutable_offset_response : public mutable_response< offset_response >
{
  public:
    offset_response::topics_t &
    mutable_topics();
};
}   // namespace kafka

#endif   // CONNECTOR_LIB_KAFKA_OFFSET_RESPONSE_HPP_A2AA97B0CB644C358EA30917F85CC9FA
