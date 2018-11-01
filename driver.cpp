#include "Common.h"
#include <vector>
#include <iostream>
using namespace std;

void run_marix_chain_mult(){
    
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

void run_edit(){
    string s1 = "geek";
    string s2 = "gesek";
    
    cout << "Edit distance for " << s1 << " " << s2 << " : \n" << EditDistance(s1, s2) << "\n";
    s1 = "cat";
    s2 = "cut";
    
    cout << "Edit distance for " << s1 << " " << s2 << " : \n" << EditDistance(s1, s2) << "\n";
    s1 = "sunday";
    s2 = "saturday";
    
    cout << "Edit distance for " << s1 << " " << s2 << " : \n" << EditDistance(s1, s2) << "\n";

}

void run_distcover(){
    std::vector<int> steps;
    steps.push_back(1);
    steps.push_back(2);
    steps.push_back(3);
    
    cout << "No of ways to cover the distance = \n " << CoverDistance(steps, 3) << "\n";
    cout << "No of ways to cover the distance = \n " << CoverDistance(steps, 4) << "\n";
    

}

void run_subsetsum(){
    std::vector<int> set;
    set.push_back(3);
    set.push_back(34);
    set.push_back(4);
    set.push_back(12);
    set.push_back(5);
    set.push_back(2);
    cout << "subset sum result : \n" << SubSetSum(set, 9) << "\n";
}

int main(){
    //run_marix_chain_mult();
    //run_edit();
    //run_distcover();
    run_subsetsum();
    return 0;
}
