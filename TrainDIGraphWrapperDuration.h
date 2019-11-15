/*
 * File:   TrainDiGraphWrapperDuration
 * Author: Loïc Dessaules, Doran Kayoumi, Robin Demarta
 *
 * Created on 15. November 2019, 14:58
 */

#ifndef LABO03_TRAINDIGRAPHWRAPPERDURATION_H
#define LABO03_TRAINDIGRAPHWRAPPERDURATION_H

#include "TrainNetwork.h"
#include "EdgeWeightedDigraph.h"

class TrainDIGraphWrapperDuration {

    typedef TrainNetwork::Line Line;

private:
    const TrainNetwork& tn;

public :

    typedef WeightedDirectedEdge<double> Edge;

    /**
     * Constructor
     * @param tn The TrainNetwork
     */
    TrainDIGraphWrapperDuration(const TrainNetwork& tn) : tn(tn) {}

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
            // Create on the fly the two edges because the wrapper is for oriented graph, one for each side
            Edge e1(tn.lines[i].cities.first, tn.lines[i].cities.second, calculWeightTime(tn.lines[i]));
            Edge e2(tn.lines[i].cities.second, tn.lines[i].cities.first, calculWeightTime(tn.lines[i]));

            // Apply the function in parameter on our edges
            func(e1);
            func(e2);
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
        // Nb of adjacent for a specific vertex
        size_t adjacentSize = tn.cities[(size_t)vertex].lines.size();

        for(size_t i = 0; i < adjacentSize; ++i) {
            // Fetch the line
            int lineIndex = tn.cities[(size_t)vertex].lines[i];
            Line line = tn.lines[(size_t)lineIndex];

            // We are in an oriented version, we create on the fly the right oriented edge with the good weight and
            // apply the specific function on it
            if(line.cities.first == vertex) {
                Edge e1(line.cities.first, line.cities.second, calculWeightTime(line));
                func(e1);
            }else{
                Edge e2(line.cities.second, line.cities.first, calculWeightTime(line));
                func(e2);
            }
        }
    }

private :

    /**
     * Specific weight calcul for an edge. This is the duration in minutes
     * @param line The current edge as a Line
     * @return The weight for the edge in parameter
     */
    double calculWeightTime(const Line& line) const {
        return line.duration;
    }


};


#endif //LABO03_TRAINDIGRAPHWRAPPERDURATION_H
