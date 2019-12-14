#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <list>
#include <vector>

struct Node {
  std::vector<Node*> neighbors;
  int color;
};

class Graph {
private:
  std::vector<Node*> vertices; 
  int num_vertices;
public:
  Graph(int V)  : num_vertices(V) { 
       for(int i=0; i<V; i++){
         Node* n = new Node;
         n->color = -1;
         vertices.push_back(n);
       }
  }
  ~Graph() {
      for(auto n : vertices) delete n;
  }

  void add_edge(int n1, int n2){
    vertices[n1]->neighbors.push_back(vertices[n2]);
    vertices[n2]->neighbors. push_back(vertices[n1]);
  }

  int get_num_vertices() {
    return num_vertices;
  }
  
  void set_vertex_color(int vertex, int color) {
    vertices[vertex]->color = color;
  }

  int get_vertex_color(int vertex) {
    return vertices[vertex]->color;
  }

  Node* get_vertex(int vertex) {
    return vertices[vertex];
  }
  

};


#endif 