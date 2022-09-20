//
// Created by tammd on 9/1/22.
//

#ifndef CONNECTOR_LIB_KAFKA_CONSUMER_METADATA_RESPONSE_HPP_A1539E373BF14C12A93B12D4A32D4003
#define CONNECTOR_LIB_KAFKA_CONSUMER_METADATA_RESPONSE_HPP_A1539E373BF14C12A93B12D4A32D4003

#include <kafka/primitives.hpp>
#include <kafka/response.hpp>

#include <string>

namespace kafka
{

struct mutable_consumer_metadata_response;

struct consumer_metadata_response : public response< consumer_metadata_response >
{
    friend struct MutableConsumerMetadataResponse;

    int16
    error_code() const;
    int32
    coordinator_id() const;
    const std::string &
    coordinator_host() const;

    int32
    coordinator_port() const;

  private:
    int16       error_code_;
    int32       coordinator_id_;
    std::string coordinator_host_;
    int32       coordinator_port_;
};

struct mutable_consumer_metadata_response : public mutable_response< consumer_metadata_response >
{
    void
    set_error_code(int16 error_code);
    void
    set_coordinator_id(int32 coordinator_id);

    void
    set_coordinator_host(std::string coordinator_host);

    void
    set_coordinator_port(int32 coordinator_port);
};

}   // namespace kafka

#endif   // CONNECTOR_LIB_KAFKA_CONSUMER_METADATA_RESPONSE_HPP_A1539E373BF14C12A93B12D4A32D4003
