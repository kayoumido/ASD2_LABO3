//
//  main.cpp
//  Labo3
//
//  Created by Olivier Cuisenaire on 18.11.14.
//
//

#include <cstdlib>
#include <iostream>
#include <ctime>

#include "TrainNetwork.h"
#include "MinimumSpanningTree.h"
#include "ShortestPath.h"

#include "EdgeWeightedGraph.h"
#include "EdgeWeightedDigraph.h"
#include "TrainDIGraphWrapperDuration.h"
#include "TrainDIGraphWrapperDistance.h"
#include "TrainGraphWrappePrice.h"

using namespace std;

// Calcule et affiche le plus court chemin de la ville depart a la ville arrivee
// en passant par le reseau ferroviaire tn. Le critere a optimiser est la distance.
void PlusCourtChemin(const string& depart, const string& arrivee, TrainNetwork& tn) {
    // Get the vertices for the `depart` and `arrivee`
    int vFrom   = (tn.cityIdx.find(depart))->second;
    int vTo     = (tn.cityIdx.find(arrivee))->second;

    // Use our DIGraphWrapper to calculate the shortest distance
    TrainDIGraphWrapperDistance tdgw(tn);

    // Use Dijkstra to get the shortest path from `depart` to `arrivee`
    DijkstraSP<TrainDIGraphWrapperDistance> dikstra(tdgw, vFrom);
    vector<WeightedDirectedEdge<double>> shortestPath = dikstra.PathTo(vTo);

    cout << "longueur = " << dikstra.DistanceTo(vTo) << " km" << endl;
    cout << "via ";

    // Display the shortest path from `depart` to `arrivee`
    // Display the origin
    // i.e. `depart`
    cout << depart << " -> ";

    // Display the path from the origin to the destination
    for(size_t  i = 1; i < shortestPath.size(); ++i){
        WeightedDirectedEdge<double> edge = shortestPath[i];

        cout << tn.cities[edge.From()].name << " -> ";
    }

    // Display the destination
    // i.e. `arrivee`
    cout << arrivee << endl;
    }

// Calcule et affiche le plus court chemin de la ville depart a la ville arrivee
// en passant par le reseau ferroviaire tn ayant une ville en travaux et donc
// inaccessible. Vous pouvez mettre un cout infini aux arcs ayant comme depart ou
// comme arrivee cette ville en travaux. Le critere a optimiser est la distance.
void PlusCourtCheminAvecTravaux(const string& depart, const string& arrivee, const string& gareEnTravaux, TrainNetwork& tn) {
    // fetch vertex index of each town (from, to)
    int vFrom = (tn.cityIdx.find(depart))->second;
    int vTo = (tn.cityIdx.find(arrivee))->second;
    int vUnderRenovation = (tn.cityIdx.find(gareEnTravaux))->second;

    // Use our DIGraphWrapper for Distance calcul with in parameter the vertex in Renovation
    TrainDIGraphWrapperDistance tdgw(tn, vUnderRenovation);

    // Dijkstra From -> To
    DijkstraSP<TrainDIGraphWrapperDistance> dikstra(tdgw, vFrom);
    vector<WeightedDirectedEdge<double>> shortestPath = dikstra.PathTo(vTo);

    cout << "longueur = " << dikstra.DistanceTo(vTo) << " km" << endl;
    cout << "via ";

    // Display Via -> To
    for(size_t  i = 0; i < shortestPath.size(); ++i){
        // Display only the From town
        WeightedDirectedEdge<double> edge = shortestPath[i];
        cout << tn.cities[edge.From()].name << " -> ";
        // Display the last town (To) at the end
        if(i == shortestPath.size() - 1) {
            cout << tn.cities[edge.To()].name;
        }
    }

    cout << endl;
}

