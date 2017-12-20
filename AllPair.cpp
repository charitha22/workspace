#include "AllPair.h"
#include <vector>
#include <cassert>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#define INT_MAX 999999
using namespace std;

Graph::Graph(int size){
    size_ = size;
    for(int i = 0; i<size; i++){
        AdjList* new_adjlist = new AdjList;
        vertices_.push_back(new_adjlist);
        
        vector<int> temp;
        for(int j=0; j<size; j++){
            if(i==j) {
                temp.push_back(0);
            }
            else{
                temp.push_back(INT_MAX);
            }
        }

        adj_mat_.push_back(temp);
    
    }
    
}

Graph::Graph(Graph* g){
	adj_mat_ = g->adj_mat_;
	vertices_ = g->vertices_;
	edges_ = g->edges_;
	size_ = g->size_;
}
void Graph::addEdge(int src, int dest, int weight ){
    ListNode* fwd_nd = new ListNode(src, dest, weight);
    vertices_[src]->push_back(fwd_nd);

	//ListNode* back_nd = new ListNode(dest, src, weight);
	//vertices_[dest]->push_back(back_nd);
    
    //update the adj matrix
    adj_mat_[src][dest] = weight;
    edges_.push_back(fwd_nd);
}

void MinHeap::swapNodes(int a, int b){


    HeapNode* temp = nodes[a];
    nodes[a] = nodes[b];
    nodes[b] = temp;

}

void MinHeap::minHeapify(int idx){
	int smallest = idx;
	int left = 2*idx+1;
	int right = 2*idx+2;

	if(left<filled_ && nodes[left]->dist_ < nodes[smallest]->dist_){
		smallest = left;
	}
	if(right<filled_ && nodes[right]->dist_ < nodes[smallest]->dist_){
		smallest = right;
	}

	if(smallest!=idx){
		HeapNode * small_nd = nodes[smallest];
		HeapNode * idx_nd = nodes[idx];

		vertex_to_idx[small_nd->vid_] = idx;
		vertex_to_idx[idx_nd->vid_] = smallest;

		swapNodes(smallest, idx);

		minHeapify(smallest);
	}
}

HeapNode* MinHeap::getMin(){
	if(isEmpty()){
    	return NULL;
	}
	
	HeapNode* root = nodes[0];
	HeapNode* last_nd = nodes[filled_-1];

	nodes[0] = last_nd;

	vertex_to_idx[root->vid_] = filled_-1;
	vertex_to_idx[last_nd->vid_] = 0;

	filled_--;

	minHeapify(0);

	return root;

}

void MinHeap::decreaseKey(int vid, int dist){

	int i = vertex_to_idx[vid];
	nodes[i]->dist_ = dist;

	while(i && nodes[i]->dist_ < nodes[(i-1)/2]->dist_){
		vertex_to_idx[nodes[i]->vid_] = (i-1)/2;
		vertex_to_idx[nodes[(i-1)/2]->vid_] = i;

		swapNodes(i, (i-1)/2);

		i = (i-1)/2;
	}
}

bool MinHeap::isInMinHeap(int vid){

	if(vertex_to_idx[vid] < filled_) return true;

	return false;
}

void printDistances(int * dist, int V){

	cout << "vertex		distance from source \n";

	for(int i =0; i<V; i++){
		std::cout  << i << "\t\t " << dist[i] << "\n";
	
	}



}

void printDistances(vector<vector<int>>& dist){

    int V = (int)dist.size();
    for(int i=0; i<V; i++){
        for(int j=0; j<V; j++){
            if(dist[i][j]==INT_MAX){
                std::cout << "INF\t" ;
            }
            else{
                std::cout << dist[i][j] << "\t";
            }
        }
        std::cout << "\n";
    }
}



