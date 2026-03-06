#include "../../2_Zestaw5/C/NEIGHBORgraph.h"

std::pair<std::map<int, int>, std::map<int, int>> calculateDistancesWithPaths(ADTgraph& graf, int startingVertex) {
    auto cmp = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second > b.second;
    };

    std::map<int, int> distances;
    std::map<int, int> previous;

    for (const auto& vertex : graf.getAllVertices()) {
        distances[vertex] = INT_MAX;
        previous[vertex] = -1; // -1 oznacza brak poprzednika
    }
    distances[startingVertex] = 0;

    std::priority_queue<
        std::pair<int, int>,
        std::vector<std::pair<int, int>>,
        std::function<bool(const std::pair<int, int>&, const std::pair<int, int>&)>
    > queue(cmp);

    queue.push({startingVertex, 0});

    while (!queue.empty()) {
        int currentVertex = queue.top().first;
        int currentDistance = queue.top().second;
        queue.pop();

        if (currentDistance > distances[currentVertex]) continue;

        for (int neighbor : graf.neighbors(currentVertex)) {
            int weight = graf.getEdgeValue(currentVertex, neighbor);
            int distance = currentDistance + weight;

            if (distance < distances[neighbor]) {
                distances[neighbor] = distance;
                previous[neighbor] = currentVertex;
                queue.push({neighbor, distance});
            }
        }
    }

    return {distances, previous};
}

void printPath(int start, int end, ADTgraph& graf) {
    std::map<int, int> previous = calculateDistancesWithPaths(graf, start).second;
    std::map<int, int> distances = calculateDistancesWithPaths(graf, start).first;
    std::vector<int> path;
    for (int at = end; at != -1; at = previous.at(at)) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    if (path.front() != start) {
        std::cout << "Brak ścieżki z " << graf.getVertexCaption(start)
                  << " do " << graf.getVertexCaption(end) << std::endl;
        return;
    }

    std::cout << "Najkrótsza ścieżka z " << graf.getVertexCaption(start)
              << " do " << graf.getVertexCaption(end) << ": ";
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << graf.getVertexCaption(path[i]);
        if (i + 1 < path.size()) std::cout << " -> ";
    }
    std::cout << " (dystans: " << distances[end] << ")" << std::endl;
    std::cout << std::endl;
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

    printPath(9, 4, graf);
    return 0;
}