//
// Created by tammd on 9/7/22.
//

#ifndef CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_RECURSIVE_MESSAGESET_ITERATOR_HPP_1F1A4082EBC043A095F7C025CAAC2E6F
#define CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_RECURSIVE_MESSAGESET_ITERATOR_HPP_1F1A4082EBC043A095F7C025CAAC2E6F

#include <kafka/message.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/scoped_ptr.hpp>
#include <kafka/message.hpp>

namespace kafka::detail
{

struct recursive_message_set_iterator :
  public boost::iterator_facade<
    recursive_message_set_iterator,
    const message_and_offset,
    boost::forward_traversal_tag
  >
{
public:

  // Create a new empty and uninitialized iterator. Such objects can be used
  // as end-iterator.
  recursive_message_set_iterator();

  // Create a new object, recursively iterating over the given MessageSet.
  // The MessageSet MUST always have a longer lifetime than the iterator object.
  explicit recursive_message_set_iterator(const message_set & message_set);

  // Copy the given iterator object. The resulting iterator will iterate over
  // the same MessageSet. The outer- as well as the inner-iterator will be
  // copied as well. So one can continue to work with the original iterator
  // object without affecting the new one and vice-versa.
  recursive_message_set_iterator(const recursive_message_set_iterator& orig);

  // Assign the given iterator to this one by copying it. The same rules apply
  // as for the copy-constructor above.
  recursive_message_set_iterator& operator=(
    const recursive_message_set_iterator& rhs);

private:
  friend class boost::iterator_core_access;

  using inner_iterator_type_t = std::unique_ptr<recursive_message_set_iterator>;

  void increment();

  bool equal(const recursive_message_set_iterator& other) const;

  const message_and_offset& dereference() const;

  void reset();

  bool is_inner_done() const;

  // Pointer to the MessageSet we're iterating through
  const message_set *message_set_;

  // Outer iterators: Normal iterators on the given MessageSet
  message_set::const_iterator outer_iterator_;
  message_set::const_iterator outer_end_iterator_;

  // Inner iterator: If the Message, currently pointed to by the outer iterator
  // has a nested MessageSet, the inner iterator is used to walk through it.
  inner_iterator_type_t inner_iterator_;
};

}   // namespace kafka::detail
#endif   // CONNECTOR_DEPENDENCIES_KAFKA_DETAIL_RECURSIVE_MESSAGESET_ITERATOR_HPP_1F1A4082EBC043A095F7C025CAAC2E6F
