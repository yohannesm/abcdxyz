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
  enum colors {white, grey, black};
  template <typename G>
  bool has_cycle (const G& myG) {
    std::vector<colors> vc(num_vertices(myG), white);
    return has_cycle_helper(vc, vertex(0, myG), myG);
  }
  
  template<typename G>
  bool has_cycle_helper(std::vector<colors>& visited, const typename G::vertex_descriptor& vd,   const G& myG){
       typedef typename G::adjacency_iterator adjIt;
       if(visited[vd] == grey) return true;
       if(visited[vd] == black) return false;
       std::pair<adjIt, adjIt> p = adjacent_vertices(vd, myG);
       adjIt b = p.first;
       adjIt e = p.second;
       while(b!=e){
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
