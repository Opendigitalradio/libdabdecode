cmake_minimum_required(VERSION 3.1)
project("DABDecode"
  LANGUAGES CXX
  VERSION 1.0.1)

string(TOUPPER ${PROJECT_NAME} ${PROJECT_NAME}_UPPER)
string(TOLOWER ${PROJECT_NAME} ${PROJECT_NAME}_LOWER)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")
set(CXX_VERSION "c++11")

include("CompilerSetup")
include("ConanPackages")

install_conan_packages(SYSTEM_HEADERS
  PKGOPTS ${CONAN_OPTIONS}
  )

find_package(Boost REQUIRED)

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
include_directories("include")

add_subdirectory("include")
add_subdirectory("src")

install(EXPORT ${PROJECT_NAME}
  DESTINATION share/${${PROJECT_NAME}_LOWER}/cmake
  )

export(EXPORT ${PROJECT_NAME})
