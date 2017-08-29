cmake_minimum_required(VERSION 3.1)
project("DABDecode"
  LANGUAGES CXX
  VERSION 1.0.2)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/config/Base.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/config/Options.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/config/Dependencies.cmake")

find_package(Boost REQUIRED)

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
include_directories("include")

add_subdirectory("include")
add_subdirectory("src")
