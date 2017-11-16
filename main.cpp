#include <stdlib.h>
#include <iostream>
#include "AllPair.h"


Graph* gen_test_graph(int V){
	
	Graph * g = new Graph(V);
	
	// test dijskstra
	g->addEdge( 0, 1, 4);
	g->addEdge( 1, 0, 4);
    g->addEdge(0, 7, 8);
    g->addEdge(7, 0, 8);
    g->addEdge( 1, 2, 8);
    g->addEdge( 2,1, 8);
    g->addEdge( 1, 7, 11);
    g->addEdge( 7, 1, 11);
    g->addEdge( 2, 3, 7);
    g->addEdge( 3, 2, 7);
    g->addEdge( 2, 8, 2);
    g->addEdge( 8, 2, 2);
    g->addEdge( 2, 5, 4);
    g->addEdge( 5, 2, 4);
    g->addEdge( 3, 4, 9);
    g->addEdge( 4, 3, 9);
    g->addEdge( 3, 5, 14);
    g->addEdge( 5, 3, 14);
    g->addEdge( 4, 5, 10);
    g->addEdge( 5, 4, 10);
    g->addEdge( 5, 6, 2);
    g->addEdge( 6, 5, 2);
    g->addEdge( 6, 7, 1);
    g->addEdge( 7, 6, 1);
    g->addEdge( 6, 8, 6);
    g->addEdge( 8, 6, 6);
    g->addEdge( 7, 8, 7);
    g->addEdge( 8, 7, 7);
 
	return g;
}




int main(){
	int V = 9;
	int src = 0;
	
    Graph * g1 = gen_test_graph(V);
    std::cout << "INPUT :\n";
    printDistances(g1->adj_mat_);
	//runDijkstra(g, src);
    //runBellmanFord(g, src);
    runFloydWarshall(g1);
    
    Graph * g2 = gen_test_graph(V);
    runJhonsons(g2);

	delete g1, g2;
	return 0;
}

