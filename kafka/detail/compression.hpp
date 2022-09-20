//
// Created by tammd on 9/10/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_COMPRESS_HPP_F2AA978F77854F8A9D5FE9C6605C8048
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_COMPRESS_HPP_F2AA978F77854F8A9D5FE9C6605C8048
#include <kafka/primitives.hpp>
#include <boost/system.hpp>
#include <kafka/constants.hpp>

namespace kafka::detail
{

// Compress the given bytes with the specified compression algorithm.
// If the something goes wrong or the compression algorithm is not available,
// the error code will be set correspondingly.
bytes compress(const bytes& data,
               constants::compression compression,
               boost::system::error_code& ec);


// De-compress the given bytes using the specified compression algorithm.
// If there was an error or the compression algorithm is not available, the
// given error code will be set.
bytes decompress(const bytes& data,
                 constants::compression compression,
                 boost::system::error_code& ec);


// Fallback implementation, which will be used in case an algorithm was disabled
// and is therefore not available. It simply sets a respective error code and
// returns an empty value.
struct fallback_compression_algorithm
{
  static bytes compress(const bytes&, boost::system::error_code& ec);

  static bytes decompress(const bytes&, boost::system::error_code& ec);
};


// Compression algorithm policy template.
// Specific algorithms should specialize this template and define the
// 'Algorithm' type.
template<constants::compression C>
struct compression_policy
{
  using algorithm_t =  fallback_compression_algorithm;
};

}

#include <kafka/detail/impl/compression.hpp>

#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_COMPRESS_HPP_F2AA978F77854F8A9D5FE9C6605C8048
