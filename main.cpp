#include <stdlib.h>
#include <iostream>
#include "AllPair.h"
#include <chrono>
#include <random>
using namespace std;
using namespace std::chrono;

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

void run_test(){
	int V = 9;
	int src = 0;

    Graph * g1 = gen_test_graph(V);
    std::cout << "INPUT :\n";
    printDistances(g1->adj_mat_);
	//runDijkstra(g, src);
    //runBellmanFord(g, src);
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    runFloydWarshall(g1);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
   
    auto fw_time = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Time for floyd warshall : " << fw_time << " us\n";

    Graph * g2 = gen_test_graph(V);
    high_resolution_clock::time_point t3 = high_resolution_clock::now();
    runJhonsons(g2);
    high_resolution_clock::time_point t4 = high_resolution_clock::now();
    
    auto j_time = duration_cast<microseconds>( t4 - t3 ).count();
    cout << "Time for jhonsons : " <<  j_time << " us\n";


	delete g1, g2;


}

Graph* gen_random_graph(int V, double ratio){
	
	unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed1);
	std::uniform_int_distribution<int> distribution(1,1000);

	Graph * new_g = new Graph(V);
	for(int i =0; i<V; i++){
		for(int j=0; j<V; j++){
			if(i==j) continue;
			
			int rnum = distribution(generator);
			double prob = (double)rnum/1000;

			// add edge 
			if(prob<=ratio){
				int w = distribution(generator);
				new_g->addEdge(i, j, w);
			}


		}
	}


	cout << "no of vertices = " << new_g->size_ << "\n";
	cout << "no of edges = " << new_g->edges_.size() << "\n";
	
	return new_g;



}

int main(){
	//run_test();
	
	
	Graph* g = gen_random_graph(100, 0.3);
	//Graph* g = gen_test_graph(9);
    //std::cout << "INPUT :\n";
    //printDistances(g->adj_mat_);
    
    int E = g->edges_.size();
    int V = g->size_;
    double EEmax_ratio = (double)(E)/ (double)(V*(V-1));
    cout << "|E|/|E_max| = " << EEmax_ratio << "\n";

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
    runFloydWarshall(g);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
   
    auto fw_time = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Time for floyd warshall : " << fw_time << " us\n";

	high_resolution_clock::time_point t3 = high_resolution_clock::now();
    runJhonsons(g);
    high_resolution_clock::time_point t4 = high_resolution_clock::now();
   
    auto j_time = duration_cast<microseconds>( t4 - t3 ).count();
    cout << "Time for Jhonson : " << j_time << " us\n";
	
	high_resolution_clock::time_point t5 = high_resolution_clock::now();
    runHybrid(g);
    high_resolution_clock::time_point t6 = high_resolution_clock::now();
   
    auto h_time = duration_cast<microseconds>( t6 - t5 ).count();
    cout << "Time for Hybrid : " << h_time << " us\n";


	return 0;
}

