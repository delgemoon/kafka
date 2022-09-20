//
// Created by tammd on 9/6/22.
//

#ifndef CONNECTOR_LIB_KAFKA_OFFSET_FETCH_RESPONSE_HPP_4E141C4014704CE495FE5E901AAE1E24
#define CONNECTOR_LIB_KAFKA_OFFSET_FETCH_RESPONSE_HPP_4E141C4014704CE495FE5E901AAE1E24

#include <kafka/detail/topics_partitions.hpp>
#include <kafka/response.hpp>

#include <vector>

namespace kafka
{

struct mutable_offset_fetch_response;

// Kafka Offset Commit/Fetch API response implementation:
// Offset fetch response
struct offset_fetch_response : public response< offset_fetch_response >
{
    friend class mutable_offset_fetch_response;

    struct partition_properties
    {
        int64       offset_;
        std::string metadata_;
        int16       error_code_;
    };

    using topics_partitions_t = detail::topics_partitions_map< detail::empty_properties, partition_properties >;

  public:
    using topic_t      = topics_partitions_t::topic_type;
    using partition_t  = topics_partitions_t::partition_type;
    using topics_t     = topics_partitions_t::topics_type;
    using partitions_t = topics_partitions_t::partitions_type;

    const topics_t &
    topics() const;

  private:
    topics_t topics_;
};

struct mutable_offset_fetch_response : public mutable_response< offset_fetch_response >
{
  public:
    offset_fetch_response::topics_t &
    mutable_topics();
};

}   // namespace kafka
#endif   // CONNECTOR_LIB_KAFKA_OFFSET_FETCH_RESPONSE_HPP_4E141C4014704CE495FE5E901AAE1E24