void runDijkstra(Graph* g, int src){
	int V = g->size_;
	int dist[V];

	MinHeap heap(V);

	for(int i=0 ; i<V; i++){
		dist[i] = INT_MAX;
		HeapNode* nd = new HeapNode(i, dist[i]);
		heap.nodes.push_back(nd);
		heap.vertex_to_idx.push_back(i);
	}
	
	heap.nodes[src] = new HeapNode(src, dist[src]);
	heap.vertex_to_idx[src] = src;
	dist[src] = 0;
	heap.decreaseKey(src, dist[src]);

	heap.filled_ = V;

	while(!heap.isEmpty()){
		HeapNode* min_nd = heap.getMin();
		int u = min_nd->vid_;

		std::vector<ListNode*>::iterator it = g->vertices_[u]->begin();
		while(it!=g->vertices_[u]->end()){
			int v = (*it)->dest_;

			if(heap.isInMinHeap(v) && dist[u]!=INT_MAX && (*it)->weight_+dist[u] < dist[v]){
				dist[v] = dist[u] + (*it)->weight_;
				heap.decreaseKey(v, dist[v]);
			}

			it++;
		}
	
	}

    // store result
    vector<int> temp;
    for(int i=0; i<V; i++){
        temp.push_back(dist[i]);
    }

    g->dij_results_.insert(std::pair<int, vector<int>>(src, temp));

    //std::cout << "DIJKSTRA OUTPUT : \n"; 
	//printDistances(dist, V);



}

void runFloydWarshall(Graph* g){
    vector<vector<int>> dist = g->adj_mat_;

    for(int k=0;  k<g->size_; k++){
        for(int i=0; i<g->size_; i++){
            for(int j=0; j<g->size_; j++){
                if(dist[i][k]+dist[k][j]<dist[i][j]){
                    dist[i][j] = dist[i][k]+dist[k][j];
                }
            }
        }
    }
    
    //std::cout << "FLOYDWARSHALL OUTPUT : \n";
    //printDistances(dist);
}


bool runBellmanFord(Graph* g, int src){
    int V = g->size_;
    int dist[V];

    for(int i=0; i<V; i++){
        dist[i] = INT_MAX;
    }

    dist[src] = 0;

    for(int i=0; i<V-1; i++){
        
        for(unsigned int j=0; j<g->edges_.size(); j++){
            ListNode* e = g->edges_[j];
            int u = e->src_;
            int v = e->dest_;
            int w = e->weight_;
            if(dist[v]>dist[u]+w){
                dist[v] = dist[u] + w;
            }
        }
    }

    //std::cout << "BELLMANFORD OUTPUT : \n";
    //printDistances(dist, V);

        // check for negative cycles
    for(unsigned int i=0; i<g->edges_.size(); i++){
        ListNode* e = g->edges_[i];
        int u = e->src_;
        int v = e->dest_;
        int w = e->weight_;
        if(dist[v]>dist[u]+w){
            return false;
        }
    }
    
    // update results
    vector<int> result;
    for(int i=0; i<V; i++){
        result.push_back(dist[i]);
    }
    g->bford_results_.insert(std::pair<int, vector<int>>(src, result));
 

    return true;
}


void runJhonsons(Graph* gg){
        
	Graph* g = new Graph(gg);
    // create a new graph 
    Graph new_g(g->size_+1);
    int new_vid = g->size_;

    // add new edges
    for(unsigned int i=0; i>g->edges_.size(); i++){
        ListNode* e = g->edges_[i];
        new_g.addEdge(e->src_, e->dest_, e->weight_);
    }
    for(int i=0; i<g->size_; i++){
        new_g.addEdge(new_vid, i, 0);
    }

    if(!runBellmanFord(&new_g, new_vid)){
        std::cout << "graph contains negative weight cycles\n";
        return;
    }
    
    map<int, vector<int>>::iterator it = new_g.bford_results_.find(new_vid);
    assert(it!=new_g.bford_results_.end());

    vector<int> h_vec = it->second;
    assert(h_vec.size()==new_g.size_);


    vector<vector<int>> d = g->adj_mat_;

    for(unsigned int i=0; i<g->edges_.size(); i++){
        int u = g->edges_[i]->src_;
        int v = g->edges_[i]->dest_;
        g->edges_[i]->weight_ = g->edges_[i]->weight_ + h_vec[u] - h_vec[v];
    }

    for(int i=0; i<g->size_; i++){
        runDijkstra(g, i);
        vector<int> result = g->dij_results_[i];
        for(int j=0; j<g->size_; j++){
            d[i][j] = result[j] + h_vec[j]-h_vec[i];
        }
    }
    
    //std::cout << "JHONSONS OUTPUT : \n";
    //printDistances(d);
   


}


void runHybrid(Graph* g){
	
	int V = g->size_;
	int E = g->edges_.size();

	double ratio = (double)(E/(double)(V*(V-1)));
    //double fw_cost = (double)V*V*V;	
	//double jsn_cost = (double)V*E*log2((double)V);
    
	if(ratio<0.4){
		runJhonsons(g);
	}
	else{
		runFloydWarshall(g);
	}


}



