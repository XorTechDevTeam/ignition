cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)  #Android NDK supports only C++11 (maybe and 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PLATFORM "NONE" CACHE STRING "Default platform")
set(PROJECT_NAME "XorTech" CACHE STRING "Project name")

project(${PROJECT_NAME})

<<<<<<< HEAD
if (NOT PLATFORM STREQUAL "NONE")
    set(XT_INITED_BUILD 0)
    message(">> ----------------------------------------------------------")
    message(">> Configure project ${PROJECT_NAME} for ${PLATFORM} platform")
    message(">> ----------------------------------------------------------")

    set(XT_SOURCES
            src
            src/Core
            src/Core/Render
            src/Core/Input
            src/Core/Time
            src/Core/Log)

    set(XT_INCLUDES src)

    add_definitions(-DXT_PROJECT_NAME="${PROJECT_NAME}")

    include_directories(src)
    include_directories(src/3rd/glm)

    if (PLATFORM STREQUAL "ANDROID")
        include(cmake/Android.cmake)
        message(STATUS ">> Include build scripts for Android")
    elseif(PLATFORM STREQUAL "LINUX")
        include(cmake/Linux.cmake)
        message(STATUS ">> Include build scripts for Linux")
    else()
        message(STATUS ">> Unsupported platform ${PLATFORM}")
    endif()

    foreach(XT_PATH ${XT_SOURCES})
        file(GLOB XT_CPP_SRCS ${PROJECT_SOURCE_DIR}/${XT_PATH}/*.cpp)
        file(GLOB XT_H_SRCS ${PROJECT_SOURCE_DIR}/${XT_PATH}/*.h)
        # ... here you can add custom type like hpp, hxx, hui and etc.
        list(APPEND XT_SOURCE_FILES ${XT_CPP_SRCS})
        list(APPEND XT_SOURCE_FILES ${XT_H_SRCS})
    endforeach()

    XtGenerate()
    target_link_libraries(${PROJECT_NAME} ${XT_DEPS})
else()
    message(ERROR_FATAL "Unknown platform")
endif()
=======
message(">> Configure project ${PROJECT_NAME} for ${PLATFORM} platform")

set(XT_DEPS
        angelscript)

set(XT_SOURCES
        src
        src/Core
        src/Core/Render
        src/Core/Input
        src/Core/Time
        src/Core/Event
        src/Core/Logic
        src/Core/Log
        src/Modules)

set(XT_INCLUDES src)
#
#   Linux
set(XT_LINUX_DEPS glfw pthread dl rt GL)

add_definitions(-DXT_PROJECT_NAME="${PROJECT_NAME}")

include_directories(src)
include_directories(src/3rd/glm)
include_directories(src/3rd/AngelScript/include)

add_subdirectory(src/3rd/AngelScript/projects/cmake)

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
>>>>>>> origin/modules
