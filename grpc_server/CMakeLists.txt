cmake_minimum_required(VERSION 3.20)
project(grpc_server)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

set(PROTO_FILES "${CMAKE_CURRENT_SOURCE_DIR}/../protos/hello.proto")
add_library(protolib)
target_link_libraries(protolib gRPC::grpc++)
target_include_directories(
  protolib PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
                  ${CMAKE_CURRENT_SOURCE_DIR}/../protos)
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(
  TARGET
  protolib
  LANGUAGE
  cpp
  PROTOS
  ${PROTO_FILES}
  IMPORT_DIRS
  "${CMAKE_CURRENT_SOURCE_DIR}/../protos")
protobuf_generate(
  TARGET
  protolib
  LANGUAGE
  grpc
  GENERATE_EXTENSIONS
  .grpc.pb.h
  .grpc.pb.cc
  PLUGIN
  "protoc-gen-grpc=${grpc_cpp_plugin_location}"
  PROTOS
  ${PROTO_FILES}
  IMPORT_DIRS
  "${CMAKE_CURRENT_SOURCE_DIR}/../protos")

add_executable(server src/server.cc)
target_link_libraries(server protolib)
