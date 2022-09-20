# libkafka-asio
C++ Kafka Client Library using Boost Asio

[![Build Status](https://travis-ci.org/danieljoos/libkafka-asio.svg?branch=master)](https://travis-ci.org/danieljoos/libkafka-asio)
[![Documentation Status](https://readthedocs.org/projects/libkafka-asio/badge/?version=latest)](https://readthedocs.org/projects/libkafka-asio/?badge=latest)

## Introduction

`libkafka` is a C++ header-only library, implementing the Kafka client 
protocol. All Kafka APIs, including offset commit/fetch, are implemented:

* [Metadata](https://cwiki.apache.org/confluence/display/KAFKA/A+Guide+To+The+Kafka+Protocol#AGuideToTheKafkaProtocol-MetadataAPI)
* [Produce](https://cwiki.apache.org/confluence/display/KAFKA/A+Guide+To+The+Kafka+Protocol#AGuideToTheKafkaProtocol-ProduceAPI)
* [Fetch](https://cwiki.apache.org/confluence/display/KAFKA/A+Guide+To+The+Kafka+Protocol#AGuideToTheKafkaProtocol-FetchAPI)
* [Offset](https://cwiki.apache.org/confluence/display/KAFKA/A+Guide+To+The+Kafka+Protocol#AGuideToTheKafkaProtocol-OffsetAPI)
* [Offset Commit/Fetch](https://cwiki.apache.org/confluence/display/KAFKA/A+Guide+To+The+Kafka+Protocol#AGuideToTheKafkaProtocol-OffsetCommit/FetchAPI)

It supports GZIP and Snappy message compression and therefore relies on the [zlib](http://www.zlib.net/) and [Snappy](https://code.google.com/p/snappy/) libraries.
Message compression can optionally be turned off.

The library was tested on Linux Fedora 36. There is a set of unit tests available under [`tests`](test/).

## Usage

Add the [`kafka`](kafka/) directory to your include paths and:
```
#include <kafka/kafka.hpp>
```
Please see the [`examples`](examples/) directory for some examples on how to use the library.

Also consult the documentation: [libkafka-asio Reference](http://libkafka-asio.rtfd.org/)

## Dependencies

`libkafka-asio` depends on the [Boost C++ libraries](http://www.boost.org/) -- specially on Boost Asio. The following Boost sub-libraries are explicitly used in the project:

* [boost asio](http://www.boost.org/doc/libs/release/doc/html/boost_asio.html)
* [boost bind](http://www.boost.org/doc/libs/release/libs/bind/bind.html)
* [boost crc](http://www.boost.org/doc/libs/release/libs/crc/)
* [boost foreach](http://www.boost.org/doc/libs/release/doc/html/foreach.html)
* [boost integer](http://www.boost.org/doc/libs/release/libs/integer/doc/html/index.html)
* [boost iterator](http://www.boost.org/doc/libs/release/libs/iterator/doc/index.html)
* [boost smart ptr](http://www.boost.org/doc/libs/release/libs/smart_ptr/smart_ptr.htm)
* [boost system](http://www.boost.org/doc/libs/release/libs/system/doc/index.html)

You need to link against `boost_thread` and `boost_system`.

So installing the boost library package on your distribution should do the trick (e.g. `apt-get install libboost-dev` on Ubuntu, or `pacman -S boost` on Arch).