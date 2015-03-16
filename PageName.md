# Our mimic of Boost Graph library called CS::Graph #

We are going to reverse engineer part of the boost graph library for a school project.


# Implementation #

We are going to mimic a representation of a directed graph using adjacency list. We are using an std::vector of std::set to represent our graph.

Meta information provided by our CS::class:
  1. vertex\_descriptor = describing a vertex inside the graph
  1. edge\_descriptor = describing and edge between 2 vertices
  1. vertex\_iterator
  1. edge\_iterator
  1. adjacency\_iterator
  1. vertices\_size\_type
  1. edges\_size\_type

We have an add\_edge function to add an edge between 2 vertices.  We added a remove\_edge function to temporarily remove edges from the graph so that we can avoid infinite recursion in topological\_sort (without breaking the other test cases).

The graph that will be represented is assumed to be sparse because on how we are using an adjacency list to represent it. The graph also will be directed an we don't allow a multigraph representation using our class.

## Algorithms ##

Our has\_cycle function is tree recursive and uses three "colors."  Every vertex that has been partially visited already is colored grey, while those that have had all the children visited are colored black.  We recurse over all the adjacent vertices.  If we see a black vertex, we know that it can't have a cycle in that branch of the graph, so its return value is true.  If, however, we come across a grey vertex, then we have in fact visited that node already and we know that that branch of the graph has a cycle.  If any single recursive call returns true (signifying that the branch has a cycle), then we return true to indicate the whole graph has a cycle.

topological\_sort is similar to has\_cycle, but it only uses two colors.  Black indicates a vertex we've already added to the output.  We recurse over all the vertices in the graph.  When we reach a node without children, we color it black and add the vertex to the output.  When we reach a node that's either black or has all black children, we also add that vertex to the output.