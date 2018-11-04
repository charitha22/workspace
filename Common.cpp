#include "Common.h"
#include <iostream>
#include <algorithm>
using namespace std;
int MIN(int a, int b){
    if(a<b) return a;
    return b;
}
int MAX(int a, int b){
    if(a<b) return b;
    return a;
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



int CoverDistance(std::vector<int>& steps, int N){
    int storage[N+1];
    
    for(int i=0; i<=N; i++) storage[i] = 0;
    storage[0] = 1;
    
    for(int i=1; i<=N; i++){
        for(auto s: steps){
            if(i-s >= 0) storage[i] += storage[i-s];
        }
    }

    return storage[N];
}


int SubSetSum(vector<int>& set, int S){
    bool storage[set.size()+1][S+1];

    for(int i=0; i<set.size()+1; i++)
        for(int j=0; j<S+1; j++)
            storage[i][j] = false;
    
    for(int i=0; i<set.size(); i++) storage[1][set[i]] = true;

    for(int i=2; i<=set.size(); i++){
        for(int j=1; j<=S; j++){
            if(j<set[i]) storage[i][j] = storage[i-1][j];
            else if(j>=set[i]) storage[i][j] = storage[i-1][j] | storage[i-1][j-set[i]];
        }
    }

    for(int i=0; i<set.size()+1; i++){
        for(int j=0; j<S+1; j++){
            cout << storage[i][j] << " ";
        }
        cout << "\n";
    }


    return storage[set.size()][S];
}

int KnapSack(vector<int>& V, vector<int>& W, int C){

    int S[V.size()+1][C+1];
    
    for(int i=0; i<C+1; i++) S[0][i] = 0;
    
    for(int i=1; i<V.size()+1; i++){
        for(int j=1; j<C+1; j++){
            if(W[i] > j) S[i][j] = 0;
            else S[i][j] = MAX(S[i-1][j], S[i-1][j-W[i]]+V[i]);
        }
    }
    return S[V.size()][C];
}


int CoinChange(vector<int>& S, int V){

    int T[S.size()+1][V+1];

    for(int i=0; i<V+1; i++) T[0][i] = 0;
    for(int i=0; i<S.size()+1; i++) {
        T[i][0] = 1;
    }
    for(int i=1; i<S.size()+1; i++){
        for(int j=1; j<V+1; j++){
            int x  = 0;
            if(S[i-1] <= j) x = T[i][j-S[i-1]];
            T[i][j] = x + T[i-1][j];
        }
    }

    
    //for(int i=1; i<S.size()+1; i++){
        //for(int j=1; j<V+1; j++){
            //cout << T[i][j] << " ";
        //}
        //cout << endl;
    //}
       

    return T[S.size()][V];
}












