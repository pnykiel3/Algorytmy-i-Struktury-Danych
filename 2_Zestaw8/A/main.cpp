#include "../floydWarshall.h"


int main() {
    ADTgraph graf;

    std::ifstream dane("../czasy");
	std::string miastoA, miastoB;
	int czasPrzejazdu;
	while (dane >> miastoA >> miastoB >> czasPrzejazdu) {
        if (graf.findCaption(miastoA) == -1) {
        int idA = graf.size();
		graf.addVertex (idA, miastoA);
        // std::cout << "Dodano wierzcholek: " << idA << " " << miastoA << "\n";
        }
        if (graf.findCaption(miastoB) == -1) {
        int idB = graf.size();
		graf.addVertex (idB, miastoB);
        // std::cout << "Dodano wierzcholek: " << idB << " " << miastoB << "\n";
        }
		graf.addUndirectedEdge (graf.findCaption(miastoA), graf.findCaption(miastoB), czasPrzejazdu);
	}
	
	dane.close();
	std::ofstream result("result.txt");
    std::pair<myTab, myTab> fW = floydWarshall(graf);
    result << "Macierz odleglosci:\n";
    std::list<int> verticles = graf.getAllVertices();
    for (int vv : verticles) {
        result << graf.getVertexCaption(vv) << "\t";
    }
    for (int i = 1; i < graf.size(); ++i) {
        result << "\n" << graf.getVertexCaption(i) << "\t";
        for (int j = 1; j < graf.size(); ++j) {
            if (fW.first[i][j] == INF) {
                result << "INFINITY\t";
            } else {
                result << fW.first[i][j] << "\t";
            }
        }
        result << "\n";
    }
    result.close();
    

}