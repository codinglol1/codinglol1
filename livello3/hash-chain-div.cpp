#include<iostream>
#include<fstream>
#include<list>
#include <math.h>
using namespace std;

template<class T> class ChainedHashTable{
    private:
        list<T> *l;
        int m;
        int n;
        double c; 
        int divisonMethod(int key){
            return key % this->m;
        }

       
    public:
        ChainedHashTable(int m,int n){
            c = 0.61803;
            this->n =n;
            this->m = m;
            l = new list<T>[m];
        }

    ChainedHashTable<T>* insertKey(T k){
        int index = divisonMethod(k);
       
        l[index].push_back(k);
        return this;
    }
    
    void printTable(ofstream &out){
        int count = 0;
        for(int i=0;i < m; i++){
                out<<l[i].size() <<" ";
               
        }
         out<<endl;
    }
};

int main(){
 ifstream in("input.txt");
 ofstream out("output.txt");

for(int i=0; i<100;i++){
    string type; in >> type;
    int m; in >> m;
    int n; in >>n;
    
    if(type=="int"){
        ChainedHashTable<int> *t = new ChainedHashTable<int>(m,n);
        for(int i=0;i<n;i++){
            int key; in >> key;
            t->insertKey(key);
           
        }
        t->printTable(out);
    }

    if(type =="double"){
        ChainedHashTable<int> *t = new ChainedHashTable<int>(m,n);
        for(int i=0;i<n;i++){
            double key; in >> key;
            t->insertKey(key);
           
        }
       t->printTable(out);
    }

    if(type== "bool"){
        ChainedHashTable<int> *t = new ChainedHashTable<int>(m,n);
        for(int i=0;i<n;i++){
            bool key; in >> key;
            t->insertKey(key);
            
        }
       t->printTable(out);
    }

    if(type=="char"){
        ChainedHashTable<int> *t = new ChainedHashTable<int>(m,n);
        for(int i=0;i<n;i++){
            char key; in >> key;
            t->insertKey(key);
            
        }
        t->printTable(out);
    }
}
}