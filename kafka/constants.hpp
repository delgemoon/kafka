//
// Created by tammd on 8/29/22.
//

#ifndef CONNECTOR_LIB_KAFKA_CONSTANTS_HPP_02CD95D8D52E4D43B4C85FADDFF3055F
#define CONNECTOR_LIB_KAFKA_CONSTANTS_HPP_02CD95D8D52E4D43B4C85FADDFF3055F

#include <string>

namespace kafka::constants
{

enum api_Keys
{
    kApiKeyProduceRequest          = 0,
    kApiKeyFetchRequest            = 1,
    kApiKeyOffsetRequest           = 2,
    kApiKeyMetadataRequest         = 3,
    kApiKeyOffsetCommitRequest     = 8,
    kApiKeyOffsetFetchRequest      = 9,
    kApiKeyConsumerMetadataRequest = 10
};

enum compression
{
    kCompressionNone   = 0,
    kCompressionGZIP   = 1,
    kCompressionSnappy = 2,
    kCompressionLz4    = 3
};

enum defaults
{
    kDefaultPartition                = 0,
    kDefaultProduceRequiredAcks      = 1,
    kDefaultProduceTimeout           = 10000,
    kDefaultFetchOffset              = 0,
    kDefaultFetchMinBytes            = 0,
    kDefaultFetchMaxBytes            = 32768,
    kDefaultFetchMaxWaitTime         = 0,
    kDefaultOffsetMaxNumberOfOffsets = 1,
    kDefaultOffsetCommitTimestampNow = -1,
    kDefaultCorrelationId            = 0,
    kDefaultMessageMaxBytes          = 4194304,
    kDefaultSocketTimeout            = 60000
};

inline bool
defaultConnectionAutoConnect()
{
    return false;
}

inline const std::string &
defaultClientId()
{
    static std::string client_id = "libkafka_asio";
    return client_id;
}

inline const std::string &
defaultKafkaService()
{
    static std::string service = "9092";
    return service;
}

enum metadata_Leader
{
    kMetadataLeaderUndecided = -1
};

enum offsetTime
{
    kOffsetTimeLatest   = -1,
    kOffsetTimeEarliest = -2
};

}   // namespace kafka::constants

#endif   // CONNECTOR_LIB_KAFKA_CONSTANTS_HPP_02CD95D8D52E4D43B4C85FADDFF3055F
