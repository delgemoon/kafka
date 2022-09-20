//
// Created by tammd on 8/30/22.
//

#ifndef CONNECTOR_LIB_KAFKA_DETAIL_EDIAN_HPP_334F7C8A9B5B4D019631AECAEBE46D9B
#define CONNECTOR_LIB_KAFKA_DETAIL_EDIAN_HPP_334F7C8A9B5B4D019631AECAEBE46D9B

#include <arpa/inet.h>
#include <kafka/primitives.hpp>

#include <bit>
#include <bitset>
#include <endian.h>

namespace kafka
{

namespace detail
{
    // Convert the given 64 bit integer to big endian.
    inline int64
    be_to_host_64(int64 ll)
    {
        if constexpr (std::endian::native == std::endian::little)
            ll = (((uint64_t)htonl((uint32_t)((ll << 32) >> 32))) << 32) | (uint32_t)htonl((uint32_t)(ll >> 32));
        return ll;
    }

    // Convert the 64 Bit integer back to node specific endianess, which might be
    // little endian.
    inline int64
    host_to_be_64(int64 ll)
    {
        return be_to_host_64(ll);
    }
}   // namespace detail

}   // namespace kafka
#endif   // CONNECTOR_LIB_KAFKA_DETAIL_EDIAN_HPP_334F7C8A9B5B4D019631AECAEBE46D9B
