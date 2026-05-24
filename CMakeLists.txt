cmake_minimum_required(VERSION 3.27)

project(TechnicalWriting)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")

add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE
  .
  inc)

add_subdirectory(src)
add_subdirectory(test)
