//
// Created by tammd on 9/1/22.
//

#ifndef CONNECTOR_LIB_KAFKA_DETAIL_TOPIC_PARTITIONS_HPP_B49B3EB394FE4347A36D8DC2D912D3AD
#define CONNECTOR_LIB_KAFKA_DETAIL_TOPIC_PARTITIONS_HPP_B49B3EB394FE4347A36D8DC2D912D3AD

#include <kafka/primitives.hpp>

#include <map>
#include <optional>
#include <string>

namespace kafka
{
namespace detail
{
    // Basic `Topic` structure that consists of a bunch of partitions.
    // Can be extended by specifying a properties structure.
    template < typename TProperties, typename TPartitions >
    struct topic : TProperties
    {
        using optional_type = std::optional< topic< TProperties, TPartitions > >;
        TPartitions partitions_;
    };

    // Basic `Partition` structure.
    // Can be extended by specifying a properties structure.
    template < typename TProperties >
    struct partition : TProperties
    {
        using optional_type = std::optional< partition< TProperties > >;
    };
    // Used by the `TopicsPartitionsVector` to add a `topic_name` property to
    // each `Topic`.
    template < typename TProperties >
    struct vector_topic_properties : TProperties
    {
        std::string topic_name_;
    };

    // Used by the `TopicsPartitionsVector` to add a `partition` property to
    // each `Partition`.
    template < typename TProperties >
    struct vector_partition_properties : TProperties
    {
        int32 partition_;
    };
    // Empty properties structure. Use this in case no properties should be added
    // to a certain data structure.
    struct empty_properties
    {
    };

    //
    // Topic-partition data structure using two levels of nested maps. On the top
    // level, a `Topic` data structure is mapped to a topic name (string). Each of
    // the `Topic` objects contains a bunch of `Partition` objects, mapped to the
    // partition id/number.
    // Extend the Topic and/or Partition structures by specifying the two template
    // parameters.
    // The `Type` type definition defines the actual map type.
    //
    // Example:
    // ```
    //    struct MyPartitionProps { String info; };
    //    typedef TopicsPartitionsMap<
    //        EmptyProperties,      // Properties for `Topic`
    //        MyPartitionProps      // Properties for `Partition`
    //    > MyTopicsPartitionsMap;
    //
    //    MyTopicsPartitionsMap::Topics my_map;
    //    my_map["testtopic"].partitions[0].info = "Hello World";
    // ```
    //
    template < typename TTopicProperties, typename TPartitionProperties >
    struct topics_partitions_map
    {
        using partition_type  = partition< TPartitionProperties >;
        using partitions_type = std::map< int32, partition_type >;
        using topic_type      = topic< TTopicProperties, partitions_type >;
        using topics_type     = std::map< std::string, topic_type >;
    };

    //
    // Topic partition data structure using two levels of nested vectors. The top
    // level vector contains one or more `Topic` objects, each identified by a
    // `topic_name` property (string). Each of the `Topic` objects contains a bunch
    // of `Partition` objects, which themselve are identified by a `partition`
    // property (int).
    // Extend the Topic and/or Partition structures by specifying the two template
    // parameters.
    // The `Type` type definition defines the actual vector type.
    //
    // Example:
    // ```
    //    struct MyTopicProps { Int32 somenumber; };
    //    struct MyPartitionProps { String info; };
    //    typedef TopicsPartitionsVector<
    //        MyTopicProps,         // Properties for `Topic`
    //        MyPartitionProps      // Properties for `Partition`
    //    > MyTopicsPartitionsVector;
    //
    //    MyTopicsPartitionsVector::Topics my_vector(1);
    //    my_vector[0].topic_name = "test_topic";
    //    my_vector[0].somenumber = 123;
    //    my_vector[0].partitions.resize(1);
    //    my_vector[0].partitions[0].partition = 1;
    //    my_vector[0].partitions[0].info = "Hello World";
    // ```
    //
    template < typename TTopicProperties, typename TPartitionProperties >
    struct topics_partitions_vector
    {
        using partition_type  = partition< vector_partition_properties< TPartitionProperties > >;
        using partitions_type = std::vector< partition_type >;
        using topic_type      = topic< vector_topic_properties< TTopicProperties >, partitions_type >;
        using topics_type     = std::vector< topic_type >;
    };
}   // namespace detail
}   // namespace kafka
#endif   // CONNECTOR_LIB_KAFKA_DETAIL_TOPIC_PARTITIONS_HPP_B49B3EB394FE4347A36D8DC2D912D3AD
