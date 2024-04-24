cmake_minimum_required(VERSION 3.0.0)
project(cnet-cli VERSION 0.0.1)
project(cnet VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)


add_library(cnet STATIC
        includes/http_client.h
        includes/http_method.h
        includes/http_message.h
        includes/tcp_client.h
        includes/uri.h
        src/tcp_client.cpp
        src/http_client.cpp
        src/uri.cpp
)

# CLI
add_executable(cnet-cli
        cnet-cli/main.cpp
)
target_link_libraries(cnet-cli PUBLIC cnet)
target_include_directories(${PROJECT_NAME} PUBLIC vendor)
target_include_directories(${PROJECT_NAME} PUBLIC includes)


# link winsock2
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC wsock32 ws2_32)
endif ()


# Properties
set_target_properties(cnet-cli PROPERTIES INTERMEDIATE_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/obj/${PROJECT_NAME}")
set_target_properties(cnet-cli PROPERTIES DEBUG_POSTFIX "-debug")
set_target_properties(cnet-cli PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${PROJECT_NAME}")
set_target_properties(cnet-cli PROPERTIES OUTPUT_NAME "cnet-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

target_compile_options(${PROJECT_NAME} PRIVATE -Oz)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static -lpthread")


# Include OpenSSL
set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenSSL::SSL)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenSSL::Crypto)