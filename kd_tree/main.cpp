#include <iostream>
#include "kd_tree.h"


int main(int, char**) {

    srand (time(NULL));
    
    // generate a set of 2d points
    std::cout << "generate a set of points :" << std::endl;
    std::vector<point<int,2>> points_2d;
    generate_points<2>(points_2d,5);
    std::for_each(points_2d.begin(), points_2d.end(), 
        [](point<int,2>& p){
            std::cout << p << " ";
        }
    );
    std::cout  << "\n\n";

    // construct a kd-tree with the points
    std::cout << "TEST 01 : contruct a tree" << std::endl; 
    kd_tree<int, 2> tree(points_2d);
    std::cout << tree << "\n\n";

    // search for some point
    std::cout << "TEST 02 : searching the tree for a point"<< std::endl; 
    std::vector<int> v1 = {1,2};
    point<int,2> p1(v1);
    std::cout << "point " << p1 << 
        " FOUND : " << tree.search_point(p1) << "\n\n";

    // add a point and search for it
    std::cout << "TEST 03 : add a point and serach for it"<< std::endl; 
    std::vector<int> v2 = {32,982};
    point<int,2> p2(v2);
    tree.add_point(p2);
    std::cout << "point " << p2 << 
        " FOUND : " << tree.search_point(p2) << "\n\n";

    
    // find nearset neighbor of a point
    std::cout << "TEST 04 : find nearest neighbor of a point"<< std::endl; 
    std::vector<int> v3 = {32, 982};
    point<int,2> p3(v3);
    std::cout << "nearset neighbor of point " << p3 << " is " << 
        tree.find_nearest_neighbour(p3) << "\n";

    return 0;
}
