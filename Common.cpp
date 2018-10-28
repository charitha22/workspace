#include "Common.h"
#include <iostream>
using namespace std;
int MIN(int a, int b){
    if(a<b) return a;
    return b;
}
int RowsOf(std::vector<int>& p, int i) {
    return p[i];
}
int ColsOf(std::vector<int>& p, int i){
    return p[i+1];
}

int MatrixChainMult(std::vector<int>& p){
    int N = p.size()-1;

    // M[i][j] gives min chain multiplications for Mi...Mj
    int M[N-1][N-1];
    for(int i=0; i<=N-1; i++) M[i][i] = 0;

    for(int j=1; j<=N-1; j++){

        for(int i=0; i<=N-1-j; i++){
            //cout << i << endl;
            int min = 10000000;
            for(int k=0; k<j; k++){
                //cout << M[i][i+k] << endl;
                //cout << M[i+k+1][i+j] << endl;
                min = MIN(min, M[i][i+k] + M[i+k+1][i+j] + RowsOf(p, i) * ColsOf(p, i+k) * ColsOf(p, i+j));
            }
            //cout << "M(" << i << "," << j+i << ")" << " = " << min << endl;
            M[i][i+j] = min;
        }
    }

    //cout << RowsOf(p,2) << " " << ColsOf(p,2) << endl;

    return M[0][N-1];
}

int EditDistance(string s1, string s2){
    int l1 = s1.length();
    int l2 = s2.length();
    int table[l1+1][l2+1];

    for(int i=0; i<l1+1; i++) table[i][0] = i;
    for(int i=0; i<l2+1; i++) table[0][i] = i;

    
    for(int i=1; i<l1+1; i++){
        for(int j=1; j<l2+1; j++){
            if(s1[i-1] == s2[j-1]) table[i][j] = table[i-1][j-1];
            else{
                table[i][j] = MIN(table[i-1][j-1] , MIN(table[i-1][j], table[i][j-1]))+1;
            }
        }
    }

    //for (int i=0; i<l1+1; i++){
        //for(int j=0; j<l2+1; j++){
            //cout << table[i][j]  << " ";
        //}
        //cout << "\n";
    //}
    return table[l1][l2];
}
