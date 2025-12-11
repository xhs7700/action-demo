// Explicit template instantiations for Heap
// This file can be used for common types if needed

#include "data_structures/heap.h"

namespace data_structures {

// Explicit instantiations for common types
template class Heap<int>;
template class Heap<double>;
template class Heap<int, std::greater<int>>;

} // namespace data_structures
