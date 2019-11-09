//
// Created by loic on 11/8/19.
//

#include "TrainDIGraphWrapperDuration.h"
#include "EdgeWeightedGraph.h"
#include <algorithm>

TrainDIGraphWrapperDuration::TrainDIGraphWrapperDuration(const TrainNetwork& tn):tn(tn){}

int TrainDIGraphWrapperDuration::V() const  {
    return (int)tn.cities.size();
}

template <typename Func>
void TrainDIGraphWrapperDuration::forEachEdge(Func func) const {
    for(size_t i = 0; i < tn.lines.size(); ++i) {
        WeightedEdge<int> e1(tn.lines[i].cities.first, tn.lines[i].cities.second, calculWeightTime(tn.lines[i]));
        WeightedEdge<int> e2(tn.lines[i].cities.second, tn.lines[i].cities.first, calculWeightTime(tn.lines[i]));
        func(e1);
        func(e2);
    }
}

template <typename Func>
void TrainDIGraphWrapperDuration::forEachAdjacentEdge(int vertex, Func func) const {
    size_t vertexCitiesLength = tn.cities[(size_t)vertex].lines.size();

    for(size_t i = 0; i < vertexCitiesLength; ++i) {
        int lineIndex = tn.cities[(size_t)vertex].lines[i];
        Line line = tn.lines[(size_t)lineIndex];
        WeightedEdge<int> e1(line.cities.first, line.cities.second, calculWeightTime(line));
        WeightedEdge<int> e2(line.cities.second, line.cities.first, calculWeightTime(line));
        func(e1);
        func(e2);
    }
}

int TrainDIGraphWrapperDuration::calculWeightTime(const Line& line) const {
    return line.duration;
}

