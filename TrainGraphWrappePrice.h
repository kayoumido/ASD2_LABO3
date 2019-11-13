//
// Created by rdema on 12.11.2019.
//

#ifndef LABO03_TRAINGRAPHWRAPPEPRICE_H
#define LABO03_TRAINGRAPHWRAPPEPRICE_H

#include "TrainNetwork.h"
#include "EdgeWeightedGraph.h"

class TrainGraphWrappePrice {

    typedef TrainNetwork::Line Line;

private:
    const TrainNetwork& tn;

public :

    typedef WeightedEdge<double> Edge;

    TrainGraphWrappePrice(const TrainNetwork& tn) : tn(tn) {

    }

    int V() const {
        return (int)tn.cities.size();
    }

    template <typename Func>
    void forEachEdge(Func func) const {
        for(size_t i = 0; i < tn.lines.size(); ++i) {
            func(Edge(tn.lines[i].cities.first, tn.lines[i].cities.second, calculateLinePrice(tn.lines[i])));
        }
    }

    template <typename Func>
    void forEachAdjacentEdge(int vertex, Func func) const {
        for(size_t i = 0; i < tn.cities[(size_t)vertex].lines.size(); ++i) {
            int lineIndex = tn.cities[(size_t)vertex].lines[i];
            Line line = tn.lines[(size_t)lineIndex];
            func(Edge(line.cities.second, line.cities.first, calculateLinePrice(line)));
        }
    }

private :
    double calculateLinePrice(const Line& line) const {
        // Number of km is multiplied by the tracks cost
        double price = line.length;

        switch(line.nbTracks) {
            case 1:
                price *= 3;
                break;
            case 2:
                price *= 6;
                break;
            case 3:
                price *= 10;
                break;
            default: // 4 or more tracks
                price *= 15;
                break;
        }

        return price;
    }
};

#endif //LABO03_TRAINGRAPHWRAPPEPRICE_H