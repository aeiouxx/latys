cmake_minimum_required(VERSION 3.21)
project(latys LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(Options)
include(Versioning)
message(STATUS "Definitions: ${COMPILE_DEFINITIONS}")
message(STATUS "CXX flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "-----------------> Building ${PROJECT_NAME} version ${PROJECT_VERSION}")
include(Platform)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SOURCES src/main.cc)
add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${COMPILE_DEFINITIONS})
target_include_directories(${PROJECT_NAME} 
  PRIVATE
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ext/wintun)
# -------------------- DEPENDENCIES --------------------
include(Dependencies)
# -------------------- DEPENDENCIES --------------------
#include(Tests)
