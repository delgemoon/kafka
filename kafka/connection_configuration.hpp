//
// Created by tammd on 8/29/22.
//

#ifndef CONNECTOR_LIB_KAFKA_CONNECTION_CONFIGURATION_HPP_F7F4510FDB2E409E8DAAAFDF1AC1CCE3
#define CONNECTOR_LIB_KAFKA_CONNECTION_CONFIGURATION_HPP_F7F4510FDB2E409E8DAAAFDF1AC1CCE3

#include <kafka/primitives.hpp>

#include <optional>
#include <string>
#include <vector>

namespace kafka
{
struct connection_configuration
{
    struct broker_addr
    {
        using optional_type = std::optional< broker_addr >;
        std::string hostname_;
        std::string service_;
    };

    using broker_list = std::vector< broker_addr >;
    int32 message_max_bytes_;

    unsigned int socket_timeout_;

    std::string client_id_;

    bool auto_connect_;

    broker_addr::optional_type broker_address;

    connection_configuration();

    // Set the broker address using the given string.
    // If the string contain a colon, the part before the colon is interpreted
    // as hostname and the part after that character is interpreted as service
    // name.
    // Example: localhost:9092
    //
    void
    set_broker_from_string(const std::string &str);

    // Set the broker address using the given data structure.
    // The broker's address is determined by the fields:
    //     - host
    //     - port
    // A lexical cast is done on both fields.
    template < typename T >
    void
    set_broker(const T &broker);

    // Set the broker address using the given hostname and service parameter.
    // Both will be casted to string using a lexical_cast.
    template < typename Tx, typename Ty >
    void
    set_broker(const Tx &hostname, const Ty &service);
};

}   // namespace kafka

#include <kafka/impl/connection_configuration.hpp>

#endif   // CONNECTOR_LIB_KAFKA_CONNECTION_CONFIGURATION_HPP_F7F4510FDB2E409E8DAAAFDF1AC1CCE3
