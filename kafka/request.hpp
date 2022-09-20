//
// Created by tammd on 8/29/22.
//

#ifndef CONNECTOR_LIB_KAFKA_REQUEST_HPP_13FA3AC1B93842CDB832FC9E8B94CD4E
#define CONNECTOR_LIB_KAFKA_REQUEST_HPP_13FA3AC1B93842CDB832FC9E8B94CD4E

#include <kafka/constants.hpp>
#include <kafka/primitives.hpp>

#include <string>

namespace kafka
{

template < typename Request >
struct request
{
    request()
    : correlation_id_(constants::kDefaultCorrelationId)
    {
    }
    inline int16
    api_key() const
    {
        return Request::ApiKey();
    }
    inline int16
    api_version() const
    {
        return 0;
    }
    int32
    correlation_id() const
    {
        return correlation_id_;
    }

    // Set the correlation ID. The Kafka server will put this value into the
    // corresponding response message.
    void
    set_correlation_id(int32 correlation_id)
    {
        correlation_id_ = correlation_id;
    }

    bool
    ResponseExpected() const
    {
        return true;
    }

  private:
    int32       correlation_id_;
    std::string client_id_;
};

}   // namespace kafka
#endif   // CONNECTOR_LIB_KAFKA_REQUEST_HPP_13FA3AC1B93842CDB832FC9E8B94CD4E
