#include <iostream>
#include "kd_tree.h"


int main(int, char**) {

    srand (time(NULL));
    
    // generate a set of 2d points
    std::vector<point<int,2>> points_2d;
    generate_points<2>(points_2d,5);
    std::for_each(points_2d.begin(), points_2d.end(), 
        [](point<int,2>& p){
            std::cout << p << " ";
        }
    );
    std::cout  << std::endl;

    // construct a kd-tree with the points
    kd_tree<int, 2> tree(points_2d);
    std::cout << tree << std::endl;

    // search for some point
    std::vector<int> spv = {1,2};
    point<int,2> sp(spv);
    std::cout << "point " << sp << 
        " FOUND : " << tree.search_point(sp) << std::endl;

    // add a point and search for it
    std::vector<int> spv1 = {32,982};
    point<int,2> sp1(spv);
    tree.add_point(sp1);
    std::cout << "point " << sp1 << 
        " FOUND : " << tree.search_point(sp1) << std::endl;


    return 0;
}
