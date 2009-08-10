// ------------------------------
// projects/c++/graph/TestGraph.h
// Copyright (C) 2009
// Glenn P. Downing
// ------------------------------

#ifndef TestGraph_h
#define TestGraph_h

// --------
// includes
// --------

#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair

#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE

#include "Graph.h"
#include "GraphAlgorithms.h"

// ---------
// TestGraph
// ---------

template <typename T>
struct TestGraph : CppUnit::TestFixture {
  // --------
  // typedefs
  // --------

  typedef T                                       graph_type;

  typedef typename graph_type::vertex_descriptor  vertex_descriptor;
  typedef typename graph_type::edge_descriptor    edge_descriptor;

  typedef typename graph_type::vertex_iterator    vertex_iterator;
  typedef typename graph_type::edge_iterator      edge_iterator;
  typedef typename graph_type::adjacency_iterator adjacency_iterator;

  typedef typename graph_type::vertices_size_type vertices_size_type;
  typedef typename graph_type::edges_size_type    edges_size_type;

  // -----
  // tests
  // -----

  graph_type g;

  vertex_descriptor vdA;
  vertex_descriptor vdB;
  vertex_descriptor vdC;
  vertex_descriptor vdD;
  vertex_descriptor vdE;
  vertex_descriptor vdF;
  vertex_descriptor vdG;
  vertex_descriptor vdH;

  edge_descriptor edAB;
  edge_descriptor edAC;
  edge_descriptor edAE;
  edge_descriptor edBD;
  edge_descriptor edBE;
  edge_descriptor edCD;
  edge_descriptor edDE;
  edge_descriptor edDF;
  edge_descriptor edFD;
  edge_descriptor edFH;
  edge_descriptor edGH;

  // -----
  // setUp
  // -----

  // directed, sparse, unweighted
  // possibly connected
  // possibly cyclic
  // Collins, 2nd, pg. 653
  void setUp () {
    vdA  = add_vertex(g);
    vdB  = add_vertex(g);
    vdC  = add_vertex(g);
    vdD  = add_vertex(g);
    vdE  = add_vertex(g);
    vdF  = add_vertex(g);
    vdG  = add_vertex(g);
    vdH  = add_vertex(g);
    edAB = add_edge(vdA, vdB, g).first;
    edAC = add_edge(vdA, vdC, g).first;
    edAE = add_edge(vdA, vdE, g).first;
    edBD = add_edge(vdB, vdD, g).first;
    edBE = add_edge(vdB, vdE, g).first;
    edCD = add_edge(vdC, vdD, g).first;
    edDE = add_edge(vdD, vdE, g).first;
    edDF = add_edge(vdD, vdF, g).first;
    edFD = add_edge(vdF, vdD, g).first;
    edFH = add_edge(vdF, vdH, g).first;
    edGH = add_edge(vdG, vdH, g).first;
  }

  // -------------
  // test_add_edge
  // -------------

  void test_add_edge1() {
    std::pair<edge_descriptor, bool> p = add_edge(vdA, vdB, g);
    CPPUNIT_ASSERT(p.first  == edAB);
    CPPUNIT_ASSERT(p.second == false);
  }

  void test_add_edge2() {
    std::pair<edge_descriptor, bool> p = add_edge(vdE, vdG, g);
    adjacency_iterator b = adjacent_vertices(vdE, g).first;
    adjacency_iterator e = adjacent_vertices(vdE, g).second;
    CPPUNIT_ASSERT(std::distance(b, e) == 1);
    CPPUNIT_ASSERT(*b == vdG);
    CPPUNIT_ASSERT(p.second == true);
    remove_edge(vdE, vdG, g);
  }

  // -----------
  // test_vertex
  // -----------

  void test_vertex1() {
    vertex_descriptor vd = vertex(0, g);
    CPPUNIT_ASSERT(vd == vdA);
  }

  void test_vertex2() {
    vertex_descriptor vd = vertex(1, g);
    CPPUNIT_ASSERT(vd == vdB);
  }

