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

