/* Cambiato il nome da RB-Tree-Insert a insert-RBTree
Un Albero Rosso-Nero è un albero binario di ricerca in cui ad ogni nodo è associato un colore il quale può essere rosso o nero. Inoltre è necessario che i nodi siano disposti in modo da soddisfare 5 semplici regole. Quando tali regole sono rispettate l'albero risulta essere bilanciato ed ogni operazione di inserimento, cancellazione o ricerca può essere svolta in tempo logaritmico, nel caso pessimo.

Specifiche
Si implementi una classe RBtree, attraverso l'utilizzo dei template, contenente elementi di tipo generico H. La classe dovrà implementare la procedura di inserimento di un nuovo elemento e la procedura di stampa degli elementi in essa contenuti. La stampa dovrà essere effettuata utilizzando la visita inorder, postorder o preorder.

Dati in input
L'input è suddiviso in 100 task, uno per ogni riga. Ogni riga del file di input è formata da 3+N elementi. Il primo elemento è una stringa che identifica il tipo di dato (H) che dovrà essere contenuto all'interno dell'albero rosso-nero. Il secondo elemento è un valore intero N, il quale rappresenta l'insieme degli elementi che dovranno essere inseriti nella struttura dati. il terzo elemento è una stringa che identifica l'ordine in cui gli elementi dovranno essere presentati in output ("inorder", "preorder" o "postorder"). Seguono N valori che rappresentano, nell'ordine dato, gli elementi di tipo H che dovranno essere inseriti all'interno dell'albero.

Dati in output
L'output dovrà essere formato da 100 righe, una per ogni task. Ogni riga contiene una lista di N elementi, i quali rappresentano gli nodi dell'albero, nell'ordine indicato in input. Per ogni nodo dovranno essere stampati la chiave k ed il colore c, separati da una virgola e racchiusi tra parentesi. Il colore c dovrà essere uguale a B (per indicare il Nero/Black) o uguale a R (per indicare il Rosso/Red ).
Ad esempio un nodo nero contenete la chiave 45 dovrà essere rappresentato dalla stringa "(45,B)", mentre un nodo rosso contenete la chiave 34.6 dovrà essere rappresentato dalla stringa "(34.6,R)".

Note
N è un numero intero compreso tra 10 e 200.
Il tipo H può essere uno desi seguenti tipi di dato: int, double.
Tutti gli elementi presenti nella lista sono distinti.
I primi 30 task di input prevedono esclusivamente il tipo di dato int.
ATTENZIONE! Il carattere ',' potrebbe essere sostituito da uno spazio.

Esempio
Il seguente esempio presenta un file di input, contenente 3 task, ed il corrispondente file di output.

input.txt:
int 10 preorder 348 588 185 954 673 189 162 956 829 720
int 10 postorder 910 165 53 278 44 299 745 479 793 255
int 10 inorder 790 964 63 638 953 273 690 299 117 217

output.txt
(673,B) (348,R) (185,B) (162,R) (189,R) (588,B) (954,R) (829,B) (720,R) (956,B)
(44,R) (53,B) (255,R) (278,B) (165,R) (479,B) (793,R) (910,B) (745,R) (299,B)
(63,R) (117,B) (217,R) (273,R) (299,R) (638,B) (690,R) (790,B) (953,R) (964,B) 
*/

#include <iostream>
#include <fstream>

#define max(A, B) A > B ? A : B
using namespace std;

template <class T>
class Node
{
private:
    int color;
    T key;
    Node<T> *left, *right, *parent;

public:
    Node(T key, int color)
    {
        this->color = color;
        this->key = key;
        left = right = parent = NULL;
    }

    T getKey()
    {
        return key;
    }

    int getColor()
    {
        return color;
    }

    Node<T> *getLeft()
    {
        return left;
    }

    Node<T> *getRight()
    {
        return right;
    }

    Node<T> *getParent()
    {
        return parent;
    }

    void setKey(T nkey)
    {
        this->key = nkey;
    }

    void setColor(int ncolor)
    {
        this->color = ncolor;
    }

    void setLeft(Node<T> *nleft)
    {
        this->left = nleft;
    }

    void setRight(Node<T> *nright)
    {
        this->right = nright;
    }

    void setParent(Node<T> *nparent)
    {
        this->parent = nparent;
    }
};

template <class T>
class RBTree
{
private:
    const int RED = 1;
    const int BLACK = 0;
    Node<T> *root;

    int isLeftChild(Node<T> *x)
    {
        return x == x->getParent()->getLeft();
    }

    void insertNodeUp(Node<T> *parent, Node<T> *child)
    {
        if (parent->getParent() != NULL)
        {
            if (isLeftChild(parent))
                parent->getParent()->setLeft(child);
            else
                parent->getParent()->setRight(child);
        }
        else
            this->setRoot(child);
        child->setParent(parent->getParent());
        parent->setParent(child);
    }

    Node<T> *getUncle(Node<T> *x)
    {
        if (x->getParent() != NULL && x->getParent()->getParent() != NULL)
        {
            if (isLeftChild(x->getParent()))
                return x->getParent()->getParent()->getRight();
            return x->getParent()->getParent()->getLeft();
        }
        return NULL;
    }

