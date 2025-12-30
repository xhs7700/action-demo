# Implementation Tasks

## 1. QuickSort Optimizations
- [ ] 1.1 Implement median-of-three pivot selection helper function
- [ ] 1.2 Add hybrid insertionSort threshold (INSERTION_SORT_THRESHOLD = 16)
- [ ] 1.3 Refactor quickSortHelper with tail recursion optimization
- [ ] 1.4 Update quickSortHelper to call insertionSort for small ranges

## 2. MergeSort Memory Optimization
- [ ] 2.1 Add mergeSortWithBuffer helper that accepts pre-allocated buffer
- [ ] 2.2 Modify mergeSort to allocate single buffer once at top level
- [ ] 2.3 Update merge function to use shared buffer instead of local vectors

## 3. Testing & Validation
- [ ] 3.1 Add performance benchmark tests (sorted, reverse-sorted, random data)
- [ ] 3.2 Verify existing unit tests still pass
- [ ] 3.3 Run full test suite: `ctest --test-dir build --output-on-failure`
- [ ] 3.4 Build and test all platforms (Debug/Release)

## 4. Documentation
- [ ] 4.1 Update function documentation with optimization notes
- [ ] 4.2 Add performance characteristics to docstrings
