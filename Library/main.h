#ifndef MAIN_H
#define MAIN_H

#if defined(__WINDOWS__) || defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN32__) || defined(__TOS_WIN__)
#	define OS_NAME "Windows"
#	define OS_WINDOWS
#elif defined(__linux__) || defined(linux) || defined(__linux) || defined(__LINUX__) || defined(LINUX) || defined(_LINUX)
#	define OS_NAME "Linux"
#	define OS_LINUX
#else
#	define NUT_PLATFORM_OS_NAME "Unknown"
#	error unknown os
#endif

#include <string>
#include <iostream>
#include <vector>

#include <ctime>

#define CLEAR

#endif // MAIN_H