    void leftRotate(Node<T> *x)
    {
        Node<T> *nParent = x->getRight();
        insertNodeUp(x, nParent);
        x->setRight(nParent->getLeft());
        if (nParent->getLeft() != NULL)
            nParent->getLeft()->setParent(x);
        nParent->setLeft(x);
    }

    void rightRotate(Node<T> *x)
    {
        Node<T> *nParent = x->getLeft();
        insertNodeUp(x, nParent);
        x->setLeft(nParent->getRight());
        if (nParent->getRight() != NULL)
            nParent->getRight()->setParent(x);
        nParent->setRight(x);
    }

    void swapColors(Node<T> *n1, Node<T> *n2)
    {
        int tmp = n1->getColor();
        n1->setColor(n2->getColor());
        n2->setColor(tmp);
    }

    void insertFixUp(Node<T> *x)
    {
        if (x == this->getRoot())
        {
            x->setColor(BLACK);
            return;
        }
        Node<T> *parent = x->getParent();
        Node<T> *uncle = getUncle(x);
        Node<T> *grandparent = parent->getParent();

        if (parent->getColor() != BLACK)
        {
            if (uncle != NULL && uncle->getColor() == RED)
            {
                parent->setColor(BLACK);
                uncle->setColor(BLACK);
                grandparent->setColor(RED);
                insertFixUp(grandparent);
            }
            else
            {
                if (isLeftChild(parent))
                {
                    if (isLeftChild(x))
                        swapColors(parent, grandparent);
                    else
                    {
                        leftRotate(parent);
                        swapColors(x, grandparent);
                    }
                    rightRotate(grandparent);
                }
                else
                {
                    if (isLeftChild(x))
                    {
                        rightRotate(parent);
                        swapColors(x, grandparent);
                    }
                    else
                        swapColors(parent, grandparent);
                    leftRotate(grandparent);
                }
            }
        }
    }

    Node<T> *search(T key)
    {
        Node<T> *tmp = this->getRoot();
        while ((tmp != NULL) && (tmp->getKey() != key))
        {
            if (key < tmp->getKey())
            {
                if (tmp->getLeft() != NULL)
                    tmp = tmp->getLeft();
                else
                    break;
            }
            else
            {
                if (tmp->getRight() != NULL)
                    tmp = tmp->getRight();
                else
                    break;
            }
        }
        return tmp;
    }

    void preOrder(Node<T> *x, ofstream &out)
    {
        if (x)
        {
            out << "(" << x->getKey() << " " << this->printCharColor(x->getColor()) << ") ";
            preOrder(x->getLeft(), out);
            preOrder(x->getRight(), out);
        }
    }

    void inOrder(Node<T> *x, ofstream &out)
    {
        if (x)
        {
            inOrder(x->getLeft(), out);
            out << "(" << x->getKey() << " " << this->printCharColor(x->getColor()) << ") ";
            inOrder(x->getRight(), out);
        }
    }

    void postOrder(Node<T> *x, ofstream &out)
    {
        if (x)
        {
            postOrder(x->getLeft(), out);
            postOrder(x->getRight(), out);
            out << "(" << x->getKey() << " " << this->printCharColor(x->getColor()) << ") ";
        }
    }

public:
    RBTree()
    {
        root = NULL;
    }

    void setRoot(Node<T> *x)
    {
        root = x;
    }

    Node<T> *getRoot()
    {
        return root;
    }

    RBTree<T> *insertKey(T key)
    {
        Node<T> *x = new Node<T>(key, RED);
        if (root == NULL)
            this->setRoot(x);
        else
        {
            Node<T> *tmp = search(key);
            if (tmp->getKey() != key)
            {
                if (key < tmp->getKey())
                    tmp->setLeft(x);
                else
                    tmp->setRight(x);
                x->setParent(tmp);
            }
            else
                return this;
        }
        insertFixUp(x);
        return this;
    }

    void preOrder(ofstream &out)
    {
        preOrder(this->getRoot(), out);
        out << endl;
    }

    void inOrder(ofstream &out)
    {
        inOrder(this->getRoot(), out);
        out << endl;
    }

    void postOrder(ofstream &out)
    {
        postOrder(this->getRoot(), out);
        out << endl;
    }

    char printCharColor(int c)
    {
        if (c)
            return 'R';
        return 'B';
    }

    int Height(Node<T> *x)
    {
        if (x == NULL)
            return 0;
        int sx = Height(x->getLeft());
        int dx = Height(x->getRight());
        return 1 + max(dx, sx);
    }
};

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    string type, print;
    int N;
    for (int task = 0; task < 100; task++)
    {
        in >> type >> N >> print;
        if (type[0] == 'i')
        {
            int key;
            RBTree<int> *tree = new RBTree<int>();
            for (int i = 0; i < N; i++)
            {
                in >> key;
                tree->insertKey(key);
            }
            if (print == "preorder")
                tree->preOrder(out);
            else if (print == "inorder")
                tree->inOrder(out);
            else if (print == "postorder")
                tree->postOrder(out);
        }
        else if (type[0] == 'd')
        {
            double key;
            RBTree<double> *tree = new RBTree<double>();
            for (int i = 0; i < N; i++)
            {
                in >> key;
                tree->insertKey(key);
            }
            if (print == "preorder")
                tree->preOrder(out);
            else if (print == "inorder")
                tree->inOrder(out);
            else if (print == "postorder")
                tree->postOrder(out);
        }
    }
}