#ifndef __KD_TREE__
#define __KD_TRRR__

#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>    // std::for_each
#include <iostream>

// T is the data type and N is the dimension of the point
template <class T, size_t N>
class point {
public:    
    point(std::vector<T>& data)  {
        for(int i = 0; i < N; i++){
            pt[i] = data[i];
        }
    }

    // copy constructor
    point(const point<T,N>& p){
        for(int i = 0; i < N; i++){
            pt[i] = p.get_value_at_dim(i);
        }
    }

    // eqaulity operator
    bool operator==(const point<T,N>& p){
        for(int i = 0; i < N; i++){
            if ( pt[i] != p.get_value_at_dim(i)) return false;
        }
        return true;
    }

    T get_value_at_dim(int dim) const {return pt[dim];}
    friend std::ostream& operator<<(std::ostream& os, const point& p){
        os << "(" << p.pt[0];
        for(int i=1; i<N; i++) os << ", " << p.pt[i];
        os << ")";
        return os;
    }

private :
    T pt[N];
};


template <class T, size_t N>
struct kd_tree_node {
public:
    kd_tree_node(const point<T,N>& p) 
        :  data(p), left(nullptr), right(nullptr) {}

    kd_tree_node<T,N>* left;
    kd_tree_node<T,N>* right;

    point<T, N> data;

    // do a pre-order print of node values
    friend std::ostream& operator<<(std::ostream& os, const kd_tree_node<T,N>& nd){
        os << nd.data;
        if(nd.left) os << " " << *nd.left;
        if(nd.right) os << " " << *nd.right; 
        return os;
    }

};

template <class T, size_t N>
class kd_tree {
public:
    // construct a kd-tree with a set of points
    // points are sequentilly added
    kd_tree(const std::vector<point<T, N>>& points){
        
        for(auto p : points){
            if(!root){
                root = new kd_tree_node<T,N>(p);
                continue;
            }
            insert_point(root, p, 0);
        }
    }

    kd_tree_node<T,N>* get_root() {return root;}

    // search for a point in the tree
    bool search_point (const point<T,N>& p) {
        return search_node(root, p, 0);
    } 

    // add a neew point to the tree
    void add_point(const point<T,N>& p){
        insert_point(root, p, 0);
    }

    // ostream operator for tree
    friend std::ostream& operator<<(std::ostream& os, const kd_tree<T,N>& tree){
        if(tree.root) {
            os << "kd tree : " << *tree.root;
        }
        return os;
    }
    
private:
    kd_tree_node<T,N>* root = nullptr;

    bool search_node(kd_tree_node<T,N>* nd, 
        const point<T,N>& p, int depth){
        // compute the dim of the dividing plane
        int curr_dim = depth % N;

        // we ended in a null node 
        if(!nd) return false;
        // we found the node
        else if(nd->data == p) return true;
        // if point value in curr_dim is less check left subtree
        // else right subtree
        else if(p.get_value_at_dim(curr_dim) < nd->data.get_value_at_dim(curr_dim)){
            return search_node(nd->left, p, depth+1);
        }
        else{
            return search_node(nd->right, p, depth+1);
        }
    }

    kd_tree_node<T,N>* insert_point(kd_tree_node<T,N>* nd, const point<T,N>& p, int depth){
        
        int curr_dim = depth % N;

        if(nd == nullptr){
            nd = new kd_tree_node<T,N>(p);
        }
        else if(p.get_value_at_dim(curr_dim)  < nd->data.get_value_at_dim(curr_dim)){
            nd->left = insert_point(nd->left, p, depth+1);
        }
        else{
            nd->right = insert_point(nd->right, p, depth+1);
        }

        return nd;
        
    }
    
};


// generate N-dimensional int points
static int MAX_VAL_INT = 1000;
template <size_t N>
void generate_points(std::vector<point<int,N>>& generated_points, int n) {
    for(int i=0; i<n; i++){
        std::vector<int> data (N, 0);
        std::for_each(data.begin(), data.end(),
            [](int& j) { 
                j = rand()%MAX_VAL_INT;    
            }); 

        generated_points.push_back(point<int, N>(data));
    }    
}



#endif