  void test_vertex3() {
    vertex_descriptor vd = vertex(2, g);
    CPPUNIT_ASSERT(vd == vdC);
  }

  void test_vertex4() {
    vertex_descriptor vd = vertex(3, g);
    CPPUNIT_ASSERT(vd == vdD);
  }

  void test_vertex5() {
    vertex_descriptor vd = vertex(4, g);
    CPPUNIT_ASSERT(vd == vdE);
  }

  void test_vertex6() {
    vertex_descriptor vd = vertex(5, g);
    CPPUNIT_ASSERT(vd == vdF);
  }

  void test_vertex7() {
    vertex_descriptor vd = vertex(6, g);
    CPPUNIT_ASSERT(vd == vdG);
  }

  void test_vertex8() {
    vertex_descriptor vd = vertex(7, g);
    CPPUNIT_ASSERT(vd == vdH);
  }

  // ---------
  // test_edge
  // ---------

  void test_edge1() {
    std::pair<edge_descriptor, bool> p = edge(vdA, vdB, g);
    CPPUNIT_ASSERT(p.first  == edAB);
    CPPUNIT_ASSERT(p.second == true);
  }

  void test_edge2() {
    std::pair<edge_descriptor, bool> p = edge(vdA, vdC, g);
    CPPUNIT_ASSERT(p.first  == edAC);
    CPPUNIT_ASSERT(p.second == true);
  }

  void test_edge3() {
    std::pair<edge_descriptor, bool> p = edge(vdA, vdE, g);
    CPPUNIT_ASSERT(p.first  == edAE);
    CPPUNIT_ASSERT(p.second == true);
  }

  void test_edge4() {
    std::pair<edge_descriptor, bool> p = edge(vdB, vdD, g);
    CPPUNIT_ASSERT(p.first  == edBD);
    CPPUNIT_ASSERT(p.second == true);
  }

  void test_edge5() {
    std::pair<edge_descriptor, bool> p = edge(vdB, vdE, g);
    CPPUNIT_ASSERT(p.first  == edBE);
    CPPUNIT_ASSERT(p.second == true);
  }

  void test_edge6() {
    std::pair<edge_descriptor, bool> p = edge(vdC, vdD, g);
    CPPUNIT_ASSERT(p.first  == edCD);
    CPPUNIT_ASSERT(p.second == true);
  }

  void test_edge7() {
    std::pair<edge_descriptor, bool> p = edge(vdD, vdE, g);
    CPPUNIT_ASSERT(p.first  == edDE);
    CPPUNIT_ASSERT(p.second == true);
  }

  void test_edge8() {
    std::pair<edge_descriptor, bool> p = edge(vdD, vdF, g);
    CPPUNIT_ASSERT(p.first  == edDF);
    CPPUNIT_ASSERT(p.second == true);
  }

  void test_edge9() {
    std::pair<edge_descriptor, bool> p = edge(vdF, vdD, g);
    CPPUNIT_ASSERT(p.first  == edFD);
    CPPUNIT_ASSERT(p.second == true);
  }

  void test_edge10() {
    std::pair<edge_descriptor, bool> p = edge(vdF, vdH, g);
    CPPUNIT_ASSERT(p.first  == edFH);
    CPPUNIT_ASSERT(p.second == true);
  }

  void test_edge11() {
    std::pair<edge_descriptor, bool> p = edge(vdG, vdH, g);
    CPPUNIT_ASSERT(p.first  == edGH);
    CPPUNIT_ASSERT(p.second == true);
  }

  void test_edge12() {
    std::pair<edge_descriptor, bool> p = edge(vdD, vdG, g);
    CPPUNIT_ASSERT(p.second == false);
  }

  // -----------------
  // test_num_vertices
  // -----------------

  void test_num_vertices() {
    vertices_size_type vs = num_vertices(g);
    CPPUNIT_ASSERT(vs == 8);
  }

  // --------------
  // test_num_edges
  // --------------

  void test_num_edges() {
    edges_size_type es = num_edges(g);
    CPPUNIT_ASSERT(es == 11);
  }

