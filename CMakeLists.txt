cmake_minimum_required(VERSION 3.5.2)

project(AIM)


set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/reactor.cpp)

include_directories(${CMAKE_SOURCE_DIR}/headers)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")

add_executable(aim ${SOURCES} ${HEADERS})
set_property(TARGET aim PROPERTY CXX_STANDARD 14)