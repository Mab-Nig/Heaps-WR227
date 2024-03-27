cmake_minimum_required(VERSION 3.27)

project(TechnicalWriting)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")

add_executable(${PROJECT_NAME}
  BinaryHeap.hpp
  BinomialHeap.hpp
  Heap.hpp
  PairingHeap.hpp
  
  Dijkstra.hpp
  Dijkstra.cpp
  HeapSort.hpp

  Helper.hpp
  Helper.cpp
  main.cpp)

target_include_directories(${PROJECT_NAME}
  PRIVATE
  .)

add_subdirectory(test)
