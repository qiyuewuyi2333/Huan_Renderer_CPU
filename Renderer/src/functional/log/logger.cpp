#pragma once
#ifdef WINDOWS_PLATFORM
#include <iostream>
#include <Windows.h>

#include "functional/log/logger.h"
#define FOREGROUND_DEFAULT 0x0007
#define FOREGROUND_GREEN 0x0002  // text color contains green.
#define FOREGROUND_RED 0x0004    // text color contains red.
#define FOREGROUND_YELLOW 0x0006 // text color contains yellow.

namespace huan_renderer_cpu
{
namespace functional
{
Logger::~Logger()
{
    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h_console, FOREGROUND_DEFAULT);
}
void Logger::error(const char* message)
{
    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h_console, FOREGROUND_RED);
    std::cout << "ERROR: " << message << std::endl;
}
void Logger::warning(const char* message)
{
    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h_console, FOREGROUND_RED | FOREGROUND_GREEN);
    std::cout << "WARNING: " << message << std::endl;
}
void Logger::info(const char* message)
{
    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h_console, FOREGROUND_GREEN);
    std::cout << "INFO: " << message << std::endl;
}
void Logger::debug(const char* message)
{
    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h_console, FOREGROUND_DEFAULT);
    std::cout << "DEBUG: " << message << std::endl;
}

} // namespace functional
} // namespace huan_renderer_cpu

#endif
