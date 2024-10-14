cmake_minimum_required(VERSION 3.5.0)
project(
  Renderer_On_CPU
  VERSION 0.1.0
  LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置库和可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

option(BUILD_PLATFORM_WINDOWS "Build for Windows" ON)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  message(STATUS "Use Clang kit")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  message(STATUS "Use GNU kit")
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  message(STATUS "Configure in Debug Mode")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
  message(STATUS "Configure in Release Mode")
endif()


file(GLOB_RECURSE RENDERER_SRC CONFIGURE_DEPENDS
     ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/src/*.cpp)

add_executable(Renderer_On_CPU ${RENDERER_SRC})


target_include_directories(Renderer_On_CPU PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/include/)


if(${BUILD_PLATFORM_WINDOWS})
    message(STATUS "Build for Windows")
    target_compile_definitions(Renderer_On_CPU PUBLIC WINDOWS_PLATFORM)
endif()
