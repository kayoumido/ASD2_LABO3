//
// Created by loic on 11/8/19.
//

#ifndef LABO03_TRAINDIGRAPHWRAPPERDISTANCE_H
#define LABO03_TRAINDIGRAPHWRAPPERDISTANCE_H

#include "TrainNetwork.h"
#include "EdgeWeightedDigraph.h"

class TrainDIGraphWrapperDistance {

    typedef TrainNetwork::Line Line;

private:
    const TrainNetwork& tn;

public :

    typedef WeightedDirectedEdge<double> Edge;

    TrainDIGraphWrapperDistance(const TrainNetwork& tn) : tn(tn) {

    }

    int V() const {
        return (int)tn.cities.size();
    }

    template <typename Func>
    void forEachEdge(Func func) const {
        for(size_t i = 0; i < tn.lines.size(); ++i) {
            Edge e1(tn.lines[i].cities.first, tn.lines[i].cities.second, calculWeightDistance(tn.lines[i]));
            Edge e2(tn.lines[i].cities.second, tn.lines[i].cities.first, calculWeightDistance(tn.lines[i]));
            func(e1);
            func(e2);
        }
    }

    template <typename Func>
    void forEachAdjacentEdge(int vertex, Func func) const {
        size_t vertexCitiesLength = tn.cities[(size_t)vertex].lines.size();

        for(size_t i = 0; i < vertexCitiesLength; ++i) {
            int lineIndex = tn.cities[(size_t)vertex].lines[i];
            Line line = tn.lines[(size_t)lineIndex];
            // From first to Second
            if(line.cities.first == vertex) {
                Edge e1(line.cities.first, line.cities.second, calculWeightDistance(line));
                func(e1);
            }
                // Form second to First
            else{
                Edge e2(line.cities.second, line.cities.first, calculWeightDistance(line));
                func(e2);
            }
        }
    }

private :
    double calculWeightDistance(const Line& line) const {
        return line.length;
    }


};


#endif //LABO03_TRAINDIGRAPHWRAPPERDURATION_H
