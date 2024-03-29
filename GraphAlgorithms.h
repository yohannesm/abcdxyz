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

  enum colors {white, grey, black};

  /**
   * depth-first traversal
   * three colors
   * looking for a cycle inside a graph
   * @return true if the graph has a cycle, false otherwise
   */
  template <typename G>
  bool has_cycle (const G& myG) {
    std::vector<colors> vc(num_vertices(myG), white);
    return has_cycle_helper(vc, vertex(0, myG), myG);
  }
  
  template<typename G>
  bool has_cycle_helper(std::vector<colors>& visited, const typename G::vertex_descriptor& vd, const G& myG) {
    typedef typename G::adjacency_iterator adjit;
    if(visited[vd] == grey) return true;
    if(visited[vd] == black) return false;
    std::pair<adjit, adjit> p = adjacent_vertices(vd, myG);
    adjit b = p.first;
    adjit e = p.second;
    while(b != e) {
      visited[vd] = grey;
      if(has_cycle_helper(visited, *b, myG)) return true;
      ++b;
    }      
    visited[vd] = black;
    return false;
  }

  // ----------------
  // topological_sort
  // ----------------

  /**
   * depth-first traversal
   * two colors
   * printing a topological ordering of a graph
   * Precondition: !has_cycle(g)
   */
  template <typename G, typename OI>
  void topological_sort (const G& myG, OI x) {
    assert(!has_cycle(myG));
    std::vector<colors> vc(num_vertices(myG), white);
    typedef typename G::vertex_iterator vertit;
    std::pair<vertit, vertit> p = vertices(myG);
    vertit b = p.first;
    vertit e = p.second;

    while(b != e){
      topological_sort_helper(vc, *b, x, myG);
      ++b;
    }
  }

  template <typename G, typename OI>
  void topological_sort_helper(std::vector<colors>& visited,
			       const typename G::vertex_descriptor& vd,
			       OI x, const G& myG) {
    typedef typename G::adjacency_iterator adjit;
    std::pair<adjit, adjit> p = adjacent_vertices(vd, myG);
    adjit b = p.first;
    adjit e = p.second;

    if(visited[vd] == black)
      return;
    if(e == b) {
      visited[vd] = black;
      *x = vd; ++x;
      return;
    }
    while(b != e) {
      topological_sort_helper(visited, *b, x, myG);
      ++b;
    }      
    visited[vd] = black;
    *x = vd; ++x;
  }
} // cs

#endif // GraphAlgorithms_h
