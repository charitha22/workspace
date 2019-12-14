#ifndef _GRAPH_COLORING_H_
#define _GRAPH_COLORING_H_
#include <iostream>
#include "graph.hh"

class GraphColoring {
public:
    static void ColorGraph(Graph& g){
        if(!g.get_num_vertices()) return;

        // set first color
        g.set_vertex_color(0, 0);
        int v = 1;

        // available colors
        bool avail[g.get_num_vertices()];
        for(int i = 0; i < g.get_num_vertices(); i++) avail[i] = true;

        for(;v < g.get_num_vertices(); v++){
            // traverse all neighbors
            Node* n = g.get_vertex(v);
            auto nit = n->neighbors.begin();
            for(; nit!=n->neighbors.end(); nit++){
                if((*nit)->color!=-1) avail[(*nit)->color] = false;
            }

            // find the lowset index color avilable
            int c = 0;
            for(; c<g.get_num_vertices(); c++){
                if(avail[c]) break;
            }
            // set the color for this node
            g.set_vertex_color(v, c);
            // reset colors
            for(int i = 0; i < g.get_num_vertices(); i++) avail[i] = true;

        }
    }  

    static void PrintColoring(Graph& g){
        for(int i = 0; i < g.get_num_vertices(); i++){
            std::cout << "vertex = " << i << 
                " , color = " << g.get_vertex_color(i) << std::endl;
        }
    }
};

#endif