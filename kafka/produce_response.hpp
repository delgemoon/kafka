//
// Created by tammd on 9/6/22.
//

#ifndef CONNECTOR_LIB_KAFKA_PRODUCE_RESPONSE_HPP_3358149E7EDF4C9FA9E7B9ADB34D9677
#define CONNECTOR_LIB_KAFKA_PRODUCE_RESPONSE_HPP_3358149E7EDF4C9FA9E7B9ADB34D9677

#include <kafka/detail/functional.hpp>
#include <kafka/detail/topics_partitions.hpp>
#include <kafka/primitives.hpp>
#include <kafka/response.hpp>

#include <vector>

namespace kafka
{

struct mutable_produce_response;

struct produce_response : public response< produce_response >
{
    friend class mutable_produce_response;

    struct partition_properties
    {
        int16 error_code_;
        int64 offset_;
    };

    using topics_partition = detail::topics_partitions_map< detail::empty_properties, partition_properties >;

  public:
    using topic_t      = topics_partition::topic_type;
    using partition_t  = topics_partition::partition_type;
    using topics_t     = topics_partition::topics_type;
    using partitions_t = topics_partition::partitions_type;

    const topics_t &
    topics() const
    {
        return topics_;
    }

    topic_t::optional_type
    find_topic(const std::string &topic_name) const;

    partition_t::optional_type
    find_topic_partition(const std::string &topic_name, int32 partition) const;

  private:
    topics_t topics_;
};

struct mutable_produce_response : public mutable_response< produce_response >
{
  public:
    produce_response::topics_t &
    mutable_topics()
    {
        return response_.topics_;
    }
};

}   // namespace kafka


#include <kafka/impl/produce_response.hpp>

#endif   // CONNECTOR_LIB_KAFKA_PRODUCE_RESPONSE_HPP_3358149E7EDF4C9FA9E7B9ADB34D9677
