//
// Created by tammd on 9/2/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_BYTE_STREAMBUF_HPP_2ECA93083F66454C8AAB559B8783767A
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_BYTE_STREAMBUF_HPP_2ECA93083F66454C8AAB559B8783767A

#include <kafka/primitives.hpp>

#include <streambuf>

namespace kafka::detail
{

    struct byte_streambuf : public std::streambuf
    {
      public:
        explicit byte_streambuf(bytes data);

        bytes
        data() const;

      private:
        bytes data_;
    };

}   // namespace kafka

#include <kafka/detail/impl/byte_streambuf.hpp>

#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_BYTE_STREAMBUF_HPP_2ECA93083F66454C8AAB559B8783767A