// Calcule et affiche le plus rapide chemin de la ville depart a la ville arrivee via la ville "via"
// en passant par le reseau ferroviaire tn. Le critere a optimiser est le temps de parcours
void PlusRapideChemin(const string& depart, const string& arrivee, const string& via, TrainNetwork& tn) {
    // fetch vertex index of each town (from, via, to)
    int vFrom = (tn.cityIdx.find(depart))->second;
    int vVia = (tn.cityIdx.find(via))->second;
    int vTo = (tn.cityIdx.find(arrivee))->second;

    // Use our DIGraphWrapper for Duration calcul
    TrainDIGraphWrapperDuration tdgw(tn);

    // Dijkstra From -> Via
    DijkstraSP<TrainDIGraphWrapperDuration> dikstra(tdgw, vFrom);
    vector<WeightedDirectedEdge<double>> shortestPathFromVia = dikstra.PathTo(vVia);
    double durationFromVia = dikstra.DistanceTo(vVia);

    // Dijkstra Via -> To
    dikstra = DijkstraSP<TrainDIGraphWrapperDuration>(tdgw, vVia);
    vector<WeightedDirectedEdge<double>> shortestPathViaTo = dikstra.PathTo(vTo);
    double durationViaTo = dikstra.DistanceTo(vTo);

    cout << "Temps = " << durationFromVia + durationViaTo << " minutes" << endl;

    cout << "Via ";

    // Display From -> Via
    for(size_t  i = 0; i < shortestPathFromVia.size(); ++i){
        // Display only the From town
        WeightedDirectedEdge<double> edge = shortestPathFromVia[i];
        cout << tn.cities[edge.From()].name << " -> ";
    }
    // Display Via -> To
    for(size_t  i = 0; i < shortestPathViaTo.size(); ++i){
        // Display only the From town
        WeightedDirectedEdge<double> edge = shortestPathViaTo[i];
        cout << tn.cities[edge.From()].name << " -> ";
        // Display the last town (To) at the end
        if(i == shortestPathViaTo.size() - 1) {
            cout << tn.cities[edge.To()].name;
        }
    }

    cout << endl;

}

// Calcule et affiche le plus reseau a renover couvrant toutes les villes le moins cher.
// Le prix pour renover 1 km de chemin de fer est de :
// - 15 CHF par km pour les lignes ayant 4 voies
// - 10 CHF par km pour les lignes ayant 3 voies
// - 6 CHF par km pour les lignes ayant 2 voies
// - 3 CHF par km pour les lignes ayant 1 voie
void ReseauLeMoinsCher(TrainNetwork &tn) {
    TrainGraphWrappePrice tgwmst(tn);
    vector<WeightedEdge<double>> mst = MinimumSpanningTree<TrainGraphWrappePrice>::Kruskal(tgwmst);

    double totalPrice = 0;

    // Display every line
    for(WeightedEdge<double> p : mst) {
        cout << tn.cities[p.Either()].name << " - " << tn.cities[p.Other(p.Either())].name << " : " << p.Weight() << " MF" << endl;
        totalPrice += p.Weight();
    }

    // Display total cost
    cout << endl << "Cout total: " << totalPrice << " MF" << endl; // Should give 7959
}

// compare les algorithmes Dijkstra et BellmanFord pour calculer les plus courts chemins au
// sommet 0 dans le graphe defini par filename.
void testShortestPath(string filename)
{
    cout << "Testing " << filename << endl;
    
    bool ok = true;
    
    typedef EdgeWeightedDiGraph<double> Graph;
    Graph ewd(filename);
    
    clock_t startTime = clock();
    
    BellmanFordSP<Graph> referenceSP(ewd,0);
    
    cout << "Bellman-Ford: " << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
    startTime = clock();
    
    DijkstraSP<Graph> testSP(ewd,0);
    
    cout << "Dijkstra:     " << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
    
    for (int v=0; v<ewd.V(); ++v) {
        if (referenceSP.DistanceTo(v) != testSP.DistanceTo(v) ) {
            cout << "Oops: vertex" << v << " has " << referenceSP.DistanceTo(v) << " != " <<  testSP.DistanceTo(v) << endl;
            ok = false;
            break;
        }
    }
    
    if(ok) cout << " ... test succeeded " << endl << endl;
}


int main(int argc, const char * argv[]) {

    testShortestPath("tinyEWD.txt");
    testShortestPath("mediumEWD.txt");
    testShortestPath("1000EWD.txt");
    //testShortestPath("10000EWD.txt");

    TrainNetwork tn("reseau.txt");

    cout << "1. Chemin le plus court entre Geneve et Coire" << endl;
    PlusCourtChemin("Geneve", "Coire", tn);

    cout << endl;

    cout << "2. Chemin le plus court entre Geneve et Coire, avec la gare de Sion en travaux" << endl;
    PlusCourtCheminAvecTravaux("Geneve", "Coire", "Sion", tn);

    cout << endl;

    cout << "3. Chemin le plus rapide entre Geneve et Coire en passant par Brigue" << endl;
    PlusRapideChemin("Geneve", "Coire", "Brigue", tn);

    cout << endl;

    cout << "4. Chemin le plus rapide entre Lausanne et Zurich en passant par Bale" << endl;
    PlusRapideChemin("Lausanne", "Zurich", "Bale", tn);

    cout << endl;

    cout << "5. Quelles lignes doivent etre renovees ? Quel sera le cout de la renovation de ces lignes ?" << endl;
    ReseauLeMoinsCher(tn);

    return 0;
}

