//
// Created by tammd on 9/6/22.
//

#ifndef CONNECTOR_LIB_KAFKA_OFFSET_REQUEST_HPP_E45635A24DC24B96860E639CC821DA58
#define CONNECTOR_LIB_KAFKA_OFFSET_REQUEST_HPP_E45635A24DC24B96860E639CC821DA58

#include <kafka/constants.hpp>
#include <kafka/detail/topics_partitions.hpp>
#include <kafka/offset_response.hpp>
#include <kafka/primitives.hpp>
#include <kafka/request.hpp>

#include <vector>

namespace kafka
{

// Kafka Offset API request implementation
struct offset_request : public request< offset_request >
{
    friend class request< offset_request >;

    static int16
    ApiKey();

    struct partition_properties_s
    {
        int64 time_;
        int32 max_number_of_offsets_;
    };

    using topics_partitions_t = detail::topics_partitions_vector< detail::empty_properties, partition_properties_s >;

  public:
    using response_type_t        = offset_response;
    using mutable_esponse_type_t = mutable_offset_response;
    using topic_t                  = topics_partitions_t::topic_type;
    using partition_t       = topics_partitions_t::partition_type;
    using topics_t               = topics_partitions_t::topics_type;
    using partitions_t      = topics_partitions_t::partitions_type;

    int32
    replica_id() const;

    const topics_t &
    topics() const;

    // Fetch offset information for the given topic-partition.
    // The (optional) `time` parameter can be used to ask for messages before
    // a certain time in the past (in milliseconds). Two special values exist for
    // this parameter:
    //   `libkafka_asio::constants::kOffsetTimeLatest`    (-1) (Default)
    //   `libkafka_asio::constants::kOffsetTimeEarliest`  (-2)
    //
    void
    fetch_topic_offset(const std::string &topic_name,
                       int32              partition,
                       int64              time                  = constants::kOffsetTimeLatest,
                       int32              max_number_of_offsets = constants::kDefaultOffsetMaxNumberOfOffsets);

    // Clears all entries for fetching topic-partitions
    void
    clear();

  private:
    topics_t topics_;
};

}   // namespace kafka
#endif   // CONNECTOR_LIB_KAFKA_OFFSET_REQUEST_HPP_E45635A24DC24B96860E639CC821DA58
