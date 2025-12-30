# Design: Sorting Algorithm Optimizations

## Context
The current sorting implementations use textbook algorithms without production-grade optimizations. This change affects core algorithm performance and sets patterns for future optimizations across the codebase.

**Background**: Educational C++ project demonstrating algorithms and CI/CD practices.  
**Constraints**: Must maintain C++17 compatibility, zero external dependencies, cross-platform (Linux/macOS/Windows).  
**Stakeholders**: Students learning algorithms, developers using library for performance-sensitive tasks.

## Goals / Non-Goals

**Goals:**
- Improve quickSort average-case performance by 2-3x on real-world data
- Reduce mergeSort memory allocations from O(n log n) to O(n)
- Maintain backward compatibility (no API changes)
- Establish cache-aware coding patterns for future work

**Non-Goals:**
- Not replacing std::sort (this is educational)
- Not adding parallel/multi-threaded sorting
- Not implementing additional sort algorithms (heapSort, etc.)
- Not changing template interface or comparison function API

## Decisions

### Decision 1: Median-of-Three Pivot Selection
**Choice**: Use first, middle, and last elements for pivot selection.  
**Rationale**: 
- Simple to implement (no random number generation)
- Effective against sorted/reverse-sorted inputs
- Minimal overhead (3 comparisons)

**Alternatives considered**:
- Random pivot: requires RNG, non-deterministic
- Median-of-five: more comparisons, diminishing returns
- Single pivot (current): O(n²) on sorted data (unacceptable)

### Decision 2: Insertion Sort Threshold = 16
**Choice**: Switch to insertionSort when subarray size < 16.  
**Rationale**:
- Industry standard (used by std::sort implementations)
- Empirically proven optimal for small arrays
- Insertion sort has lower overhead than quickSort recursion

**Alternatives considered**:
- Threshold = 8: misses optimization opportunities
- Threshold = 32: too much overhead from insertionSort O(n²)
- No hybrid: wastes time on small subarrays

### Decision 3: Tail Recursion on Larger Partition
**Choice**: Recurse on smaller partition, iterate on larger.  
**Rationale**:
- Guarantees O(log n) stack depth
- Prevents stack overflow on adversarial inputs
- Compiler may optimize tail call to iteration

**Alternatives considered**:
- Both recursive: risks O(n) stack depth
- Iterative with explicit stack: more complex code

### Decision 4: Single Buffer for MergeSort
**Choice**: Allocate vector<T> buffer once at top level, pass by reference.  
**Rationale**:
- Eliminates O(log n) allocations per recursion level
- Modern move semantics reduce copy overhead
- Buffer size = input size (no wasted space)

**Alternatives considered**:
- In-place merge: O(n²) complexity (defeats purpose)
- Buffer per level: current approach (wasteful)
- Parallel merge: out of scope (no threading)

### Decision 5: Cache Alignment - Documentation Only
**Choice**: Document guidelines without enforcing alignment now.  
**Rationale**:
- Premature optimization without profiling data
- Alignment directives (alignas) are compiler-specific
- Educational project prioritizes clarity over micro-optimization

**Future work**: Add alignas(64) to hot data structures after benchmarking.

## Risks / Trade-offs

| Risk | Impact | Mitigation |
|------|--------|------------|
| Breaking behavior for existing code expecting exact O(n²) on sorted data | Low | Unit tests verify output correctness, not complexity |
| Increased code complexity | Medium | Add detailed comments, maintain educational clarity |
| Threshold tuning may not be optimal for all types T | Low | 16 is empirically good for primitives and small objects |
| Shared buffer in mergeSort adds parameter | None | Internal helper, public API unchanged |

**Trade-offs**:
- Code simplicity vs performance: accepting 20% more code for 2-3x speedup
- Memory (temporary buffer) vs speed: still O(n) space as before, just better managed

## Migration Plan

**Phase 1: Implementation**
1. Add optimized helpers (`medianOfThree`, `mergeSortWithBuffer`) alongside existing code
2. Update public functions (`quickSort`, `mergeSort`) to use new helpers
3. No API changes - users recompile, no code modifications needed

**Phase 2: Validation**
1. Run existing test suite (tests/algorithms/test_sort.cpp)
2. Add benchmark tests comparing old vs new performance
3. CI matrix (Debug/Release × Ubuntu/macOS/Windows) must pass

**Phase 3: Deployment**
- Single PR with all changes (small scope, low risk)
- No runtime configuration needed
- No data migration (algorithms are stateless)

**Rollback**: Revert commit if tests fail (git revert, no state to clean up)

## Open Questions
1. Should we add a compile-time flag to disable optimizations for teaching basic algorithms?
   - **Answer**: No, defeats purpose. Keep old versions in git history.
2. Profile actual performance gains on CI platforms?
   - **Answer**: Yes, add benchmark tests showing before/after (task 3.1)
