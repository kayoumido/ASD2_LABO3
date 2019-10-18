cmake_minimum_required(VERSION 3.14)
project(Labo03)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wconversion -Wextra -pedantic")
add_executable(Labo03 main.cpp EdgeWeightedGraph.h EdgeWeightedDigraph.h EdgeWeightedGraphCommon.h MinimumSpanningTree.h ShortestPath.h TrainNetwork.cpp TrainNetwork.h UnionFind.cpp UnionFind.h Util.cpp Util.h)