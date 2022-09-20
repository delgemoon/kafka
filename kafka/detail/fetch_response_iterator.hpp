//
// Created by tammd on 9/7/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_FETCH_RESPONSE_ITERATOR_HPP_45CB22884BDD4BD88BF8AFD485094351
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_FETCH_RESPONSE_ITERATOR_HPP_45CB22884BDD4BD88BF8AFD485094351

#include <boost/iterator/iterator_facade.hpp>
#include <kafka/message.hpp>
#include <kafka/detail/recursive_messageset_iterator.hpp>

namespace kafka::detail
{

template < typename TTopicsPartitions >
struct fetch_response_iterator
: public boost::iterator_facade< fetch_response_iterator< TTopicsPartitions >,
                                 const message_and_offset,
                                 boost::forward_traversal_tag >
{
    using t_my = fetch_response_iterator< TTopicsPartitions >;

  public:
    using topic_t = typename TTopicsPartitions::TopicType      ;
    using partition_t =  typename TTopicsPartitions::PartitionType  ;
    using topics_t =  typename TTopicsPartitions::TopicsType     ;
    using partitions_t = typename TTopicsPartitions::PartitionsType ;

    fetch_response_iterator()
    : topics_(NULL)
    {
    }

    explicit fetch_response_iterator(const topics_t &topics)
    : topics_(&topics)
    {
        topic_iter_ = topics_->begin();
        while (topic_iter_ != topics_->end())
        {
            topic_partition_iter_ = topic_iter_->second.partitions.begin();
            while (topic_partition_iter_ != topic_iter_->second.partitions.end())
            {
                message_iter_ = RecursiveMessageSetIterator(topic_partition_iter_->second.messages);
                if (message_iter_ != recursive_message_set_iterator())
                {
                    // Found a message to start with
                    return;
                }
                ++topic_partition_iter_;
            }
            ++topic_iter_;
        }
        // Found nothing...
        reset();
    }

    const std::string &
    topic_name() const
    {
        return topic_iter_->first;
    }

    const topic_t &
    topic() const
    {
        return topic_iter_->second;
    }

    int32
    topic_partition_id() const
    {
        return topic_partition_iter_->first;
    }

    const partition_t &
    topic_partition() const
    {
        return topic_partition_iter_->second;
    }

  private:
    friend class boost::iterator_core_access;

    using topic_iterator = typename topics_t::const_iterator     ;
    using topic_partition_iterator = typename partitions_t::const_iterator;

    void
    reset()
    {
        topics_ = NULL;
    }

    void
    increment()
    {
        if (!topics_)
        {
            return;
        }
        ++message_iter_;
        while (message_iter_ == recursive_message_set_iterator())
        {
            ++topic_partition_iter_;
            while (topic_partition_iter_ == topic_iter_->second.partitions.end())
            {
                ++topic_iter_;
                if (topic_iter_ == topics_->end())
                {
                    reset();
                    return;
                }
                topic_partition_iter_ = topic_iter_->second.partitions.begin();
            }
            message_iter_ = RecursiveMessageSetIterator(topic_partition_iter_->second.messages);
        }
    }

    bool
    equal(const t_my &other) const
    {
        if (topics_)
        {
            return other.topics_ == topics_ && other.message_iter_ == message_iter_;
        }
        return other.topics_ == topics_;
    }

    const message_and_offset &
    dereference() const
    {
        return *message_iter_;
    }

    const topics_t               *topics_;
    topic_iterator              topic_iter_;
    topic_partition_iterator     topic_partition_iter_;
    recursive_message_set_iterator message_iter_;
};

}

#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_FETCH_RESPONSE_ITERATOR_HPP_45CB22884BDD4BD88BF8AFD485094351
