cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)  #Android NDK supports only C++11 (maybe and 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(XT_VERSION_MAJOR 0)
set(XT_VERSION_MINOR 1)
add_definitions(-DXT_VERSION_MAJOR=${XT_VERSION_MAJOR})
add_definitions(-DXT_VERSION_MINOR=${XT_VERSION_MINOR})

set(PLATFORM "LINUX" CACHE STRING "Default platform")
set(PROJECT_NAME "XorTech" CACHE STRING "Project name")

project(${PROJECT_NAME})

message(">> Configure project ${PROJECT_NAME} for ${PLATFORM} platform")

set(XT_SOURCES
        src
        src/Core
        src/Core/Render
        src/Core/Input
        src/Core/Time
        src/Core/Log)

set(XT_INCLUDES src)
#
#   Linux
set(XT_LINUX_DEPS glfw pthread dl rt GL)

add_definitions(-DXT_PROJECT_NAME="${PROJECT_NAME}")

include_directories(src)
include_directories(src/3rd/glm)

if (${PLATFORM} STREQUAL "ANDROID")
    include(cmake/Android.cmake)
elseif(${PLATFORM} STREQUAL "LINUX")
    include(cmake/Linux.cmake)
else()
    message(ERROR_FATAL "Unknown platform")
endif()

foreach(XT_PATH ${XT_SOURCES})
    file(GLOB XT_CPP_SRCS ${PROJECT_SOURCE_DIR}/${XT_PATH}/*.cpp)
    file(GLOB XT_H_SRCS ${PROJECT_SOURCE_DIR}/${XT_PATH}/*.h)
    # ... here you can add custom type like hpp, hxx, hui and etc.
    list(APPEND XT_SOURCE_FILES ${XT_CPP_SRCS})
    list(APPEND XT_SOURCE_FILES ${XT_H_SRCS})
endforeach()

foreach(PATH ${XT_SOURCE_FILES})
    message(STATUS "Compile ${PATH}")
endforeach()

XtGenerate()
target_link_libraries(${PROJECT_NAME} ${XT_DEPS})