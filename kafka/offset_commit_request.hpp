//
// Created by tammd on 9/6/22.
//

#ifndef CONNECTOR_LIB_KAFKA_OFFSET_COMMIT_REQUEST_HPP_523F012702564F21B83277CE585B05CF
#define CONNECTOR_LIB_KAFKA_OFFSET_COMMIT_REQUEST_HPP_523F012702564F21B83277CE585B05CF
#include <kafka/constants.hpp>
#include <kafka/detail/topics_partitions.hpp>
#include <kafka/offset_commit_response.hpp>
#include <kafka/request.hpp>

#include <vector>

namespace kafka
{

// Kafka Offset Commit/Fetch API request implementation:
// Offset commit request
struct offset_commit_request : public request< offset_commit_request >
{
    friend class request< offset_commit_request >;

    static int16
    ApiKey();

    struct partition_properties
    {
        int64       offset_;
        int64       timestamp_;
        std::string metadata_;
    };

    using topics_partitions = detail::topics_partitions_vector< detail::empty_properties, partition_properties >;

  public:
    using response_type_t         = offset_commit_request;
    using mutable_response_type_t = mutable_offset_commit_response;
    using topic_t                 = topics_partitions::topic_type;
    using partition_t             = topics_partitions::partition_type;
    using topics_t                = topics_partitions::topics_type;
    using partitions_t            = topics_partitions::partitions_type;

    const std::string &
    consumer_group() const;

    const topics_t &
    topics() const;

    void
    set_consumer_group(const std::string &consumer_group);

    void
    commit_offset(const std::string &topic_name,
                  int32              partition,
                  int64              offset,
                  int64              timestamp = constants::kDefaultOffsetCommitTimestampNow,
                  const std::string &metadata  = "");

    void
    clear();

  private:
    std::string consumer_group_;
    topics_t     topics_;
};

}   // namespace kafka
#endif   // CONNECTOR_LIB_KAFKA_OFFSET_COMMIT_REQUEST_HPP_523F012702564F21B83277CE585B05CF
