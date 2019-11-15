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

    /**
     * Constructor
     * @param tn THe Train network
     */
    TrainGraphWrappePrice(const TrainNetwork& tn) : tn(tn) {}

    /**
     * Return the number of vertex
     * @return The number of vertex (cities)
     */
    int V() const {
        return (int)tn.cities.size();
    }

    /**
     * Loop through all edges (lines) and apply a specific function passed in parameter on all of them.
     * @details We do not stock a concrete Graph, so we generate on the fly all edges and calculate the edge
     * weight with a specific weigthCalcul function
     * @param Func The function we have to apply on all edges
     */
    template <typename Func>
    void forEachEdge(Func func) const {
        for(size_t i = 0; i < tn.lines.size(); ++i) {
            // Create on the fly the edge (non oriented) calcul its weight and apply the specific function on it
            func(Edge(tn.lines[i].cities.first, tn.lines[i].cities.second, calculateLinePrice(tn.lines[i])));
        }
    }

    /**
     * Loop through all adjacent edge of a specific vertex and apply a specific function passed in parameter on all of them.
     * @details We do not stock a concrete Graph, so we generate on the fly all edges and calculate the edge
     * weight with a specific weigthCalcul function
     * @param vertex The vertex for which we want its adjacent edges
     * @param func The function we have to apply on all edges
     */
    template <typename Func>
    void forEachAdjacentEdge(int vertex, Func func) const {
        // Loop through all adjacent
        for(size_t i = 0; i < tn.cities[(size_t)vertex].lines.size(); ++i) {
            int lineIndex = tn.cities[(size_t)vertex].lines[i];
            // create on the fly the edge (non oriented) calcul its weight and apply the specific function on it
            Line line = tn.lines[(size_t)lineIndex];
            func(Edge(line.cities.second, line.cities.first, calculateLinePrice(line)));
        }
    }

private :

    /**
     * Specific weight calcul for an edge. This is the price of renovation in millions swiss francs for one edge
     * (composed of one or more tracks)
     * @param line The current edge as a Line
     * @return The weight of the edge in parameter
     */
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