  // -----------
  // test_source
  // -----------

  void test_source1() {
    vertex_descriptor vd = source(edAB, g);
    CPPUNIT_ASSERT(vd == vdA);
  }

  void test_source2() {
    vertex_descriptor vd = source(edAC, g);
    CPPUNIT_ASSERT(vd == vdA);
  }

  void test_source3() {
    vertex_descriptor vd = source(edAE, g);
    CPPUNIT_ASSERT(vd == vdA);
  }

  void test_source4() {
    vertex_descriptor vd = source(edBD, g);
    CPPUNIT_ASSERT(vd == vdB);
  }

  void test_source5() {
    vertex_descriptor vd = source(edBE, g);
    CPPUNIT_ASSERT(vd == vdB);
  }

  void test_source6() {
    vertex_descriptor vd = source(edCD, g);
    CPPUNIT_ASSERT(vd == vdC);
  }

  void test_source7() {
    vertex_descriptor vd = source(edDE, g);
    CPPUNIT_ASSERT(vd == vdD);
  }

  void test_source8() {
    vertex_descriptor vd = source(edDF, g);
    CPPUNIT_ASSERT(vd == vdD);
  }

  void test_source9() {
    vertex_descriptor vd = source(edFD, g);
    CPPUNIT_ASSERT(vd == vdF);
  }

  void test_source10() {
    vertex_descriptor vd = source(edFH, g);
    CPPUNIT_ASSERT(vd == vdF);
  }

  void test_source11() {
    vertex_descriptor vd = source(edGH, g);
    CPPUNIT_ASSERT(vd == vdG);
  }

  // -----------
  // test_target
  // -----------

  void test_target1() {
    vertex_descriptor vd = target(edAB, g);
    CPPUNIT_ASSERT(vd == vdB);
  }

  void test_target2() {
    vertex_descriptor vd = target(edAC, g);
    CPPUNIT_ASSERT(vd == vdC);
  }

  void test_target3() {
    vertex_descriptor vd = target(edAE, g);
    CPPUNIT_ASSERT(vd == vdE);
  }

  void test_target4() {
    vertex_descriptor vd = target(edBD, g);
    CPPUNIT_ASSERT(vd == vdD);
  }

  void test_target5() {
    vertex_descriptor vd = target(edBE, g);
    CPPUNIT_ASSERT(vd == vdE);
  }

  void test_target6() {
    vertex_descriptor vd = target(edCD, g);
    CPPUNIT_ASSERT(vd == vdD);
  }

  void test_target7() {
    vertex_descriptor vd = target(edDE, g);
    CPPUNIT_ASSERT(vd == vdE);
  }

  void test_target8() {
    vertex_descriptor vd = target(edDF, g);
    CPPUNIT_ASSERT(vd == vdF);
  }

  void test_target9() {
    vertex_descriptor vd = target(edFD, g);
    CPPUNIT_ASSERT(vd == vdD);
  }

  void test_target10() {
    vertex_descriptor vd = target(edFH, g);
    CPPUNIT_ASSERT(vd == vdH);
  }

  void test_target11() {
    vertex_descriptor vd = target(edGH, g);
    CPPUNIT_ASSERT(vd == vdH);
  }


  // -------------
  // test_vertices
  // -------------

  void test_vertices () {
    std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    CPPUNIT_ASSERT(b != e);
    vertex_descriptor vd = *b;
    CPPUNIT_ASSERT(vd == vdA);
    ++b;
    vd = *b;
    CPPUNIT_ASSERT(vd == vdB);
  }

  // ----------
  // test_edges
  // ----------

  void test_edges () {
    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    CPPUNIT_ASSERT(b != e);
    edge_descriptor ed = *b;
    CPPUNIT_ASSERT(ed == edAB);
    ++b;
    ed = *b;
    CPPUNIT_ASSERT(ed == edAC);
  }

  // ----------------------
  // test_adjacent_vertices
  // ----------------------

