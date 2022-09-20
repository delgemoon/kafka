//
// Created by tammd on 9/7/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_RECURSIVE_MESSAGESET_ITERATOR_HPP_C68B8CE93D0D4AE89E032CCD0AF742D7
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_RECURSIVE_MESSAGESET_ITERATOR_HPP_C68B8CE93D0D4AE89E032CCD0AF742D7

#include <kafka/detail/recursive_messageset_iterator.hpp>

namespace kafka::detail
{

inline recursive_message_set_iterator::recursive_message_set_iterator()
: message_set_(nullptr)
{
}

inline recursive_message_set_iterator::recursive_message_set_iterator(const message_set &message_set)
: message_set_(&message_set)
{
    outer_iterator_     = message_set_->begin();
    outer_end_iterator_ = message_set_->end();
    if (outer_iterator_ == outer_end_iterator_)
    {
        reset();
    }
    else if (!outer_iterator_->nested_message_set().empty())
    {
        inner_iterator_.reset(new inner_iterator_type_t::element_type(outer_iterator_->nested_message_set()));
    }
}

inline recursive_message_set_iterator::recursive_message_set_iterator(const recursive_message_set_iterator &orig)
: message_set_(orig.message_set_)
, outer_iterator_(orig.outer_iterator_)
, outer_end_iterator_(orig.outer_end_iterator_)
, inner_iterator_()
{
    if (orig.inner_iterator_)
    {
        inner_iterator_.reset(new inner_iterator_type_t::element_type(*orig.inner_iterator_));
    }
}

inline recursive_message_set_iterator &
recursive_message_set_iterator::operator=(const recursive_message_set_iterator &rhs)
{
    message_set_        = rhs.message_set_;
    outer_iterator_     = rhs.outer_iterator_;
    outer_end_iterator_ = rhs.outer_end_iterator_;
    if (rhs.inner_iterator_)
    {
        inner_iterator_.reset(new inner_iterator_type_t::element_type(*rhs.inner_iterator_));
    }
    else
    {
        inner_iterator_.reset();
    }
    return *this;
}

inline void
recursive_message_set_iterator::increment()
{
    if (!message_set_)
    {
        return;
    }
    if (!is_inner_done())
    {
        // First increase the inner-iterator (if it is still valid)
        (*inner_iterator_)++;
    }

    if (is_inner_done())
    {
        // If the inner iterator is at the end (or there is no nested message set)
        // then increase the outer iterator
        ++outer_iterator_;
        if (outer_iterator_ == outer_end_iterator_)
        {
            // If the outer iterator reached the end of the message set, we're done
            reset();
            return;
        }
        if (!outer_iterator_->nested_message_set().empty())
        {
            // Create a new inner iterator, if the new outer has a nested message set
            inner_iterator_.reset(new inner_iterator_type_t::element_type(outer_iterator_->nested_message_set()));
        }
    }
}

inline bool
recursive_message_set_iterator::equal(const recursive_message_set_iterator &other) const
{
    if (message_set_ && other.message_set_)
    {
        if ((inner_iterator_ && other.inner_iterator_))
        {
            return (message_set_ == other.message_set_) && (message_set_ != NULL) &&
                   (outer_iterator_ == other.outer_iterator_) && (inner_iterator_ == other.inner_iterator_);
        }
        return (message_set_ == other.message_set_) && (message_set_ != NULL) &&
               (outer_iterator_ == other.outer_iterator_);
    }
    return (message_set_ == other.message_set_);
}

inline const message_and_offset &
recursive_message_set_iterator::dereference() const
{
    if (!is_inner_done())
    {
        return inner_iterator_->dereference();
    }
    else
    {
        return *outer_iterator_;
    }
}

inline void
recursive_message_set_iterator::reset()
{
    message_set_ = NULL;
    inner_iterator_.reset();
}

inline bool
recursive_message_set_iterator::is_inner_done() const
{
    return !inner_iterator_ || !inner_iterator_->message_set_;
}

}   // namespace kafka::detail
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_IMPL_RECURSIVE_MESSAGESET_ITERATOR_HPP_C68B8CE93D0D4AE89E032CCD0AF742D7
