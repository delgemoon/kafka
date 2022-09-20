message("kafka build")
add_executable(kafka_ut main.spec.cpp endian.spec.cpp response_read.spec.cpp request_write.spec.cpp functional_test.spec.cpp metadata_request_write_test.spec.cpp)