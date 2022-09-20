//
// Created by tammd on 8/30/22.
//

#ifndef CONNECTOR_LIB_KAFKA_PRODUCT_REQUEST_HPP_2384E7A997EC479184C7A5F9F3A8E6F2
#define CONNECTOR_LIB_KAFKA_PRODUCT_REQUEST_HPP_2384E7A997EC479184C7A5F9F3A8E6F2

#include <kafka/detail/topics_partitions.hpp>
#include <kafka/message.hpp>
#include <kafka/primitives.hpp>
#include <kafka/produce_response.hpp>
#include <kafka/request.hpp>

#include <vector>

namespace kafka
{

struct produce_request : public request< produce_request >
{
    friend class request< produce_request >;

    static int16
    ApiKey();

    struct partition_properties
    {
        message_set messages_;
    };

    using TopicsPartitions = detail::topics_partitions_vector< detail::empty_properties, partition_properties >;

  public:
    using response_type_t         = produce_request;
    using mutable_response_type_t = mutable_produce_response;
    using topic_t                 = TopicsPartitions::topic_type;
    using partition_t             = TopicsPartitions::partition_type;
    using topics_t                = TopicsPartitions::topics_type;
    using partitions_t            = TopicsPartitions::partitions_type;

    produce_request();

    int16
    required_acks() const;

    int32
    timeout() const;

    const topics_t &
    topics() const;

    // Number of acknowledgments that need to be received by the server before
    // the response for this request is sent.
    // If zero (0) is specified for this parameter, the server will no wait for
    // acknowledgements. In this case, no response will be sent by the server.
    void
    set_required_acks(int16 required_acks);

    // Time out (in milliseconds) to wait for required acknowledgements
    void
    set_timeout(int32 timeout);

    // Add a byte array value for the given topic-partition in this produce
    // request.
    void
    add_value(const bytes &value, const std::string &topic_name, int32 partition = 0);

    // Add a string value for the given topic-partition in this produce request.
    void
    add_value(const std::string &value, const std::string &topic_name, int32 partition = 0);

    // Add a copy of the given message to the specified topic-partition in this
    // produce request.
    void
    add_message(const message &message, const std::string &topic_name, int32 partition = 0);

    // Copy the given set of messages (for the given topic-partition), into this
    // produce request.
    void
    add_message_set(const message_set &message_set, const std::string &topic_name, int32 partition = 0);

    // Clear all message data of this request
    void
    clear();

    // Clear the message data for the Topic with the given name.
    void
    clear_topic(const std::string &topic_name);

    // Clear the message data for the given topic-partition.
    void
    clear_topic_partition(const std::string &topic_name, int32 partition);

    // Return true, if this request expects a response from the Kafka server
    bool
    response_expected() const;

  private:
    using is_topic_with_name_f = detail::is_topic_with_name< topic_t >;
    using is_topic_partition_f = detail::is_topic_partition< partition_t >;

    int16    required_acks_;
    int32    timeout_;
    topics_t topics_;
};

}   // namespace kafka

#include <kafka/impl/produce_request.hpp>


#endif   // CONNECTOR_LIB_KAFKA_PRODUCT_REQUEST_HPP_2384E7A997EC479184C7A5F9F3A8E6F2
