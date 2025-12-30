# Change: Optimize Sorting Algorithms Performance

## Why
Current sorting implementations (quickSort, mergeSort) use basic algorithms without modern optimizations. This leads to:
- QuickSort O(n²) worst case on sorted/reverse-sorted data (common in practice)
- Excessive memory allocation in mergeSort (creates temporary vectors on every merge call)
- Poor cache locality causing CPU cache misses on large datasets

## What Changes
1. **QuickSort optimizations**:
   - Median-of-three pivot selection to avoid O(n²) on sorted data
   - Tail recursion optimization to reduce stack depth
   - Hybrid approach: switch to insertionSort for small subarrays (< 16 elements)
2. **MergeSort memory optimization**:
   - Pre-allocate single temporary buffer, reuse across all merge operations
   - Eliminates O(n log n) allocations
3. **Cache-aware data layout** (future-proofing):
   - Document alignment considerations for data structures

## Impact
- Affected specs: `sorting` (new capability)
- Affected code:
  - `src/algorithms/include/algorithms/sort.h:19-78` (quickSort implementation)
  - `src/algorithms/include/algorithms/sort.h:88-159` (mergeSort implementation)
  - `src/algorithms/src/sort.cpp` (template instantiations - unchanged)
- Performance improvements:
  - QuickSort: 2-3x faster on nearly-sorted data
  - MergeSort: ~30% faster due to reduced allocations
- Backward compatible: no API changes
