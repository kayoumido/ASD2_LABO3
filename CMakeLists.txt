cmake_minimum_required(VERSION 3.15)
project(Labo03)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Labo03
        EdgeWeightedDigraph.h
        EdgeWeightedGraph.h
        EdgeWeightedGraphCommon.h
        main.cpp
        MinimumSpanningTree.h
        ShortestPath.h
        TrainNetwork.cpp
        TrainNetwork.h
        UnionFind.cpp
        UnionFind.h
        Util.cpp
        Util.h)
