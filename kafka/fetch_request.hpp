//
// Created by tammd on 9/6/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_FETCH_REQUEST_HPP_923CA35F421B4585A66F201D8E5167F6
#define CONNECTOR_DEPENDENCIES_KAFKA_FETCH_REQUEST_HPP_923CA35F421B4585A66F201D8E5167F6

#include <kafka/constants.hpp>
#include <kafka/detail/topics_partitions.hpp>
#include <kafka/fetch_response.hpp>
#include <kafka/primitives.hpp>
#include <kafka/request.hpp>

#include <vector>

namespace kafka
{
struct fetch_request : public request< fetch_request >
{
    friend class request< fetch_request >;

    static int16
    ApiKey();

    struct partition_properties
    {
        int64 fetch_offset_;
        int32 max_bytes_;
    };

    using topics_partitions = detail::topics_partitions_vector< detail::empty_properties, partition_properties >;

  public:
    using response_type         = fetch_response;
    using mutable_response_type = mutable_fetch_response;
    using topic_t               = topics_partitions::topic_type;
    using partition_t           = topics_partitions::partition_type;
    using topics_t              = topics_partitions::topics_type;
    using partitions_t          = topics_partitions::partitions_type;

    fetch_request();

    int32
    replica_id() const;

    int32
    max_wait_time() const;

    int32
    min_bytes() const;

    const topics_t &
    topics() const;

    // Maximum time to wait for message data to become available on the server.
    // This option can be used in combination with the `min_bytes` parameter.
    // The timeout must be specified in milliseconds.
    void
    set_max_wait_time(int32 max_wait_time);

    // Set the minimum number of bytes to wait for on the server side.
    // If this is set to 0, the server won't wait at all. If set to 1, the server
    // waits until 1 byte of the requested topic-partition data is available or
    // the specified timeout occurs.
    void
    set_min_bytes(int32 min_bytes);

    // Fetch data for the specified topic-partition.
    // If such entry already exists in this Fetch request, it gets overridden.
    // Optionally, the offset to start the Fetch operation from, as well as the
    // maximum number of bytes to fetch, can be specified.
    void
    FetchTopic(const std::string &topic_name,
               int32              partition,
               int64              fetch_offset = constants::kDefaultFetchOffset,
               int32              max_bytes    = constants::kDefaultFetchMaxBytes);

    // Clears this Fetch request by removing all topic/partition entries.
    void
    Clear();

  private:
    int32    max_wait_time_;
    int32    min_bytes_;
    topics_t topics_;
};

}   // namespace kafka

#endif   // CONNECTOR_DEPENDENCIES_KAFKA_FETCH_REQUEST_HPP_923CA35F421B4585A66F201D8E5167F6
