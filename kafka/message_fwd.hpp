//
// Created by tammd on 8/29/22.
//

#ifndef CONNECTOR_LIB_KAFKA_MESSAGE_FWD_HPP_EF1D5CE8ECB7452AA834AFC56961D024
#define CONNECTOR_LIB_KAFKA_MESSAGE_FWD_HPP_EF1D5CE8ECB7452AA834AFC56961D024

#include <vector>

namespace kafka
{

struct message;
struct message_and_offset;
using message_set = std::vector< message_and_offset >;

}   // namespace kafka
#endif   // CONNECTOR_LIB_KAFKA_MESSAGE_FWD_HPP_EF1D5CE8ECB7452AA834AFC56961D024
