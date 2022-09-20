//
// Created by tammd on 9/6/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_METADATA_REQUEST_HPP_3A485FEF3AAD449BBB56627EE55E3529
#define CONNECTOR_DEPENDENCIES_KAFKA_METADATA_REQUEST_HPP_3A485FEF3AAD449BBB56627EE55E3529

#include <kafka/metadata_response.hpp>
#include <kafka/primitives.hpp>
#include <kafka/request.hpp>

#include <vector>

namespace kafka
{
// Kafka Metadata API request implementation.
// The metadata API can be used to determine information about available topics,
// partitions and brokers.
struct metadata_request : public request< metadata_request >
{
    friend struct request< metadata_request >;

    static int16
    ApiKey();

  public:
    using response_type         = metadata_response;
    using mutable_response_type = mutable_metadata_response;
    using topic_name_vector     = std::vector< std::string >;

    const topic_name_vector &
    topic_names() const;

    // Add a topic to fetch metadata for
    void
    add_topic_name(const std::string &topic_name);

    // Removes all topic name entries, added to this request
    void
    clear();

  private:
    topic_name_vector topic_names_;
};

}   // namespace kafka

#include <kafka/impl/metadata_request.hpp>

#endif   // CONNECTOR_DEPENDENCIES_KAFKA_METADATA_REQUEST_HPP_3A485FEF3AAD449BBB56627EE55E3529
