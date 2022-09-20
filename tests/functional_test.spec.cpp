//
// Created by tammd on 9/17/22.
//

#include <doctest/doctest.h>
#include <kafka/kafka.hpp>

#include <iostream>
#include <list>
#include <set>
#include <sstream>
#include <vector>

using namespace std;
using namespace kafka;
using namespace kafka::detail;

struct test_topic
{
    std::string topic_name_;

    test_topic() {}

    test_topic(const string &name)
    : topic_name_(name)
    {
    }
};

struct test_partition
{
    int32 partition_;

    test_partition() {}

    test_partition(int32 p)
    : partition_(p)
    {
    }
};

using test_topic_vector     = vector< test_topic >;
using test_partition_vector = vector< test_partition >;

TEST_CASE("functional_test")
{
    test_topic_vector test_topics;
    test_topics.push_back(test_topic("hello"));
    test_topics.push_back(test_topic("world"));
    test_topics.push_back(test_topic("foo"));
    test_topics.push_back(test_topic("bar"));
    DOCTEST_CHECK_EQ(4, test_topics.size());
    const test_topic_vector          &const_test_topics = test_topics;
    test_topic_vector::const_iterator result;
    result = find_topic_by_name("foo", const_test_topics);
    DOCTEST_CHECK_NE(result, const_test_topics.end());
    result = find_topic_by_name("test", const_test_topics);
    DOCTEST_CHECK_EQ(result, const_test_topics.end());
    DOCTEST_CHECK_EQ(4, test_topics.size());
}

TEST_CASE("functional_test::find_topic_by_name_1")
{
    test_topic_vector test_topics;
    test_topics.push_back(test_topic("hello"));
    test_topics.push_back(test_topic("world"));
    test_topics.push_back(test_topic("foo"));
    test_topics.push_back(test_topic("bar"));
    DOCTEST_CHECK_EQ(4, test_topics.size());
    test_topic_vector::iterator result;
    result = find_topic_by_name("foo", test_topics);
    DOCTEST_CHECK_NE(result, test_topics.end());
    result = find_topic_by_name("test", test_topics);
    DOCTEST_CHECK_NE(result, test_topics.end());
    result = find_topic_by_name("yetanother", test_topics, false);
    DOCTEST_CHECK_EQ(result, test_topics.end());
    DOCTEST_CHECK_EQ(5, test_topics.size());
}

TEST_CASE("functional_test::find_partition_by_number_1")
{
    test_partition_vector test_partitions;
    test_partitions.push_back(test_partition(1337));
    test_partitions.push_back(test_partition(42));
    test_partitions.push_back(test_partition(1));
    test_partitions.push_back(test_partition(2));
    DOCTEST_CHECK_EQ(4, test_partitions.size());
    const test_partition_vector          &const_test_partitions = test_partitions;
    test_partition_vector::const_iterator result;
    result = find_topic_partition_by_number(2, const_test_partitions);
    DOCTEST_CHECK_NE(result, const_test_partitions.end());
    result = find_topic_partition_by_number(9000, const_test_partitions);
    DOCTEST_CHECK_EQ(result, const_test_partitions.end());
    DOCTEST_CHECK_EQ(4, test_partitions.size());
}

TEST_CASE("functional_test::find_partition_by_number_2")
{
    test_partition_vector test_partitions;
    test_partitions.push_back(test_partition(1337));
    test_partitions.push_back(test_partition(42));
    test_partitions.push_back(test_partition(1));
    test_partitions.push_back(test_partition(2));
    DOCTEST_CHECK_EQ(4, test_partitions.size());
    test_partition_vector::iterator result;
    result = find_topic_partition_by_number(2, test_partitions);
    DOCTEST_CHECK_NE(result, test_partitions.end());
    result = find_topic_partition_by_number(9000, test_partitions);
    DOCTEST_CHECK_NE(result, test_partitions.end());
    result = find_topic_partition_by_number(1234, test_partitions, false);
    DOCTEST_CHECK_EQ(result, test_partitions.end());
    DOCTEST_CHECK_EQ(5, test_partitions.size());
}