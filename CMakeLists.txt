cmake_minimum_required(VERSION 3.2.1)

project(AIM)


set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/events_dispenser.cpp)

include_directories(${CMAKE_SOURCE_DIR}/headers)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(aim ${SOURCES} ${HEADERS})
target_link_libraries(aim Threads::Threads)

set_property(TARGET aim PROPERTY CXX_STANDARD 17)