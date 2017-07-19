cmake_minimum_required(VERSION 3.2.1)

project(AIM)


set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/events_dispenser.cpp)

include_directories(${CMAKE_SOURCE_DIR}/headers)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -Wextra -pedantic")

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

find_package(Threads REQUIRED)
find_package(Boost 1.64 COMPONENTS thread REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

add_executable(aim ${SOURCES} ${HEADERS})
target_link_libraries(aim Threads::Threads)
TARGET_LINK_LIBRARIES(aim ${Boost_LIBRARIES})

set_property(TARGET aim PROPERTY CXX_STANDARD 17)