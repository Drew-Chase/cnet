cmake_minimum_required(VERSION 3.0.0)
project(cnet VERSION 0.0.1)
project(cnet-cli VERSION 0.0.1)
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

# CLI
add_executable(cnet-cli
        cnet-cli/main.cpp
        cnet-cli/cclip.hpp
)
target_link_libraries(cnet-cli PUBLIC cnet)


# link winsock2
if (WIN32)
    target_link_libraries(cnet PUBLIC wsock32 ws2_32)
endif ()


# Properties
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${PROJECT_NAME}")
set_target_properties(${PROJECT_NAME} PROPERTIES INTERMEDIATE_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/obj/${PROJECT_NAME}")
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "-debug")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

target_include_directories(cnet PUBLIC includes)

# Check if the configuration is Release
if (CMAKE_BUILD_TYPE MATCHES Release)
    message("Release mode")
    target_compile_options(cnet PUBLIC -O3)
    target_compile_options(cnet PUBLIC -s)
endif ()

# Include VCPKG
find_package(OpenSSL REQUIRED)
target_link_libraries(cnet PUBLIC OpenSSL::SSL)
target_link_libraries(cnet PUBLIC OpenSSL::Crypto)