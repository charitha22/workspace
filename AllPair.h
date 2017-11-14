#ifndef _ALLPAIRS_H_
#define _ALLPAIRS_H_
#include<vector>
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
    vector<int> idx_to_vertex; // idx to vertex mapping
    vector<HeapNode*> nodes;
    
    void swapNodes(HeapNode* a, HeapNode* b);
    void minHeapify(int index);
    bool isEmpty() {return filled_ == 0;}
    HeapNode* getMin();
    void decreaseKey(int vid, int dist);
    bool isInMinHeap(int vid);

};

#endif
