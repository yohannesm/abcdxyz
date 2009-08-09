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
     * a simple class to iterate through vertex
     * because we have a vector of set, we need a separate iterator for the 
     * index which represent the vertex
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

    /*
     *a helper struct to call the edge_iterator constructor for beginning and the end
     */

    struct end_tag {};
    struct start_tag {};

    /*
     *inner class to iterate through all the edges inside the graph class
     *
     */

    class edge_iterator {
    private:
      const Graph* thegraph;
      vertex_iterator vpos;
      std::set<vertex_descriptor>::iterator epos;
      std::set<vertex_descriptor> empty_set; // if the graph is empty 
      // we need a dummy empty set
    public:
      edge_iterator(const Graph* g, start_tag) : thegraph(g), vpos(vertex_iterator(0)) {
	if(!( thegraph->g.empty()) ) epos = thegraph->g[*vpos].begin();
	else epos = empty_set.begin();
      }
      edge_iterator(const Graph* g, end_tag) : thegraph(g),
					       vpos(vertex_iterator(thegraph->g.size() - 1)) {     
	if(!( thegraph->g.empty()) ) epos = thegraph->g[*vpos].end();
	else epos = empty_set.end();
      }
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
    }; // end edge iterator
      
    // --------
    // add_edge
    // --------

    /**
     * <your documentation>
     */
    friend std::pair<edge_descriptor, bool>
    add_edge (vertex_descriptor x, vertex_descriptor y, Graph& myG) {
      bool            b = myG.g[x].insert(y).second;
      edge_descriptor ed(x,y);// = std::make_pair(a,b);
      return std::make_pair(ed, b);
    }

    // ----------
    // add_vertex
    // ----------
        
    /**
     * <your documentation>
     */
    friend vertex_descriptor
    add_vertex (Graph& myG) {
      myG.g.push_back( std::set<vertex_descriptor>() );
      return myG.ind++;
    }
        
    // -----------------
    // adjacent_vertices
    // -----------------
        
    /**
     * <your documentation>
     */
    friend std::pair<adjacency_iterator, adjacency_iterator>
    adjacent_vertices (vertex_descriptor x, const Graph& myG) {
      adjacency_iterator b = myG.g[x].begin();
      adjacency_iterator e = myG.g[x].end();
      return std::make_pair(b, e);
    }

    // ----
    // edge
    // ----
        
    /**
     * <your documentation>
     */
    friend std::pair<edge_descriptor, bool>
    edge (vertex_descriptor x, vertex_descriptor y, const Graph& myG) {
      assert(x < (myG.ind - 1));
      bool            b = myG.g[x].count(y);
      edge_descriptor ed(x, y);
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
    vertex (vertices_size_type n, const Graph& myG) {
      assert(n < (myG.ind - 1));
      return static_cast<vertex_descriptor>(n);
    }

    // --------
    // vertices
    // --------
        
    /**
     * <your documentation>
     */
    friend std::pair<vertex_iterator, vertex_iterator>
    vertices (const Graph& mygraph) {
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
    source (edge_descriptor x, const Graph& myG) {
      assert(x.first < myG.g.size() );
      return x.first;
    }

    // ------
    // target
    // ------
        
    /**
     * <your documentation>
     */
    friend vertex_descriptor
    target (edge_descriptor x, const Graph& myG) {
      return x.second;
    }

    // ---------
    // num_edges
    // ---------
        
    /**
     * <your documentation>
     */
    friend edges_size_type
    num_edges (const Graph& myG) {
      edges_size_type num;
      for(unsigned int i=0; i< myG.g.size(); ++i) {
	num += myG.g[i].size();
      }
      return num;
    }

    // ------------
    // num_vertices
    // ------------
        
    /**
     * <your documentation>
     */
    friend vertices_size_type
    num_vertices (const Graph& myG) {
      return  static_cast<vertices_size_type>(myG.g.size());
    }

  private:
    // ----
    // data
    // ----

    friend class edge_iterator;    
    std::vector< std::set<vertex_descriptor> > g;
    vertex_descriptor ind;
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
      ind = 0;
      assert(valid());
    }

    // Default copy, destructor, and copy assignment
    // Graph  (const Graph<T>&);
    // ~Graph ();
    // Graph& operator = (const Graph&);
  };

} // cs

#endif // Graph_h
