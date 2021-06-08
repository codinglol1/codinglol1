#include<iostream>
#include<fstream>

using namespace std;

void printC(ofstream &out,int *C,int k,int min){
    for(int i=min; i < k; i++)
        out<<C[i]<<" ";
   
}


void printArr(ofstream &out,int *A,int n){
    for(int i=1; i <= n; i++)
        out<<A[i]<<" ";
    out<<endl;
}

void countingSort(ofstream &out,int *A,int n){
    int max = A[0];
    for(int i=1; i < n; i++){
        if (max < A[i])
            max = A[i];
    }
    int min = A[0];

    for(int i=1; i < n; i++){
        if (min > A[i])
            min = A[i];
    }

    int k = max  + 1;
    int *C = new int[k];
    int *B = new int[n+1];

    for(int i=0;i < k; i++)
        C[i] = 0;
    for(int i=0; i < n; i++){
        C[A[i]] += 1;
    }

    for(int i=1; i <= k; i++)
        C[i] += C[i-1];

    for(int j = n-1; j >= 0; j--){
        B[C[A[j] ]] = A[j];
        C[A[j]] -=1;
    }
    printC(out,C,k,min);
    printArr(out,B,n);
}



int main(){
    ofstream out("output.txt");
    ifstream in("input.txt");

    for(int i=0; i < 100; i++){
        int n; in >> n;
        int *v = new int[n];
        for(int j = 0; j < n; j++){
            int tmp; in >> tmp;
            v[j] = tmp;
        }
        countingSort(out,v,n);
    }
}