  void test_adjacent_vertices () {
    std::pair<adjacency_iterator, adjacency_iterator>
      p = adjacent_vertices(vdA, g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    CPPUNIT_ASSERT(b != e);
    vertex_descriptor vd = *b;
    CPPUNIT_ASSERT(vd == vdB);
    ++b;
    vd = *b;
    CPPUNIT_ASSERT(vd == vdC);
  }

  // --------------
  // test_has_cycle
  // --------------

  void test_has_cycle1() {
    CPPUNIT_ASSERT(cs::has_cycle(g));
  }

  void test_has_cycle2() {
    remove_edge(vdD, vdF, g);
    CPPUNIT_ASSERT(!cs::has_cycle(g));
    edDF = add_edge(vdD, vdF, g).first;
  }

  // ---------------------
  // test_topological_sort
  // ---------------------

  void test_topological_sort () {
    std::ostringstream out;
    remove_edge(vdD, vdF, g);
    cs::topological_sort(g, std::ostream_iterator<vertex_descriptor>(out, " "));
    CPPUNIT_ASSERT(out.str() == "4 3 1 2 0 7 5 6 ");
    edDF = add_edge(vdD, vdF, g).first;
  }

  // -----
  // suite
  // -----

  CPPUNIT_TEST_SUITE(TestGraph);
  CPPUNIT_TEST(test_add_edge1);
  CPPUNIT_TEST(test_add_edge2);
  CPPUNIT_TEST(test_vertex1);
  CPPUNIT_TEST(test_vertex2);
  CPPUNIT_TEST(test_vertex3);
  CPPUNIT_TEST(test_vertex4);
  CPPUNIT_TEST(test_vertex5);
  CPPUNIT_TEST(test_vertex6);
  CPPUNIT_TEST(test_vertex7);
  CPPUNIT_TEST(test_vertex8);
  CPPUNIT_TEST(test_edge1);
  CPPUNIT_TEST(test_edge2);
  CPPUNIT_TEST(test_edge3);
  CPPUNIT_TEST(test_edge4);
  CPPUNIT_TEST(test_edge5);
  CPPUNIT_TEST(test_edge6);
  CPPUNIT_TEST(test_edge7);
  CPPUNIT_TEST(test_edge8);
  CPPUNIT_TEST(test_edge9);
  CPPUNIT_TEST(test_edge10);
  CPPUNIT_TEST(test_edge11);
  CPPUNIT_TEST(test_edge12);
  CPPUNIT_TEST(test_num_vertices);
  CPPUNIT_TEST(test_num_edges);
  CPPUNIT_TEST(test_source1);
  CPPUNIT_TEST(test_source2);
  CPPUNIT_TEST(test_source3);
  CPPUNIT_TEST(test_source4);
  CPPUNIT_TEST(test_source5);
  CPPUNIT_TEST(test_source6);
  CPPUNIT_TEST(test_source7);
  CPPUNIT_TEST(test_source8);
  CPPUNIT_TEST(test_source9);
  CPPUNIT_TEST(test_source10);
  CPPUNIT_TEST(test_source11);
  CPPUNIT_TEST(test_target1);
  CPPUNIT_TEST(test_target2);
  CPPUNIT_TEST(test_target3);
  CPPUNIT_TEST(test_target4);
  CPPUNIT_TEST(test_target5);
  CPPUNIT_TEST(test_target6);
  CPPUNIT_TEST(test_target7);
  CPPUNIT_TEST(test_target8);
  CPPUNIT_TEST(test_target9);
  CPPUNIT_TEST(test_target10);
  CPPUNIT_TEST(test_target11);
  CPPUNIT_TEST(test_vertices);
  CPPUNIT_TEST(test_edges);
  CPPUNIT_TEST(test_adjacent_vertices);
  CPPUNIT_TEST(test_has_cycle1);
  CPPUNIT_TEST(test_has_cycle2);
  CPPUNIT_TEST(test_topological_sort);
  CPPUNIT_TEST_SUITE_END();
};

#endif // TestGraph_h
