cmake_minimum_required(VERSION 3.15.0)
cmake_policy(SET CMP0016 NEW)
set(CMAKE_BUILD_TYPE Debug)

project(protobuf_parser VERSION 1.0.0 DESCRIPTION "Разбор потока length-prefixed Protobuf сообщений на C++")

set(SRCS
    main.cpp
    src/protobuf_parser/DelimitedMessagesStreamParser.cpp
    src/protobuf_parser/helpers.cpp
)

add_subdirectory(test)
add_subdirectory(src/protobuf)

enable_testing()

add_executable(protobuf_parser ${SRCS})
target_link_libraries(protobuf_parser Message)

