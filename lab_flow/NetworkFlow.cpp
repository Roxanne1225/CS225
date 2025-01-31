/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
  flow_ = g_;
  residual_ = g_;
  maxFlow_ = 0;
  for (const Edge & e: residual_.getEdges()) {
    residual_.insertEdge(e.dest,e.source);
    residual_.setEdgeWeight(e.dest,e.source,0);
    //residual_.setEdgeLabel(e.dest,e.source."back");
  }
  for (const Edge & e: flow_.getEdges()) {
    flow_.setEdgeWeight(e.source, e.dest,0);
  }
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink,
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  int min = residual_.getEdgeWeight(path[0],path[1]);
  for (unsigned long int i = 1; i < path.size() - 1; i++) {
    if (min > residual_.getEdgeWeight(path[i],path[i+1])) {
      min = residual_.getEdgeWeight(path[i],path[i+1]);
    }
  }
  return min;
  return 0;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE
  vector<Vertex> myPath;
  while (findAugmentingPath(source_,sink_,myPath)) {
    int cap = pathCapacity(myPath);
    if (cap == 0) {
      break;
    }
    maxFlow_ += cap;
    for (size_t i = 0 ; i < myPath.size() - 1; i++) {
        residual_.setEdgeWeight(myPath[i],myPath[i+1],residual_.getEdgeWeight(myPath[i],myPath[i+1]) - cap);
        residual_.setEdgeWeight(myPath[i+1],myPath[i],residual_.getEdgeWeight(myPath[i+1],myPath[i]) + cap);
        if (flow_.edgeExists(myPath[i],myPath[i+1])) {
          flow_.setEdgeWeight(myPath[i],myPath[i+1],flow_.getEdgeWeight(myPath[i],myPath[i+1])+cap);
        } else {
            flow_.setEdgeWeight(myPath[i + 1],myPath[i],flow_.getEdgeWeight(myPath[i + 1],myPath[i])-cap);
        }
    }
  }
  return flow_;
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}
