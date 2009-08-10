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

    // a helper struct to call the edge_iterator constructor for beginning and the end

    struct end_tag {};
    struct start_tag {};

    /**
     * inner class to iterate through all the edges inside the graph class
     */
    class edge_iterator {
    private:
      const Graph* thegraph;
      vertex_iterator vpos;
      std::set<vertex_descriptor>::iterator epos;
      std::set<vertex_descriptor> empty_set; // if the graph is empty 
      // we need a dummy empty set
    public:
     //constructor for begin() of all the edges
      edge_iterator(const Graph* g, start_tag) : thegraph(g), vpos(vertex_iterator(0)) {
	if(!( thegraph->g.empty()) ) epos = thegraph->g[*vpos].begin();
	else epos = empty_set.begin();
      }
     //constructor for end() of all the edges
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

    // -----------
    // remove_adge
    // -----------

    /**
     * Removes the edge between u and v
     * @param u The start edge
     * @param v The end edge
     * @param myG the graph
     */
    friend void remove_edge
    (vertex_descriptor u, vertex_descriptor v, Graph& myG) {
      myG.g[u].erase(v);
    }

    // --------
    // add_edge
    // --------

    /**
     * time:O(1)
     * space: O(1)
     * adding a new edge between 2 vertices inside the graph
     * @return std::pair<edge_descriptor, bool>
     * bool = false, if the edge already exist inside the graph
     * will return the edge description of 2 vertices
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
     * time:O(1) amortized
     * space: adding 1 item, O(1)
     * adding a new vertex inside the graph
     * @return the new description of the vertex that was added to the graph
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
     * time:O(1) 
     * space:  O(1)
     * returning all the adjacent vertices of a vertex inside 
     * a graph
     * @return pair of adjacency iterator marking the beginning and the end
     * of all the adjacent vertices
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
     * time:O(1) 
     * space:  O(1)
     * checking whether there is an edge between 2 vertices.
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
     * @return, a pair of iterator to traverse through all the edges inside a graph
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
     * time:O(1) 
     * space:  O(1)
     * @param the order of the vertex according to the insertion time, the specific graph
     * @return the vertex which was inserted according to the insertion time
     */
    friend vertex_descriptor
    vertex (vertices_size_type n, const Graph& myG) {
      assert(n < myG.g.size());
      return static_cast<vertex_descriptor>(n);
    }

    // --------
    // vertices
    // --------
        
    /**
     * time:O(1) 
     * space:  O(1)
     * @return a pair of vertex iterator to iterates through all the vertices inside
     * a specific graph
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
     * time:O(1) 
     * space:  O(1)
     * returning the source vertex of an edge inside a graph
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
     * time:O(1) 
     * space:  O(1)
     * returning the target vertex of an edge inside a graph
     */
    friend vertex_descriptor
    target (edge_descriptor x, const Graph& myG) {
      return x.second;
    }

    // ---------
    // num_edges
    // ---------
        
    /**
     * time:O(1) 
     * space:  O(1)
     * @return number of all the edges of  a graph
     */
    friend edges_size_type
    num_edges (const Graph& myG) {
      edges_size_type num = 0;
      for(unsigned int i = 0; i< myG.g.size(); ++i) {
	num += myG.g[i].size();
      }
      return num;
    }

    // ------------
    // num_vertices
    // ------------
        
    /**
     * time:O(1) 
     * space:  O(1)
     * @return number of all the vertices of  a graph
     */
    friend vertices_size_type
    num_vertices (const Graph& myG) {
      return static_cast<vertices_size_type>(myG.g.size());
    }

  private:
    // ----
    // data
    // ----

    friend class edge_iterator;    //gives edge iterator access to this class 
    				   // private data
    std::vector< std::set<vertex_descriptor> > g;
    vertex_descriptor ind; //the end index of a graph
    // -----
    // valid
    // -----

    /**
     * Index always has to be equal to the vector's size
     */
    bool valid () const {
      return ind == g.size();
    }

  public:
    // ------------
    // constructors
    // ------------

    /**
     * Default constructor
     */
    Graph () {
      // let the default vector of set constructor to run
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
