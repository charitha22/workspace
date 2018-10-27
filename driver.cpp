#include "Common.h"
#include <vector>
#include <iostream>
using namespace std;

int main(){
    
    std::vector<int> p;
    p.push_back(40);
    p.push_back(20);
    p.push_back(30);
    p.push_back(10);
    p.push_back(30);
    cout << "Test case 1 \n";
    cout << "No of Multiplications : \n" << MatrixChainMult(p) << "\n";

    p.clear();
    p.push_back(10);
    p.push_back(20);
    p.push_back(30);
    p.push_back(40);
    p.push_back(30);

    cout << "Test case 2 \n";
    cout << "No of Multiplications : \n" << MatrixChainMult(p) << "\n";
    
    p.clear();
    p.push_back(10);
    p.push_back(20);
    p.push_back(30);
    cout << "Test case 3 \n";
    cout << "No of Multiplications : \n" << MatrixChainMult(p) << "\n";





}
