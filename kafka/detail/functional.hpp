//
// Created by tammd on 9/1/22.
//

#ifndef CONNECTOR_LIB_KAFKA_DETAIL_FUNCTIONAL_HPP_7CA0A1575F63406DB6CCCF09773A7728
#define CONNECTOR_LIB_KAFKA_DETAIL_FUNCTIONAL_HPP_7CA0A1575F63406DB6CCCF09773A7728

#include <boost/asio.hpp>
#include <kafka/detail/endian.hpp>
#include <kafka/primitives.hpp>

namespace kafka::detail
{

    template < typename TTopic >
    class is_topic_with_name : std::unary_function< TTopic, bool >
    {
        using t_my = is_topic_with_name< TTopic >;

      public:
        is_topic_with_name(const std::string &name)
        : name_(name)
        {
        }

        typename t_my::result_type
        operator()(const typename t_my::argument_type &other)
        {
            return other.topic_name_ == name_;
        }

      private:
        std::string name_;
    };

    template < typename TTopicPartition >
    class is_topic_partition : std::unary_function< TTopicPartition, bool >
    {
        using t_my = is_topic_partition< TTopicPartition >;

      public:
        is_topic_partition(int32 partition)
        : partition_(partition)
        {
        }

        typename t_my::result_type
        operator()(const typename t_my::argument_type &other)
        {
            return other.partition_ == partition_;
        }

      private:
        int32 partition_;
    };

    template < typename TBroker >
    class is_broker_with_id : std::unary_function< TBroker, bool >
    {
        using t_my = is_broker_with_id< TBroker >;

      public:
        is_broker_with_id(int32 node_id)
        : node_id_(node_id)
        {
        }

        typename t_my::result_type
        operator()(const typename t_my::argument_type &other)
        {
            return other.node_id_ == node_id_;
        }

      private:
        int32 node_id_;
    };

    // Find an entry with 'topic_name' set to the given topic name inside the
    // given const container.
    template < typename TContainer >
    typename TContainer::const_iterator
    find_topic_by_name(const std::string &name, const TContainer &container)
    {
        typedef typename TContainer::value_type TTopic;
        typename TContainer::const_iterator     result =
            std::find_if(container.begin(), container.end(), is_topic_with_name< TTopic >(name));
        return result;
    }

    // Find or create an entry with 'topic_name' set to the given topic name inside
    // the given mutual container.
    template < typename TContainer >
    typename TContainer::iterator
    find_topic_by_name(const std::string &name, TContainer &container, bool create = true)
    {
        typedef typename TContainer::value_type TTopic;
        typename TContainer::iterator           result =
            std::find_if(container.begin(), container.end(), is_topic_with_name< TTopic >(name));
        if (create && result == container.end())
        {
            result             = container.insert(container.end(), TTopic());
            result->topic_name_ = name;
        }
        return result;
    }

    // Find an entry with 'partition' set to the given partition number inside the
    // given const container.
    template < typename TContainer >
    typename TContainer::const_iterator
    find_topic_partition_by_number(int32 partition, const TContainer &container)
    {
        typedef typename TContainer::value_type TPartition;
        typename TContainer::const_iterator     result =
            std::find_if(container.begin(), container.end(), is_topic_partition< TPartition >(partition));
        return result;
    }

    // Find or create an entry with 'partition' set to the given partition number
    // inside the given mutual container.
    template<typename TContainer>
    typename TContainer::iterator find_topic_partition_by_number(
      int32 partition,
      TContainer& container,
      bool create = true)
    {
      typedef typename TContainer::value_type TPartition;
      typename TContainer::iterator result =
        std::find_if(container.begin(), container.end(),
                     is_topic_partition<TPartition>(partition));
      if (create && result == container.end())
      {
        result = container.insert(container.end(), TPartition());
        result->partition_ = partition;
      }
      return result;
    }

    // Find or create an entry with 'partition' set to the given partition number
    // inside the given mutual container.
    template < typename TContainer >
    typename TContainer::iterator
    find_topic_partition_with_id(int32 partition, TContainer &container, bool create = true)
    {
        using TPartition = typename TContainer::value_type;
        typename TContainer::iterator result =
            std::find_if(container.begin(), container.end(), is_topic_partition< TPartition >(partition));
        if (create && result == container.end())
        {
            result            = container.insert(container.end(), TPartition());
            result->partition_ = partition;
        }
        return result;
    }

    // Find an entry with 'node_id' set to the given broker node id inside the
    // given const container.
    template < typename TContainer >
    typename TContainer::const_iterator
    find_broker_by_id(int32 node_id, const TContainer &container)
    {
        using TBroker = typename TContainer::value_type;
        typename TContainer::const_iterator result =
            std::find_if(container.begin(), container.end(), is_broker_with_id< TBroker >(node_id));
        return result;
    }
}   // namespace kafka
#endif   // CONNECTOR_LIB_KAFKA_DETAIL_FUNCTIONAL_HPP_7CA0A1575F63406DB6CCCF09773A7728
