cmake_minimum_required(VERSION 2.8)
project(btcmarketmain)

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
        main.cpp)

add_subdirectory(cpr)

include_directories(${CPR_INCLUDE_DIRS})
include_directories(${BTCMEXT_INCLUDE_DIRS})

add_executable(btcmarketmain
        ${SOURCE_FILES})

target_link_libraries(btcmarketmain
        ${BTCM_LIBRARY}
        ${Boost_LIBRARIES}
        pthread)