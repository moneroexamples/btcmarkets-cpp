cmake_minimum_required(VERSION 2.8)
project(btcmarketesxamples)

set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -std=c++11")

# find boost
find_package(Boost COMPONENTS
        program_options
        REQUIRED)

# include boost headers
include_directories(
        ${Boost_INCLUDE_DIRS})

set(SOURCE_FILES
        examples.cpp)


set(USE_SYSTEM_CURL 1)
add_subdirectory(cpr)

include_directories(${CPR_INCLUDE_DIRS})

add_executable(btcmarketsexamples
        ${SOURCE_FILES})

target_link_libraries(btcmarketsexamples
        crypto
        ${CPR_LIBRARIES}
        ${Boost_LIBRARIES}
        pthread)