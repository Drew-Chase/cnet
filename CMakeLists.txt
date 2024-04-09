cmake_minimum_required(VERSION 3.0.0)
project(cnet VERSION 0.0.1)
project(example VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
add_executable(example example/example.cpp) # This is only for testing purposes
target_include_directories(example PRIVATE includes)

add_library(cnet STATIC
        src/http_client.cpp
        includes/http_client.h)
target_include_directories(cnet PRIVATE includes)

