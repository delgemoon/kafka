//
// Created by tammd on 8/29/22.
//

#ifndef CONNECTOR_LIB_KAFKA_ERROR_HPP_3EE96C709771406EB43138C7352EBCB7
#define CONNECTOR_LIB_KAFKA_ERROR_HPP_3EE96C709771406EB43138C7352EBCB7

#ifdef ASIO_STANDALONE
#include <boost/asio/error_code.hpp>
#else
#include <boost/system/error_code.hpp>
#endif

#include <cstdint>

namespace kafka
{

enum client_error
{
    kErrorSuccess = 0,
    kErrorAlreadyConnected,
    kErrorNotConnected,
    kErrorNoBroker,
    kErrorInProgress,
    kErrorCompressionNotAvailable,
    kErrorCompressionFailed
};

enum kafka_error
{
    kErrorNoError                             = 0,
    kErrorUnknown                             = -1,
    kErrorOffsetOutOfRange                    = 1,
    kErrorInvalidMessage                      = 2,
    kErrorUnknownTopicOrPartition             = 3,
    kErrorInvalidMessageSize                  = 4,
    kErrorLeaderNotAvailable                  = 5,
    kErrorNotLeaderForPartition               = 6,
    kErrorRequestTimedOut                     = 7,
    kErrorBrokerNotAvailable                  = 8,
    kErrorReplicaNotAvailable                 = 9,
    kErrorMessageSizeTooLarge                 = 10,
    kErrorStaleControllerEpochCode            = 11,
    kErrorOffsetMetadataTooLargeCode          = 12,
    kErrorOffsetLoadInProgressCode            = 14,
    kErrorConsumerCoordinatorNotAvailableCode = 15,
    kErrorNotCoordinatorForConsumerCode       = 16
};

class client_error_category :
  public boost::system::error_category
{
public:
  inline const char *name() const BOOST_SYSTEM_NOEXCEPT
  {
    return "kafka::client_error";
  }

  inline std::string message(int value) const
  {
    switch (value)
    {
      case kErrorAlreadyConnected:
        return "Client is already connected to remote host";
      case kErrorNotConnected:
        return "Client is not connected";
      case kErrorNoBroker:
        return "No broker found";
      case kErrorInProgress:
        return "Another operation is still in progress for this client";
      case kErrorCompressionNotAvailable:
        return "The specified compression algorithm is not available!";
      case kErrorCompressionFailed:
        return "Data compression failure!";
      default:
        return "kafka client error";
    }
  }

  inline static const boost::system::error_category& Instance()
  {
    static client_error_category instance;
    return instance;
  }
};

class kafka_error_category :
  public boost::system::error_category
{
public:
  inline const char *name() const BOOST_SYSTEM_NOEXCEPT
  {
    return "kafka::kafka_error";
  }

  inline std::string message(int value) const
  {
    switch (value)
    {
      case kErrorNoError:
        return "No error";
      case kErrorUnknown:
        return "Unexpected server error";
      case kErrorOffsetOutOfRange:
        return "The requested offset is outside the range of offsets "
          "maintained by the server for the given topic/partition.";
      case kErrorInvalidMessage:
        return "message content does not match its CRC.";
      case kErrorUnknownTopicOrPartition:
        return "Topic or partition does not exist on this broker.";
      case kErrorInvalidMessageSize:
        return "The message has a negative size";
      case kErrorLeaderNotAvailable:
        return "There is currently no leader for this partition and hence it "
          "is unavailable for writes.";
      case kErrorNotLeaderForPartition:
        return "Message was sent to a replica that is not the leader for this"
          " partition. Client metadata is out of date.";
      case kErrorRequestTimedOut:
        return "Request exceeded the user-specified time limit";
      case kErrorBrokerNotAvailable:
        return "Broker not available.";
      case kErrorReplicaNotAvailable:
        return "Replica was expected on this broker but is not available.";
      case kErrorMessageSizeTooLarge:
        return "Message was too large";
      case kErrorStaleControllerEpochCode:
        return "Internal error StaleControllerEpochCode";
      case kErrorOffsetMetadataTooLargeCode:
        return "Specified string larger than configured maximum for offset "
          "metadata";
      case kErrorOffsetLoadInProgressCode:
        return "Offset fetch request is still loading offsets";
      case kErrorConsumerCoordinatorNotAvailableCode:
        return "Offsets topic has not yet been created.";
      case kErrorNotCoordinatorForConsumerCode:
        return "Request was for a consumer group that is not coordinated by "
          "this broker.";
      default:
        return "kafka kafka error";
    }
  }

  inline static const boost::system::error_category& Instance()
  {
    static kafka_error_category instance;
    return instance;
  }
};

//
// boost::system integration code following:
//

inline boost::system::error_code make_error_code(client_error e)
{
  return boost::system::error_code(
    static_cast<int>(e), client_error_category::Instance());
}

inline boost::system::error_code make_error_code(kafka_error e)
{
  return boost::system::error_code(
    static_cast<int>(e), kafka_error_category::Instance());
}

}   // namespace kafka

namespace boost
{
namespace system
{

template<>
struct is_error_code_enum<kafka::client_error>
{
  static const bool value = true;
};

template<>
struct is_error_code_enum<kafka::kafka_error>
{
  static const bool value = true;
};

}  // namespace system
}  // namespace boost

#endif   // CONNECTOR_LIB_KAFKA_ERROR_HPP_3EE96C709771406EB43138C7352EBCB7
