//
// Created by tammd on 9/6/22.
//

#ifndef CONNECTOR_LIB_KAFKA_OFFSET_COMMIT_RESPONSE_HPP_A0C2E2A968324E73AAAFCB26BF08C431
#define CONNECTOR_LIB_KAFKA_OFFSET_COMMIT_RESPONSE_HPP_A0C2E2A968324E73AAAFCB26BF08C431

#include <kafka/detail/topics_partitions.hpp>
#include <kafka/response.hpp>

namespace kafka
{
struct mutable_offset_commit_response;

// Kafka Offset Commit/Fetch API response implementation:
// Offset commit response
struct offset_commit_response : public response< offset_commit_response >
{
    friend class mutable_offset_commit_response;

    struct partition_properties
    {
        int16 error_code_;
    };

    using topics_partitions = detail::topics_partitions_map< detail::empty_properties, partition_properties >;

  public:
    using topic_t      = topics_partitions::topic_type;
    using partition_t  = topics_partitions::partition_type;
    using topics_t     = topics_partitions::topics_type;
    using partitions_t = topics_partitions::partitions_type;

    const topics_t &
    topics() const;

  private:
    topics_t topics_;
};

class mutable_offset_commit_response : public mutable_response< offset_commit_response >
{
  public:
    offset_commit_response::topics_t &
    mutable_topics();
};

}   // namespace kafka
#endif   // CONNECTOR_LIB_KAFKA_OFFSET_COMMIT_RESPONSE_HPP_A0C2E2A968324E73AAAFCB26BF08C431
