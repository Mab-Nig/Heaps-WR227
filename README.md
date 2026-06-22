# Heaps Benchmark

Benchmarking three types of Heaps - Binary Heap, Binomial Heap, and Pairing Heap - per operation, in sorting and Dijkstra algorithms.

## Overview

**Some benchmark results from Dijkstra tests :**

<img src="test/charts/dijkstra/comparison_cnt.png" width=400/> <img src="test/charts/dijkstra/iteration_cnt.png" width=400/> <img src="test/charts/dijkstra/swap_cnt.png" width=400/> <img src="test/charts/dijkstra/time.png" width=400/>

**Project Structure:**

```text
.
├── inc                                  # Header files
├── src                                  # Source files
└── test                                 # Tests
    ├── charts                           # Test results
    │   ├── dijkstra                     # Test on Dijkstra's Algorithm
    │   ├── heavy_type                   # Test with costly elements
    │   │   ├── alternating
    │   │   ├── heap_sort
    │   │   ├── meld
    │   │   └── sequential
    │   │       ├── deletion_only
    │   │       └── insertion_only
    │   └── light_type                   # Test with atomic elements
    │       ├── alternating
    │       ├── heap_sort
    │       ├── meld
    │       └── sequential
    │           ├── deletion_only
    │           └── insertion_only
    ├── generator                        # Test generators
    └── runner                           # Test runners
```

## Build and Run

**Build with:**

```text
cmake --build build
```

**Run all tests with:**

```text
./build/TechnicalWriting  # You can change its name via PROJECT_NAME in CMakeLists.txt
```
