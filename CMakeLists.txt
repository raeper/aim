cmake_minimum_required(VERSION 3.5.2)

project(RAEP)


set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/headers)


add_executable(raep ${SOURCES} ${HEADERS})
set_property(TARGET raep PROPERTY CXX_STANDARD 11)