// ----------------------
// projects/graph/Graph.h
// Copyright (C) 2008
// Glenn P. Downing
// ----------------------

#ifndef Graph_h
#define Graph_h

// --------
// includes
// --------

#include <cassert> // assert
#include <cstddef> // size_t
#include <list>    // list
#include <set>     // set
#include <utility> // make_pair, pair
#include <vector>  // vector

// ----------
// namespaces
// ----------

namespace cs {

  // -----
  // Graph
  // -----

  class Graph {
  public:
    // --------
    // typedefs
    // --------

    typedef unsigned int vertex_descriptor;
    typedef std::pair<vertex_descriptor, vertex_descriptor>
            edge_descriptor;
    
    typedef std::set<vertex_descriptor>::iterator adjacency_iterator;

    typedef std::size_t vertices_size_type;
    typedef std::size_t edges_size_type;

  public:

    // ---------
    // viterator
    // ---------

    /**
     * <your documentation>
     */
    class vertex_iterator {
    private:
      vertex_descriptor pos;
    public:
      vertex_iterator(vertex_descriptor pos) {
	this->pos = pos;
      }

      vertex_iterator operator ++ () {
	++pos;
	return *this;
      }

      vertex_iterator operator ++ (int) {
	vertex_iterator tmp(*this);
	pos++;
	return tmp;
      }

      vertex_descriptor operator * () {
	return pos;
      }

      bool operator != (const vertex_iterator& rhs) {
	return pos != rhs.pos;
      }
    };

    struct end_tag {};
    struct start_tag {};

    class edge_iterator {
    private:
      const Graph* thegraph;
      vertex_iterator vpos;
      std::set<vertex_descriptor>::iterator epos;
    public:
      edge_iterator(const Graph* g, start_tag) : thegraph(g), vpos(vertex_iterator(0)),
				       epos(thegraph->g[*vpos].begin()) {}
      edge_iterator(const Graph* g, end_tag) : thegraph(g),
				     vpos(vertex_iterator(thegraph->g.size() - 1)),
				     epos(thegraph->g[*vpos].end()) {}
      edge_iterator operator ++ () {
	if(epos == thegraph->g[*vpos].end()) {
	  vpos++;
	  epos = thegraph->g[*vpos].begin();
	}
	else {
	  epos++;
	}
	return *this;
      }

      edge_iterator operator ++ (int) {
	edge_iterator tmp = *this;
	++(*this);
	return tmp;
      }

      edge_descriptor operator * () {
	return edge_descriptor(*vpos, *epos);
      }

      bool operator != (const edge_iterator& rhs) {
	if(this == &rhs)
	  return false;
	else
	  return epos != rhs.epos || vpos != rhs.vpos ||
		 thegraph != rhs.thegraph;
      }
    };
      
    // --------
    // add_edge
    // --------

    /**
     * <your documentation>
     */
    friend std::pair<edge_descriptor, bool>
    add_edge (vertex_descriptor, vertex_descriptor, Graph&) {
      // <your code>
      edge_descriptor ed;
      bool            b;
      return std::make_pair(ed, b);
    }

    // ----------
    // add_vertex
    // ----------
        
    /**
     * <your documentation>
     */
    friend vertex_descriptor
    add_vertex (Graph&) {
      // <your code>

      vertex_descriptor v;
      return v;
    }
        
    // -----------------
    // adjacent_vertices
    // -----------------
        
    /**
     * <your documentation>
     */
    friend std::pair<adjacency_iterator, adjacency_iterator>
    adjacent_vertices (vertex_descriptor, const Graph&) {
      // <your code>
      adjacency_iterator b;
      adjacency_iterator e;
      return std::make_pair(b, e);
    }

    // ----
    // edge
    // ----
        
    /**
     * <your documentation>
     */
    friend std::pair<edge_descriptor, bool>
    edge (vertex_descriptor, vertex_descriptor, const Graph&) {
      // <your code>
      edge_descriptor ed;
      bool            b;
      return std::make_pair(ed, b);
    }

    // -----
    // edges
    // -----
        
    /**
     * O(1) in space
     * O(1) in time
     * <your documentation>
     */
    friend std::pair<edge_iterator, edge_iterator>
    edges (const Graph& mygraph) {
      edge_iterator b(&mygraph, start_tag());
      edge_iterator e(&mygraph, end_tag());
      return std::make_pair(b, e);
    }

    // ------
    // vertex
    // ------
        
    /**
     * <your documentation>
     */
    friend vertex_descriptor
    vertex (vertices_size_type, const Graph&) {
      // <your code>
      vertex_descriptor vd;
      return vd;
    }

    // --------
    // vertices
    // --------
        
    /**
     * <your documentation>
     */
    friend std::pair<vertex_iterator, vertex_iterator>
    vertices (const Graph& mygraph) {
      // <your code>
      vertex_iterator b(0);
      vertex_iterator e(mygraph.g.size() - 1);
      return std::make_pair(b, e);
    }

    // ------
    // source
    // ------
        
    /**
     * <your documentation>
     */
    friend vertex_descriptor
    source (edge_descriptor, const Graph&) {
      // <your code>
      vertex_descriptor v;
      return v;
    }

    // ------
    // target
    // ------
        
    /**
     * <your documentation>
     */
    friend vertex_descriptor
    target (edge_descriptor, const Graph&) {
      // <your code>
      vertex_descriptor v;
      return v;
    }

    // ---------
    // num_edges
    // ---------
        
    /**
     * <your documentation>
     */
    friend edges_size_type
    num_edges (const Graph&) {
      // <your code>
      edges_size_type s;
      return s;
    }

    // ------------
    // num_vertices
    // ------------
        
    /**
     * <your documentation>
     */
    friend vertices_size_type
    num_vertices (const Graph&) {
      // <your code>
      vertices_size_type s;
      return s;
    }

  private:
    // ----
    // data
    // ----

    friend class edge_iterator;    
    std::vector< std::set<vertex_descriptor> > g;

    // -----
    // valid
    // -----

    /**
     * <your documentation>
     */
    bool valid () const {
      // <your code>
      return true;
    }

  public:
    // ------------
    // constructors
    // ------------

    /**
     * <your documentation>
     */
    Graph () {
      // <your code>
      assert(valid());
    }

    // Default copy, destructor, and copy assignment
    // Graph  (const Graph<T>&);
    // ~Graph ();
    // Graph& operator = (const Graph&);
  };

} // cs

#endif // Graph_h
