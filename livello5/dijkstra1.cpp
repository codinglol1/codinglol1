/* rinominato da Dijkstra a dijkstra1
L'algoritmo di Dijkstra è un algoritmo utilizzato per calcolare i cammini minimi in un grafo con pesi non negativi sugli archi. Fu pubblicato nel 1959 dall'informatico 
olandese Edsger Dijkstra e trova applicazione in molteplici contesti quale l'ottimizzazione nella realizzazione di reti (idriche, telecomunicazioni, stradali, circuitali, ecc.) 
o l'organizzazione e la valutazione di percorsi runtime nel campo della robotica.

Specifiche
Si implementi la classe Grafo supponendo che gli archi siano direzionati e che i nodi contengano chiavi di tipo generico. In seguito, si fornisca l'implementazione 
dell'algoritmo di Dijkstra in grado di calcolare il peso dei cammini minimi da una data sorgente verso tutti i nodi del grafo.

Dati in input
L'input è suddiviso in 100 task, uno per ogni riga. Ogni riga del file di input è formata da N+M+5 elementi. I primi due elementi sono dei valori numerici interi, N ed M, i quali 
rappresentano il numero di nodi ed il numero di archi presenti nel grafo. Segue una stringa di testo che identifica il tipo di dato (int o double) che dovrà essere contenuto 
all'interno dei nodi del Grafo. Segue la sequenza delle chiavi relative agli N nodi, in ordine sparso, e la sequenza degli M archi del grafo (in ordine sparso). 
Ogni arco è rappresentato da tre elementi (le chiavi dei nodi sorgente e destinazione, nell'ordine, e il peso dell'arco) separati da una virgola e racchiusi tra parentesi. 
Gli ultimi due elementi sono la chiave del nodo sorgente e quella del nodo destinazione per i quali si vuole calcolare il cammino minimo.

Dati in output
L'output dovrà essere formato da 100 righe, una per ogni task. Ogni riga contiene un unico valore intero il quale rappresenta la distanza di cammino minimo tra il 
nodo sorgente e in nodo destinazione. Nel caso in cui non esista alcun cammino tra i nodi indicati dovrà essere stampata la stringa "inf.".

Note
N è sempre un valore inferiore a 100.
il peso degli archi è sempre minore o uguale a 100.
Gli archi hanno tutti un peso non negativo.
ATTENZIONE! Il carattere ',' potrebbe essere sostituito da uno spazio.

Esempio
Il seguente esempio presenta un file di input, contenente 3 task, ed il corrispondente file di output.

input.txt:
5 11 int 33 48 50 72 34 (33,72,20) (33,34,36) (48,33,53) (48,50,56) (48,34,9) (50,48,93) (50,72,74) (50,34,98) (72,48,52) (72,34,28) (34,50,5) 48 72
5 11 int 54 91 88 58 63 (54,91,24) (54,88,43) (54,63,99) (91,88,26) (88,54,56) (88,91,69) (88,58,65) (88,63,13) (58,63,67) (63,91,42) (63,58,89) 58 54
5 9 int 72 19 57 55 56 (72,19,24) (72,55,80) (19,57,74) (57,72,18) (57,19,25) (57,56,89) (55,19,25) (56,57,49) (56,55,29) 56 19

output.txt
73
191
54
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

template <class T>
int findIndex(T *A, int size, T x)
{
    for (int i = 0; i < size; i++)
    {
        if (A[i] == x)
            return i;
    }
    return -1;
}

template <class T>
void createAdj(ifstream &in, int N, int M, T *V, int **A)
{
    char garbage;
    T node1, node2;
    int w;
    for (int i = 0; i < M; i++)
    {
        in >> garbage >> node1 >> node2 >> w >> garbage;
        A[findIndex<T>(V, N, node1)][findIndex<T>(V, N, node2)] = w;
    }
}

int extractMin(vector<int> &q, int *distances)
{
    int min = q[0];
    int index = 0;
    for (int i = 1; i < q.size(); i++)
    {
        if (distances[q[i]] < distances[min])
        {
            min = q[i];
            index = i;
        }
    }
    q[index] = q[q.size() - 1];
    q.pop_back();
    return min;
}
template <class T>
void Dijkstra(int **Adj, T *V, int N, T keysrc, int *&distances, int *&predecessors)
{
    int src = findIndex(V, N, keysrc);
    distances = new int[N];
    predecessors = new int[N];
    vector<int> q = vector<int>(N); //Vettore che contiene gli indici dei nodi

    //Initialize Single-source
    for (int i = 0; i < N; i++)
    {
        distances[i] = INT_MAX;
        predecessors[i] = -1;
        q[i] = i;
    }
    distances[src] = 0;

    while (!q.empty())
    {
        int tmp = extractMin(q, distances);
        if (distances[tmp] == INT_MAX)
            break;

        for (int i = 0; i < N; i++)
        {
            if (Adj[tmp][i] > -1)
            {
                int newval = distances[tmp] + Adj[tmp][i];
                if (newval < distances[i])
                {
                    distances[i] = newval;
                    predecessors[i] = tmp;
                }
            }
        }
    }
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int N, M;
    string type;

    for (int task = 0; task < 100; task++)
    {
        in >> N >> M >> type; // N numero nodi, M numero archi
        int **Adj = new int *[N];
        int *distances = new int[N];
        int *predecessors = new int[N];
        for (int i = 0; i < N; i++)
        {
            Adj[i] = new int[N];
            for (int j = 0; j < N; j++)
                Adj[i][j] = -1;
        }
        if (type[0] == 'i')
        {
            int V[N];
            int keysrc;
            int finalkey;
            for (int i = 0; i < N; i++)
                in >> V[i];
            createAdj<int>(in, N, M, V, Adj);
            in >> keysrc >> finalkey;
            Dijkstra<int>(Adj, V, N, keysrc, distances, predecessors);
            out << distances[findIndex(V, N, finalkey)] << endl;
        }
        else if (type[0] == 'd')
        {
            double V[N];
            double keysrc;
            double finalkey;
            for (int i = 0; i < N; i++)
                in >> V[i];
            createAdj<double>(in, N, M, V, Adj);
            in >> keysrc >> finalkey;
            Dijkstra<double>(Adj, V, N, keysrc, distances, predecessors);
            out << distances[findIndex(V, N, finalkey)] << endl;
        }
    }
}