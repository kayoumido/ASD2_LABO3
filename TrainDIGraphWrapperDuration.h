//
// Created by loic on 11/8/19.
//

#ifndef LABO03_TRAINDIGRAPHWRAPPERDURATION_H
#define LABO03_TRAINDIGRAPHWRAPPERDURATION_H

#include "TrainNetwork.h"

class TrainDIGraphWrapperDuration {

    typedef TrainNetwork::Line Line;

private:
    const TrainNetwork& tn;

public :
    TrainDIGraphWrapperDuration(const TrainNetwork& tn);

    int V() const ;

    template <typename Func>
    void forEachEdge(Func func) const;

    template <typename Func>
    void forEachAdjacentEdge(int vertex, Func func) const;

private :
    int calculWeightTime(const Line& line) const;


};


#endif //LABO03_TRAINDIGRAPHWRAPPERDURATION_H
