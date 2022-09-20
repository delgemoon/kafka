//
// Created by tammd on 9/1/22.
//

#ifndef CONNECTOR_LIB_KAFKA_DETAIL_REQUEST_WRITE_HPP_E377F88C12AE4ADDACBF685DE15217AF
#define CONNECTOR_LIB_KAFKA_DETAIL_REQUEST_WRITE_HPP_E377F88C12AE4ADDACBF685DE15217AF

#include <kafka/primitives.hpp>
#include <kafka/message_fwd.hpp>
#include <string>

namespace kafka
{

struct metadata_request;

struct produce_request;

struct fetch_request;

struct offset_request;

struct consumer_metadata_request;

struct offset_commit_request;

struct offset_fetch_request;

namespace detail
{

    int32
    string_wire_size(const std::string &str);

    int32
    bytes_wire_size(const bytes &bytes);

    int32
    message_wire_size(const message &message);

    int32
    message_set_wire_size(const message_set &message_set);

    template < typename TRequest >
    int32
    request_wire_size(const TRequest &request, const std::string &client_id);

    int32
    request_message_wire_size(const metadata_request &request);

    int32
    request_message_wire_size(const produce_request &request);

    int32
    request_message_wire_size(const fetch_request &request);

    int32
    request_message_wire_size(const offset_request &request);

    int32
    request_message_wire_size(const consumer_metadata_request &request);

    int32
    request_message_wire_size(const offset_commit_request &request);

    int32
    request_message_wire_size(const offset_fetch_request &request);

    void
    write_int8(int8 value, std::ostream &os);

    void
    write_int16(int16 value, std::ostream &os);

    void
    write_int32(int32 value, std::ostream &os);

    void
    write_int64(int64 value, std::ostream &os);

    void
    write_string(const std::string &value, std::ostream &os);

    void
    write_bytes(const bytes &value, std::ostream &os);

    void
    write_message(const message &value, std::ostream &os);

    void
    write_message_set(const message_set &value, std::ostream &os);

    template < typename TRequest >
    void
    write_request(const TRequest &request, const std::string &client_id, std::ostream &os);

    void
    write_request_message(const metadata_request &request, std::ostream &os);

    void
    write_request_message(const produce_request &request, std::ostream &os);

    void
    write_request_message(const fetch_request &request, std::ostream &os);

    void
    write_request_message(const offset_request &request, std::ostream &os);

    void
    write_request_message(const consumer_metadata_request &request, std::ostream &os);

    void
    write_request_message(const offset_commit_request &request, std::ostream &os);

    void
    write_request_message(const offset_fetch_request &request, std::ostream &os);

}   // namespace kafka
}
#include <kafka/detail/impl/request_write.hpp>

#endif   // CONNECTOR_LIB_KAFKA_DETAIL_REQUEST_WRITE_HPP_E377F88C12AE4ADDACBF685DE15217AF
