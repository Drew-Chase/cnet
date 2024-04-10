cmake_minimum_required(VERSION 3.0.0)
project(cnet VERSION 0.0.1)
project(example VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)


add_library(cnet STATIC
        src/http_client.cpp
        includes/http_client.h
        includes/http_method.h
        includes/http_message.h
        src/tcp_client.cpp
        includes/tcp_client.h
        src/uri.cpp
        includes/uri.h)

# Example
add_executable(example example/example.cpp
        example/uri-example.cpp) # This is only for testing purposes
target_include_directories(example PRIVATE includes)
target_link_libraries(example cnet)

# Properties

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${PROJECT_NAME}")
set_target_properties(${PROJECT_NAME} PROPERTIES INTERMEDIATE_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/obj/${PROJECT_NAME}")
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "-debug")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

target_include_directories(cnet PRIVATE includes)


