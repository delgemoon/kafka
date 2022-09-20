//
// Created by tammd on 8/29/22.
//

#ifndef CONNECTOR_LIB_KAFKA_PRIMITIVES_HPP_62CBA71D5F984345BAC3A01F246A87A3
#define CONNECTOR_LIB_KAFKA_PRIMITIVES_HPP_62CBA71D5F984345BAC3A01F246A87A3

#include <memory>
#include <numeric>
#include <vector>

namespace kafka
{

using int8  = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;
using byte  = std::uint8_t;
using bytes = std::shared_ptr< std::vector< byte > >;

}   // namespace kafka

#endif   // CONNECTOR_LIB_KAFKA_PRIMITIVES_HPP_62CBA71D5F984345BAC3A01F246A87A3
