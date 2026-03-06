#include "../2_Zestaw5/C/NEIGHBORgraph.h"
#include <limits>
// https://pl.wikipedia.org/wiki/Algorytm_Floyda-Warshalla
#define INF 10'000'000 // nieskonczonosc symbolicznie
using myTab = std::vector< std::vector<int> >;

std::pair< myTab, myTab > floydWarshall(ADTgraph& graf) {
    std::list<int> verticles = graf.getAllVertices();
    std::list<std::pair<int, int>> edges = graf.getAllEdges();
    myTab distance (verticles.size(), std::vector<int>(verticles.size()));
    myTab predecessor (verticles.size(), std::vector<int>(verticles.size()));
    for (int v1 : verticles) {
        for (int v2 : verticles) {
            distance[v1][v2] = INF; // Ustawiamy odległosc na nieskończonosc
            predecessor[v1][v2] = -1; // Ustawiamy poprzednika na niezdefiniowane
        }
    distance[v1][v1] = 0; // Odległosc do samego siebie to 0
    }
    for (std::pair<int, int> e : edges) {
        distance[e.first][e.second] = graf.getEdgeValue(e.first, e.second); // Ustawiamy wage krawędzi
        predecessor[e.first][e.second] = e.first; // Ustawiamy poprzednika na wierzcholek startowy
    }
    for (int u : verticles) {
        for (int v1 : verticles) {
            for (int v2 : verticles) {
                if (distance[v1][v2] > distance[v1][u] + distance[u][v2]) {
                    distance[v1][v2] = distance[v1][u] + distance[u][v2]; // Ustawiamy nową odległosc
                    predecessor[v1][v2] = predecessor[u][v2]; 
                }
            }
        }
    }
    return {distance, predecessor};
}