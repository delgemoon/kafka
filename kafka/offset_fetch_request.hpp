//
// Created by tammd on 9/6/22.
//

#ifndef CONNECTOR_LIB_KAFKA_OFFSET_FETCH_REQUEST_HPP_A35FC4DBD3694B6CB75B2EC891F6EB56
#define CONNECTOR_LIB_KAFKA_OFFSET_FETCH_REQUEST_HPP_A35FC4DBD3694B6CB75B2EC891F6EB56

#include <kafka/detail/topics_partitions.hpp>
#include <kafka/offset_fetch_response.hpp>
#include <kafka/request.hpp>

#include <set>
#include <vector>

namespace kafka
{

// Kafka Offset Commit/Fetch API request implementation:
// Offset fetch request
struct offset_fetch_request : public request< offset_fetch_request >
{
    friend class request< offset_fetch_request >;

    static int16
    ApiKey();

    using topics_partitions_t = detail::topics_partitions_vector< detail::empty_properties, detail::empty_properties >;

  public:
    using response_type_t         = offset_fetch_response;
    using mutable_response_type_t = mutable_offset_fetch_response;
    using topic_t                 = topics_partitions_t::topic_type;
    using partition_t             = topics_partitions_t::partition_type;
    using topics_t                = topics_partitions_t::topics_type;
    using partitions_t            = topics_partitions_t::partitions_type;

    const std::string &
    consumer_group() const;

    const topics_t &
    topics() const;

    void
    set_consumer_group(const std::string &consumer_group);

    void
    fetch_offset(const std::string &topic_name, int32 partition);

  private:
    std::string consumer_group_;
    topics_t    topics_;
};

}   // namespace kafka
#endif   // CONNECTOR_LIB_KAFKA_OFFSET_FETCH_REQUEST_HPP_A35FC4DBD3694B6CB75B2EC891F6EB56
