/**
 * XorTech Source Code
 */
#pragma once

/**
 * Detect entry point
 */
#if defined(XT_LINUX) || defined(XT_OSX)        //Linux & OSX
#define XT_ENTRY int main()
#elif defined(XT_ANDROID) || defined(XT_IOS)    //Android & IOS
#define XT_ENTRY int XT_main()
#elif defined(XT_WINDOWS)                       //Windows
#include <Windows.h>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
#error Unsupported platform
#endif

#define XT_SCREEN_MIN_WIDTH  800
#define XT_SCREEN_MIN_HEIGHT 480


/**
 *  Common sources
 */
#include <cstdlib>      //malloc, calloc, memset, bzero
#include <cstdio>       //printf
#include <cstring>      //memcpy
#include <cstdarg>      //variadic
#include <cstdint>      //uint8/16/32/64 int8/16/32/64

#include <string>
#include <list>
#include <forward_list>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <queue>
#include <thread>
#include <mutex>
#include <chrono>
#include <algorithm>
#include <functional>

#if defined(XT_LINUX)
#include <pthread.h>
#include <unistd.h>
#include <csignal>

#include <GLFW/glfw3.h>

#undef XT_SCREEN_MIN_WIDTH
#undef XT_SCREEN_MIN_HEIGHT

#define XT_SCREEN_MIN_WIDTH  800
#define XT_SCREEN_MIN_HEIGHT 600

#include <Core/Platform/Linux/XtDefaultDevice.h>

#endif

/**
 * Custom aliases
 */
using String = std::string;
using Guard = std::lock_guard<std::mutex>;
template <typename T> using Vector = std::vector<T>;
template <typename T> using List = std::forward_list<T>;
template <typename T> using Queue = std::queue<T>;
template <typename K, typename V> using Map = std::map<K, V>;
template <typename K, typename V> using UnorderedMap = std::unordered_map<K, V>;
template <typename K, typename V> using Pair = std::pair<K, V>;

#include <glm/glm.hpp>
using namespace glm;

#include <Core/Log/XtLogManager.h>

#ifndef NDEBUG
#define LOGMSG(format, ...) (xt::log::XtLogManager::getInstance()->operator()(format, ##__VA_ARGS__))
#else
#define LOGMSG(format, ...)
#endif

#if (defined(XT_LINUX) || defined(XT_ANDROID) || defined(XT_IOS)) && !defined(XT_USE_VULKAN) && !defined(XT_USE_METAL)
#include <Core/Render/OpenGL/XtOpenGL.h>
#endif