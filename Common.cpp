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

int LCS(string s1, string s2){
    int l1 = s1.length();
    int l2 = s2.length();

    int S[l1+1][l2+1];

    for(int i=0; i<=l1; i++) S[i][0] = 0;
    for(int i=0; i<=l2; i++) S[0][i] = 0;

    for(int i=1; i<=l1; i++){
        for(int j=1; j<=l2; j++){
            if(s1[i-1] == s2[j-1]) S[i][j] = S[i-1][j-1] + 1;
            else S[i][j] = MAX(S[i-1][j] , S[i][j-1]);
        }
    }

    return S[l1][l2];
}

int ShortestSuperSequence(string s1, string s2){
    int l = LCS(s1, s2);

    return s1.length()+s2.length()-l;
}

void Merge(int * arr, int l, int m, int h){

    int l1 = m-l+1;
    int l2 = h-m;

    int L[l1];
    int R[l2];
    for(int i=0; i<l1; i++) L[i] = arr[l+i];
    for(int i=0; i<l2; i++) R[i] = arr[m+1+i];

    int i = 0;
    int j = 0;
    int k = l;
    while(i<l1 && j<l2){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    for(int a=i; a<l1; a++) arr[k++] = L[a];
    for(int a=j; a<l2; a++) arr[k++] = R[a];
   
}


void MergeSort(int* arr, int l, int h){
    
    if(l<h){
        int mid = (l+h)/2;
        
        MergeSort(arr, l, mid);
        MergeSort(arr, mid+1, h);
        
        Merge(arr, l, mid, h);
    }
}

void swap(int* x, int* y){
    int temp  = *x;
    *x = *y;
    *y = temp;
}

int QSPartition(int * arr, int l, int h){

    int pivot = arr[h];
    int i  = l;
    for(int j=l; j<=h-1; j++){
        if(arr[j] < pivot){
            if(j!=i) swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[h]);
    //for(auto i=l ;i<=h; i++) cout << arr[i] << " " ;
    //cout << endl;


    return i;
    
}


void QuickSort(int* arr, int l, int h){
    if(l<h){
        int p = QSPartition(arr, l, h);  
        QuickSort(arr, l, p-1);
        QuickSort(arr, p+1, h);
    }

}

int NumMult(int i, int j, vector<vector<int>>& Storage, vector<int>& p){
    if(Storage[i][j] != -1) return Storage[i][j];
    
    int min = 100000000;
    for(int k=0; k<j-i; k++){
        min = MIN(min, NumMult(i,i+k, Storage, p) +  NumMult(i+k+1, j, Storage, p) 
                + RowsOf(p, i)*ColsOf(p, i+k)*ColsOf(p, j));
    }
    Storage[i][j] = min;
    return min;
}

int MatrixChainMultRecur(std::vector<int>& p){
    int N = p.size()-1;
    vector<vector<int>> S;
    
    for(int i=0; i<N; i++){
        vector<int> temp;
        for(int j=0; j<N; j++) {
            if(i==j) temp.push_back(0);
            else temp.push_back(-1);
        }
        S.push_back(temp);
    }

    //cout << S[N-1][N-1] << endl;

    //return 0;
    return NumMult(0, N-1, S,p);
}



