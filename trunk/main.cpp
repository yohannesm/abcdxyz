// ---------------------------
// projects/c++/graph/main.c++
// Copyright (C) 2009
// Glenn P. Downing
// ---------------------------

/*
To run the program:
    g++ -ansi -pedantic -I/public/linux/include/boost-1_38 -lcppunit -ldl -Wall main.c++ -o main.app
    valgrind main.app

To configure Doxygen:
    doxygen -g
That creates the file Doxyfile.
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    doxygen Doxyfile
*/

// --------
// includes
// --------

#include <iostream> // cout, endl

#include "boost/graph/adjacency_list.hpp" // adjacency_list

#include "cppunit/TestSuite.h"      // TestSuite
#include "cppunit/TextTestRunner.h" // TestRunner

#include "Graph.h"
#include "TestGraph.h"

// ----
// main
// ----

int main () {
    using namespace std;
    using namespace boost;

    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    // ----------
    // unit tests
    // ----------

    CppUnit::TextTestRunner tr;
    tr.addTest(TestGraph< adjacency_list<setS, vecS, directedS> >::suite());
    tr.addTest(TestGraph<cs::Graph>::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
