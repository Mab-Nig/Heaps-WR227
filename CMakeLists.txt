cmake_minimum_required(VERSION 3.27)

project(TechnicalWriting)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")

add_executable(${PROJECT_NAME}
  BinaryHeap.hpp
  BinomialHeap.hpp
  # Dijkstra.hpp
  # Dijkstra.cpp
  # HeapSort.hpp
  Graph.hpp
  Graph.cpp
  Heap.hpp
  Helper.hpp
  Helper.cpp
  Int.hpp
  Int.cpp
  PairingHeap.hpp
  String.hpp
  String.cpp
  vec_utils.hpp

  main.cpp)

target_include_directories(${PROJECT_NAME}
  PRIVATE
  .)

add_subdirectory(test)
