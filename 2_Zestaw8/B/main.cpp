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

    std::ifstream danePos("../positions");
    std::map <std::string, std::pair<double, double>> pozycje;
    std::string miasto;
    double x, y;
    while (danePos >> miasto >> x >> y) {
        pozycje.insert({miasto, {x, y}});
    }
    danePos.close();

    std::string filename = "graph";
    std::ofstream dotPlik(filename + ".txt");
    std::pair< myTab, myTab > distances = floydWarshall(graf);
    std::cout << "Podaj miasto startowe: ";
    std::string start;
    std::cin >> start;
    if ( graf.findCaption(start) == -1 ) {
        std::cout << "Nie ma takiego miasta w bazie danych!" << std::endl;
        return 0;
    }
    std::cout << "Podaj miasto docelowe: ";
    std::string end;
    std::cin >> end;
    if ( graf.findCaption(end) == -1 ) {
        std::cout << "Nie ma takiego miasta w bazie danych!" << std::endl;
        return 0;
    }

    std::list<std::string> sciezka;
    sciezka.push_front(end);
    while (sciezka.back() != start) {
        std::string a = graf.getVertexCaption( distances.second[graf.findCaption(start)][graf.findCaption(sciezka.back())]);
        sciezka.push_back(a);
    }

    dotPlik << "graph G {" << std::endl;
	std::string prev = "NULL";
	for (std::string node : sciezka) {
		dotPlik << node << " [pos=\"" << pozycje[node].second << "," << pozycje[node].first << "!\"];" << std::endl;
		if (prev != "NULL") {
			dotPlik << node << " -- " << prev << " [label=\"" << distances.first[graf.findCaption(node)][graf.findCaption(prev)] << "\"];" << std::endl;
		}
		prev = node;
	}
	dotPlik << "}";
    dotPlik.close();
	
	std::cout << "Trasa została zapisana do'" << std::endl;
    std::string cmd = "dot -Tpng " + filename + ".txt -o " + filename + ".jpg";
        system(cmd.c_str());

	
}
