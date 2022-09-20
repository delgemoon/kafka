//
// Created by tammd on 8/29/22.
//

#ifndef CONNECTOR_LIB_KAFKA_MESSAGE_HPP_B6493B476F3747D49A329838C014C902
#define CONNECTOR_LIB_KAFKA_MESSAGE_HPP_B6493B476F3747D49A329838C014C902

#include <kafka/constants.hpp>
#include <kafka/error.hpp>
#include <kafka/message_fwd.hpp>
#include <kafka/primitives.hpp>

#include <memory>
#include <vector>

namespace kafka
{
struct message
{
    message();
    message(const message &orig, bool deep = false);
    message &
    operator=(const message &rhs);

    // Magic byte is always zero
    int8
    magic_byte() const;

    // Attributes bitset. the lowest 2 bits indicate the used compression algorithm
    int8
    attributes() const;

    // Sets the attribute byte of this message
    void
    set_attributes(int8 attributes);

    // Optional message key. can be null(default).
    const bytes &
    key() const;

    bytes &
    mutable_key();

    const bytes &
    value() const;

    bytes &
    mutable_value();

    // Compressed messages contain a nested message set
    const message_set &
    nested_message_set() const;

    message_set &
    mutable_nested_message_set();

    constants::compression
    compression() const;

  private:
    int8                           attributes_;
    bytes                          key_;
    bytes                          value_;
    std::shared_ptr< message_set > nested_message_set_;
};

struct message_and_offset : public message
{
    message_and_offset() ;
    message_and_offset(const message &m, int64 offset);

    int64
    offset() const;

    void
    set_offset(int64 offset);

  private:
    int64 offset_;
};

}   // namespace kafka

#include <kafka/impl/message.hpp>

#endif   // CONNECTOR_LIB_KAFKA_MESSAGE_HPP_B6493B476F3747D49A329838C014C902
