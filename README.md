# Heaps Benchmark

Benchmarking three types of Heaps - Binary Heap, Binomial Heap, and Pairing Heap - per operation, in sorting and Dijkstra algorithms.

## Overview

**Some benchmark results from Dijkstra tests :**

<img src="test/charts/dijkstra/comparison_cnt.png" width=400/> <img src="test/charts/dijkstra/iteration_cnt.png" width=400/> <img src="test/charts/dijkstra/swap_cnt.png" width=400/> <img src="test/charts/dijkstra/time.png" width=400/>

**Project Structure:**

```text
.
├── inc                # Header files
├── src                # Source files
└── test               # Tests
    ├── charts         # Test results
    │   ├── dijkstra   # Test on Dijkstra's Algorithm
    │   ├── heavy_type # Test with costly elements
    │   └── light_type # Test with atomic elements
    ├── generator      # Test generators
    └── runner         # Test runners
```
