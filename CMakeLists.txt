cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)  #Android NDK supports only C++11 (maybe and 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PLATFORM "LINUX" CACHE STRING "Default platform")
set(PROJECT_NAME "XorTech" CACHE STRING "Project name")

project(${PROJECT_NAME})

message(">> Configure project ${PROJECT_NAME} for ${PLATFORM} platform")

set(XT_SOURCES src)
set(XT_INCLUDES src)

add_definitions(-DXT_PLATFORM="${PLATFORM}" -DXT_PROJECT_NAME="${PROJECT_NAME}")
include_directories(src)

foreach(XT_PATH ${XT_SOURCES})
    file(GLOB XT_CPP_SRCS ${PROJECT_SOURCE_DIR}/${XT_PATH}/*.cpp)
    file(GLOB XT_H_SRCS ${PROJECT_SOURCE_DIR}/${XT_PATH}/*.h)
    # ... here you can add custom type like hpp, hxx, hui and etc.
    list(APPEND XT_SOURCE_FILES ${XT_CPP_SRCS})
    list(APPEND XT_SOURCE_FILES ${XT_H_SRCS})
endforeach()

list(LENGTH XT_SOURCE_FILES XT_SOURCES_LENGHT)

message(">> Detected ${XT_SOURCES_LENGHT} source(s)")

if (${PLATFORM} STREQUAL "ANDROID") #IOS in future
    # We should build .so
    message(">> Build .so")
    add_library(${PROJECT_NAME} SHARED ${XT_SOURCE_FILES})
else()
    # Other platform, build executable
    message(">> Build executable")
    add_executable(${PROJECT_NAME} ${XT_SOURCE_FILES})
endif()