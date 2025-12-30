# Sorting Algorithms Specification

## ADDED Requirements

### Requirement: QuickSort Median-of-Three Pivot Selection
The quickSort algorithm SHALL use median-of-three pivot selection to avoid O(n²) worst-case performance on sorted or reverse-sorted input.

#### Scenario: Sorted array performance
- **WHEN** quickSort is called on an already-sorted array of size n
- **THEN** the algorithm SHALL complete in O(n log n) time
- **AND** shall not degrade to O(n²) behavior

#### Scenario: Reverse-sorted array performance
- **WHEN** quickSort is called on a reverse-sorted array of size n
- **THEN** the algorithm SHALL complete in O(n log n) time
- **AND** shall not degrade to O(n²) behavior

### Requirement: QuickSort Hybrid Insertion Sort
The quickSort algorithm SHALL switch to insertionSort for subarrays smaller than 16 elements.

#### Scenario: Small subarray optimization
- **WHEN** quickSort recursion reaches a subarray of size < 16
- **THEN** the algorithm SHALL use insertionSort instead of continuing recursion
- **AND** reduce overall function call overhead

### Requirement: QuickSort Tail Recursion Optimization
The quickSort algorithm SHALL use tail recursion optimization to minimize stack depth by recursing on the smaller partition first.

#### Scenario: Deep recursion prevention
- **WHEN** quickSort partitions an array into left and right subarrays
- **THEN** it SHALL recurse on the smaller subarray first
- **AND** use iteration for the larger subarray
- **AND** limit maximum stack depth to O(log n)

### Requirement: MergeSort Single Buffer Allocation
The mergeSort algorithm SHALL pre-allocate a single temporary buffer at the top level and reuse it across all merge operations.

#### Scenario: Memory allocation reduction
- **WHEN** mergeSort is called on an array of size n
- **THEN** exactly one temporary buffer of size n SHALL be allocated
- **AND** this buffer SHALL be reused for all O(log n) merge operations
- **AND** no additional allocations occur during recursion

#### Scenario: Performance improvement verification
- **WHEN** mergeSort completes on an array of size 10000
- **THEN** memory allocations SHALL be reduced by at least 50% compared to previous implementation
- **AND** sorting time SHALL improve by at least 20%

### Requirement: Cache-Friendly Data Structure Layout
Data structure implementations SHALL document cache line alignment considerations (64 bytes) for frequently accessed members.

#### Scenario: Documentation guidance
- **WHEN** developers implement or modify data structures
- **THEN** documentation SHALL provide guidance on cache-friendly layout
- **AND** recommend placing frequently accessed fields together
- **AND** consider padding for cache line boundaries when appropriate

#### Scenario: Future alignment verification
- **WHEN** performance-critical data structures are modified
- **THEN** alignment annotations SHALL be added where beneficial
- **AND** documentation SHALL explain the cache performance rationale