﻿cmake_minimum_required(VERSION 3.0.0)
project(example VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)

add_executable(example example.cpp
        uri-example.cpp) # This is only for testing purposes
target_include_directories(example PRIVATE includes)
target_link_libraries(example PRIVATE cnet)


set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${PROJECT_NAME}")
set_target_properties(${PROJECT_NAME} PROPERTIES INTERMEDIATE_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/obj/${PROJECT_NAME}")
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "-debug")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")