#include "graph_coloring.hh"
#include <iostream>
#include <memory>



int main(int, char**) {
    Graph g1(5);
    g1.add_edge(0, 1); 
    g1.add_edge(0, 2); 
    g1.add_edge(1, 2); 
    g1.add_edge(1, 3); 
    g1.add_edge(2, 3); 
    g1.add_edge(3, 4); 

    Graph g2(5); 
    g2.add_edge(0, 1); 
    g2.add_edge(0, 2); 
    g2.add_edge(1, 2); 
    g2.add_edge(1, 4); 
    g2.add_edge(2, 4); 
    g2.add_edge(4, 3); 

    GraphColoring::ColorGraph(g1);
    std::cout << "Coloring for g1 \n";
    GraphColoring::PrintColoring(g1);

    GraphColoring::ColorGraph(g2);
    std::cout << "Coloring for g2 \n";
    GraphColoring::PrintColoring(g2);

    return 0;
}
