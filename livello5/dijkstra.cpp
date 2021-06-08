#include <fstream>          //jRoe
using namespace std;

class core{
public:
    int from, to, cost;
    core(){
        from=0;
        to=0;
        cost=0;
    }
    
    core(int from, int to, int cost){
        this->from=from;
        this->to=to;
        this->cost=cost;
    }
};

template <class H> class Graph{
    H* nodes;
    core **edges;
    
    int _search(H node){
        int k=0;
        while(k<currentNodes && nodes[k]!=node){
            ++k;
        }
        if (!(k<currentNodes)){
            return -1;
        }
        return k;
    }

    int __getMinN(int *costs){
        int min=-1;
        int k;
        for(k=1; k<currentNodes; ++k){
            if (costs[k-1]>costs[k]){
                min = k;
            }
        }
        if (min<0){
            return -1;
        }
        return min;
    }
    
public:
    int sizenodes, sizedges, currentNodes, currentEdges;
    
    Graph(int sizenodes){
        this->sizenodes=sizenodes;
        sizedges=sizenodes*sizenodes;
        currentNodes=currentEdges=0;
        nodes = new H[this->sizenodes];
        edges = new core*[sizedges];
    }
    
    Graph* insertNode(H node){
        if(currentNodes<sizenodes){
            nodes[currentNodes++]=node;
        }
        return this;
    }
    
    Graph* insertEdge(H a, H b, int cost){
        if (!(currentEdges<sizedges)){
            return this;
        }
        int indexA = _search(a), indexB = _search(b);
        if(indexA<0 || indexB < 0){
            return this;
        }
        edges[currentEdges++] = new core(indexA, indexB, cost);
        return this;
    }
    
    /* Controlliamo un nodo per volta, prendendoli in ordine di peso, contenuto in costs. In questo modo siamo sicuri di prendere in nodo il cui cammino ha costo minore:
     * da A a B il costo è 30 ma da A a C il costo è 20, quindi scegliamo la strada che collega A a C, poiché meno costosa. Detto ciò, da A ci spostiamo a C.
     * Alla prossima iterazione dell'algoritmo, siamo a C. Da C a D abbiamo costo 9 ma da C a E abbiamo costo 28. Scegliamo di andare verso D e così via. 
    
     * Dijkstra utilizza 2 array: costs contiene il costo dei cammini minimi calcolati man mano, cioé ciò che c'interessa. Prex contiene i nodi 
     * di partenza di un cammino minimo (es. inizialmente abbiamo costo 80 per il cammino da A a G, ma l'algoritmo potrebbe trovare più conveniente, per andare verso G, partire
     * da nodo C anziché A, poiché l'arco che connette C a G ha costo 20. Potremmo scrivere questa informazione in edges, che contiene le informazioni sugli archi, però 
     * perderemo in questo modo il riferimento agli archi dati in input, modificando di fatto la struttura di tutto il grafo, portando in errore l'algoritmo.
     * Quindi, scriviamo questa informazione su prex, preservando il grafo originale).
     */
    
    string dijkstra(H source, H dest){
        string res = "inf.";
        int *prex = new int[sizenodes];
        int temp;
        int start = _search(source), end = _search(dest);
        if (start<0 || end<0){
            return "";
        }
        int* costs = new int[sizenodes];
        for(int k=0; k<sizenodes; ++k){
            costs[k]=INT32_MAX;
            prex[k]=INT32_MAX;
        }
        costs[start]=0;
        prex[start] = -1;
        for(int count=0; count<sizenodes; count++){
            temp = __getMinN(costs); //scelgo nodo con costo minore grazie al metodo __getMinN
            for(int k=0; k<currentEdges; ++k){
                if (costs[edges[k]->from]!=INT32_MAX && costs[edges[k]->from] + edges[k]->cost < costs[edges[k]->to]){
                    prex[edges[k]->to] = temp;
                    costs[edges[k]->to] = costs[edges[k]->from] + edges[k]->cost;
                }
            }
        }
        if (costs[end]!=INT32_MAX){
            res = to_string(costs[end]); //se il risultato è diverso da infinito, memorizzo questo numero in res. 
            //Tuttavia, essendo res una stringa e costs[end] un intero, non posso eguagliare direttamente res = costs[end], quindi ho bisogno di to_string 
            //(non richiede c++11).
        }
        delete[] costs; 
        delete[] prex;
        return res;
    }
};

int main(int argc, char **argv)
{
	ifstream *in = new ifstream("input.txt");
    ofstream *out = new ofstream("output.txt");
    string type;
    int itemp1, itemp2, sizenodes, sizedges, cost;
    double dtemp1, dtemp2;
    char c;
    while(*in >> sizenodes >> sizedges >> type){
        if (type == "int"){
            Graph<int>* g = new Graph<int>(sizenodes);
            for(int k=0; k<sizenodes; ++k){
                *in >> itemp1;
                g->insertNode(itemp1);
            }
            for(int k=0; k<sizedges; ++k){
                *in >> c >> itemp1 >> itemp2 >> cost >> c;
                g->insertEdge(itemp1, itemp2, cost);
            }
            *in >> itemp1 >> itemp2;
            *out << g->dijkstra(itemp1, itemp2) << endl;
            delete g;
        }
        else{
            Graph<double>* g = new Graph<double>(sizenodes);
            for(int k=0; k<sizenodes; ++k){
                *in >> dtemp1;
                g->insertNode(dtemp1/10);
            }
            for(int k=0; k<sizedges; ++k){
                *in >> c >> dtemp1 >> dtemp2 >> cost >> c;
                g->insertEdge(dtemp1, dtemp2, cost);
            }
            *in >> dtemp1 >> dtemp2;
            *out << g->dijkstra(dtemp1, dtemp2) << endl;
            delete g;
        }
    }
    in->close();
    out->close();
    delete in;
    delete out;
	return 0;
}
