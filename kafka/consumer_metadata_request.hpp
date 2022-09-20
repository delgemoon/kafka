//
// Created by tammd on 9/1/22.
//

#ifndef CONNECTOR_LIB_KAFKA_CONSUMER_METADATA_REQUEST_HPP_86F0051080134893A83A1645DB6BFFDA
#define CONNECTOR_LIB_KAFKA_CONSUMER_METADATA_REQUEST_HPP_86F0051080134893A83A1645DB6BFFDA

#include <kafka/consumer_metadata_response.hpp>
#include <kafka/request.hpp>

namespace kafka
{
struct consumer_metadata_request : public request< consumer_metadata_request >
{
    friend struct request< consumer_metadata_request >;

    static int16
    api_key();

    using response_type = consumer_metadata_response;

    using mutable_response_type = mutable_consumer_metadata_response;

    const std::string &
    consumer_group() const;

    void
    set_consumer_group(const std::string &consumer_group);

  private:
    std::string consumer_group_;
};

}   // namespace kafka

#endif   // CONNECTOR_LIB_KAFKA_CONSUMER_METADATA_REQUEST_HPP_86F0051080134893A83A1645DB6BFFDA
