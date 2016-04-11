cmake_minimum_required(VERSION 3.0)
project(dabdecode CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "The build type" FORCE)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

set(OUTPUT_PREFIX "${CMAKE_BINARY_DIR}/products/${CMAKE_BUILD_TYPE}" CACHE STRING "The build product prefix")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_PREFIX}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_PREFIX}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

set(CMAKE_CXX_FLAGS "-std=c++11 -pedantic -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  string(APPEND CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address,undefined")
endif()

include_directories("include")
add_subdirectory("src")
