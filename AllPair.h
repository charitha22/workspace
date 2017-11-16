#ifndef _ALLPAIRS_H_
#define _ALLPAIRS_H_
#include<vector>
#include<map>
using namespace std;

class ListNode{
public:
    ListNode(int src, int dest, int weight) : src_(src), dest_(dest), weight_(weight) {;}
    int src_;
    int dest_;
    int weight_;
} ;

typedef std::vector<ListNode*> AdjList; 

class Graph{
public:
    Graph(int size);
    int size_; // size of graph
    vector<AdjList*> vertices_; // adjacency list for each vertice
    vector<ListNode*> edges_;
    vector<vector<int>> adj_mat_;
    
    map<int, vector<int>> bford_results_;
    map<int, vector<int>> dij_results_;
    void addEdge(int src, int dest, int weight);
};

class HeapNode{
public:    
    HeapNode(int vid, int dist) : vid_(vid), dist_(dist) {;}
    int vid_; //vertex id
    int dist_;
};  

class MinHeap{
public :
    MinHeap(int size) : size_(size) { filled_ = 0;}
    int filled_;
    int size_;
    vector<int> vertex_to_idx; // vertex to idx mapping
    vector<HeapNode*> nodes;
    
    void swapNodes(int a, int b);
    void minHeapify(int idx);
    bool isEmpty() {return filled_ == 0;}
    HeapNode* getMin();
    void decreaseKey(int vid, int dist);
    bool isInMinHeap(int vid);

};

void runDijkstra(Graph* g, int src);
bool runBellmanFord(Graph* g, int src);
void printDistances(int* dist, int V);
void printDistances(vector<vector<int>>& dist);
void runFloydWarshall(Graph* g);
void runJhonsons(Graph* g);
#endif
