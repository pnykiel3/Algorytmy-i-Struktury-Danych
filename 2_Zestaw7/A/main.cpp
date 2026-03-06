#include "../../2_Zestaw5/C/NEIGHBORgraph.h"


std::map<int, int> calculateDistances(ADTgraph& graf, int startingVertex) {

    //komparator do kolejki priorytetowej - wyrazenie lambda
    auto cmp = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second > b.second; // Porównanie dla kolejki priorytetowej
    };
    
    std::map<int, int> distances;
    for (const auto& vertex : graf.getAllVertices()) {
        distances[vertex] = INT_MAX; // Ustaw odległość na nieskończoność
    }
    distances[startingVertex] = 0; // Odległość do samego siebie to 0

    // Kolejka priorytetowa do przetwarzania wierzchołków, pair.first to id wierzchołka, pair.second to odległość
    std::priority_queue < 
    std::pair<int, int>, // 1. Typ przechowywanych elementów
    std::vector<std::pair<int, int>>, // 2. Typ kontenera wewnętrznego
    std::function<bool(const std::pair<int, int>&, const std::pair<int, int>&)> // 3. Typ komparatora
    > queue(cmp);// 4. Nazwa zmiennej i inicjalizacja komparatorem

    queue.push({startingVertex, 0}); // Dodajemy wierzchołek startowy do kolejki
    while (!queue.empty()) {
        int currentVertex = queue.top().first;
        int currentDistance = queue.top().second;
        queue.pop();

        if (currentDistance > distances[currentVertex]) {
            continue; // Jeśli odległość nie jest aktualna, pomijamy
        }

        std::list<int> neighbors = graf.neighbors(currentVertex);

        for (int neighbor : neighbors) {
            int weight = graf.getEdgeValue(currentVertex, neighbor);
            int distance = currentDistance + weight;

            if (distance < distances[neighbor]) {
                distances[neighbor] = distance;
                queue.push({neighbor, distance}); // Dodajemy sąsiada do kolejki
            }
        }

    }
    return distances;
}

void printDistances(const std::map<int, int>& distances, ADTgraph& graf) {
    std::cout << "Oto droga do reszty pomieszczeń:" << std::endl << "{";
    for (const auto& pair : distances) {
        if (pair.first != graf.size()) {
        std::cout << "'" << graf.getVertexCaption(pair.first) << "': " << pair.second << ", ";
        } else {
            std::cout << "'" << graf.getVertexCaption(pair.first) << "': " << pair.second;
        }
    }
    std::cout << "}" << std::endl;
}

void printDistanceTo(ADTgraph& graf, int Targetvertex) {
    for (int vertex : graf.getAllVertices() ) {
        std::map<int, int> distances = calculateDistances(graf, vertex);
        auto it = distances.find(Targetvertex);
        if (it != distances.end()) {
            std::cout << "Do pokoju " << graf.getVertexCaption(Targetvertex) << " z pokoju " << graf.getVertexCaption(vertex) << " trafisz pokonując dystans: " << it->second << std::endl;
        } else {
            std::cout << "Wierzchołek " << Targetvertex << " nie istnieje." << std::endl;
        }
    }
}




int main() {

    ADTgraph graf;
    graf.addVertex(1, "A");
    graf.addVertex(2, "B");
    graf.addVertex(3, "C");
    graf.addVertex(4, "D");
    graf.addVertex(5, "E");
    graf.addVertex(6, "F");
    graf.addVertex(7, "G");
    graf.addVertex(8, "H");
    graf.addVertex(9, "I");
    graf.addVertex(10, "J");

    graf.addUndirectedEdge(1, 2, 3);
    graf.addUndirectedEdge(2, 3, 2);
    graf.addUndirectedEdge(2, 4, 1);
    graf.addUndirectedEdge(3, 7, 2);
    graf.addUndirectedEdge(4, 5, 1);
    graf.addUndirectedEdge(5, 6, 1);
    graf.addUndirectedEdge(6, 7, 1);
    graf.addUndirectedEdge(7, 8, 1);
    graf.addUndirectedEdge(6, 8, 2);
    graf.addUndirectedEdge(8, 9, 2);
    graf.addUndirectedEdge(8, 10, 1);

    // mierze czas dojscia z kazdego pomieszczenia do klatki schodowej A (1)
    printDistanceTo(graf, 1);
    std::cout << std::endl << std::endl;
    // mierze czas dojscia z kazdego pomieszczenia do ubikacji (10)
    printDistanceTo(graf, 10);
    return 0;
}