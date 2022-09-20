//
// Created by tammd on 8/29/22.
//

#ifndef CONNECTOR_LIB_KAFKA_RESPONSE_HPP_88D5EE48BCB643D99B11378BE7790345
#define CONNECTOR_LIB_KAFKA_RESPONSE_HPP_88D5EE48BCB643D99B11378BE7790345

#include <kafka/constants.hpp>
#include <kafka/primitives.hpp>

#include <optional>
#include <string>

namespace kafka
{

template < typename TResponse >
struct mutable_response;

// Base response template
template < typename TResponse >
struct response
{
    friend struct mutable_response< TResponse >;

  public:
    using ptional_type = std::optional< TResponse >;

    int32
    correlation_id() const
    {
        return correlation_id_;
    }

  private:
    int32 correlation_id_;
};

template < typename TResponse >
struct mutable_response
{
  public:
    void
    set_correlation_id(int32 correlation_id)
    {
        response_.correlation_id_ = correlation_id;
    }

    const TResponse &
    response() const
    {
        return response_;
    }

  protected:
    TResponse response_;
};
}   // namespace kafka
#endif   // CONNECTOR_LIB_KAFKA_RESPONSE_HPP_88D5EE48BCB643D99B11378BE7790345
