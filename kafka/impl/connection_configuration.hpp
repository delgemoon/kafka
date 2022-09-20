//
// Created by tammd on 8/29/22.
//

#ifndef CONNECTOR_LIB_KAFKA_IMPL_CONNECTION_CONFIGURATION_HPP_68FA677999364819BBB746F677D1DE80
#define CONNECTOR_LIB_KAFKA_IMPL_CONNECTION_CONFIGURATION_HPP_68FA677999364819BBB746F677D1DE80

#include <kafka/connection_configuration.hpp>
#include <kafka/constants.hpp>

#include <string>

namespace kafka
{

inline connection_configuration::connection_configuration()
: message_max_bytes_(constants::kDefaultMessageMaxBytes)
, socket_timeout_(constants::kDefaultSocketTimeout)
, client_id_(constants::defaultClientId())
, auto_connect_(constants::defaultConnectionAutoConnect())
{
}

inline void
connection_configuration::set_broker_from_string(const std::string &str)
{
    if (str.empty())
    {
        broker_address.reset();
        return;
    }
    broker_addr            broker;
    std::string::size_type delimiter_position = str.find(':');
    if (delimiter_position != std::string::npos && delimiter_position > 0 && delimiter_position < str.size() - 1)
    {
        broker.hostname_ = str.substr(0, delimiter_position);
        broker.service_  = str.substr(delimiter_position + 1);
    }
    else
    {
        broker.hostname_ = str.substr(0, delimiter_position);
        broker.service_  = constants::defaultKafkaService();
    }
    if (broker.hostname_.empty() || broker.service_.empty())
    {
        return;
    }
    broker_address = broker;
}

template < typename T >
inline void
connection_configuration::set_broker(const T &broker)
{
    set_broker(broker.host, broker.port);
}

template < typename Tx, typename Ty >
inline void
connection_configuration::set_broker(const Tx &hostname, const Ty &service)
{
    broker_addr broker;
    broker.hostname_ = to_string(hostname);
    broker.service_  = to_string< std::string >(service);
    broker_address   = broker;
}

}   // namespace kafka

#endif   // CONNECTOR_LIB_KAFKA_IMPL_CONNECTION_CONFIGURATION_HPP_68FA677999364819BBB746F677D1DE80
