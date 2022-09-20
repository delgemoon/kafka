//
// Created by tammd on 9/10/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_COMPRESSION_HPP_88902E18A6DF4D87878DDBB75BF31844
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_COMPRESSION_HPP_88902E18A6DF4D87878DDBB75BF31844

#include <kafka/detail/compression.hpp>
#include <kafka/error.hpp>

namespace kafka::detail
{

inline bytes compress(const bytes& data,
                      constants::compression compression,
                      boost::system::error_code& ec)
{
  using namespace kafka::constants;

  switch (compression)
  {
    case kCompressionGZIP:
      return compression_policy<kCompressionGZIP>::
      algorithm_t::compress(data, ec);
    case kCompressionSnappy:
      return compression_policy<kCompressionSnappy>::
      algorithm_t::compress(data, ec);
    case kCompressionLz4:
      return compression_policy<kCompressionLz4>::
      algorithm_t::compress(data, ec);
    case kCompressionNone:
      ec = kErrorSuccess;
      break;
    default:
      ec = kErrorCompressionNotAvailable;
      break;
  }

  return bytes();
}

inline bytes decompress(const bytes& data,
                        constants::compression compression,
                        boost::system::error_code& ec)
{
  using namespace kafka::constants;

  switch (compression)
  {
    case kCompressionGZIP:
      return compression_policy<kCompressionGZIP>::
      algorithm_t::decompress(data, ec);
    case kCompressionSnappy:
      return compression_policy<kCompressionSnappy>::
      algorithm_t::decompress(data, ec);
    case kCompressionLz4:
      return compression_policy<kCompressionLz4>::
      algorithm_t::decompress(data, ec);
    case kCompressionNone:
      ec = client_error::kErrorSuccess;
      break;
    default:
      ec = client_error::kErrorCompressionNotAvailable;
      break;
  }

  return bytes();
}

inline bytes fallback_compression_algorithm::compress(
  const bytes&, boost::system::error_code& ec)
{
  ec = kErrorCompressionNotAvailable;
  return bytes();
}

inline bytes fallback_compression_algorithm::decompress(
  const bytes&, boost::system::error_code& ec)
{
  ec = kErrorCompressionNotAvailable;
  return bytes();
}


}
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_COMPRESSION_HPP_88902E18A6DF4D87878DDBB75BF31844
