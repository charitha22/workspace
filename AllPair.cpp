#include "AllPair.h"
#include <vector>
#include <stdlib.h>
using namespace std;

Graph::Graph(int size){
    size_ = size;
    for(int i = 0; i<size; i++){
        AdjList* new_adjlist = new AdjList;
        vertices_.push_back(new_adjlist);
    }
}

void Graph::addEdge(int src, int dest, int weight ){
    ListNode* new_node = new ListNode(src, dest, weight);
    vertices_[src]->push_back(new_node);
}

void MinHeap::swapNodes(HeapNode* a, HeapNode* b){
    vector<HeapNode*>::iterator it1 = nodes.find(a);
    vector<HeapNode*>::iterator it2 = nodes.find(b);

    assert(it1!=nodes.end() && it2!=nodes.end() && "can not swap nodes");

    HeadNode* temp = *it1;
    *it1 = *it2;
    *it2 = temp;

}

void MinHeap::minHeapify(int index){
}

HeapNode* MinHeap::getMin(){
    return NULL;
}

void MinHeap::decreaseKey(int vid, int dist){
}

bool MinHeap::isInMinHeap(int vid){
    return false;
}
