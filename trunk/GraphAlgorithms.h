// ------------------------------------
// projects/c++/graph/GraphAlgorithms.h
// Copyright (C) 2009
// Glenn P. Downing
// ------------------------------------

#ifndef GraphAlgorithms_h
#define GraphAlgorithms_h

// --------
// includes
// --------

#include <cassert> // assert

// ----------
// namespaces
// ----------

namespace cs {

// ---------
// has_cycle
// ---------

/**
 * depth-first traversal
 * three colors
 * <your documentation>
 */
template <typename G>
bool has_cycle (const G& g) {
    return true;}

// ----------------
// topological_sort
// ----------------

/**
 * depth-first traversal
 * two colors
 * <your documentation>
 * Precondition: !has_cycle(g)
 */
template <typename G, typename OI>
void topological_sort (const G& g, OI x) {
    *x = 2;
    ++x;
    *x = 0;
    ++x;
    *x = 1;
    }

} // cs

#endif // GraphAlgorithms_h
