// in a DAG
#include <iostream>
#include <list>
#include <stack>
#include <limits.h>
#define NINF INT_MIN //minimo valor de um inteiro -2147483648
using namespace std;

/*
Represetação do Grafo com lista de adjacencia.
O nós possuem o vertice com que estão conectados e
seu respectivo peso (valor da aresta / borda).
*/

class AdjListNode
{
    int v;
    int weight;
public:
    AdjListNode(int _v, int _w){
        v = _v;
        weight = _w;
    }

    int getV(){
        return v;
    }

    int getWeight(){
        return weight;
    }
};

/*
Umma Classe pra representar o grafo com lista de adjacencia
*/
class Graph{
    int V;    // Numero de vértices

    list<AdjListNode> *adj; //ponteiro para um array de vetor de lista

    // A function used by longestPath
    void topologicalSortUtil(int v, bool visited[],stack<int> &Stack);
public:
    Graph(int V);//

    // function to add an edge to graph
    void addEdge(int u, int v, int weight);

    // Finds longest distances from given source vertex
    void longestPath(int s);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<AdjListNode>[V];
}

void Graph::addEdge(int u, int v, int weight)
{
    AdjListNode node(v, weight);
    adj[u].push_back(node); // Add v to u's list
}

// A recursive function used by longestPath. See below
// link for details
// https://www.geeksforgeeks.org/topological-sorting/
void Graph::topologicalSortUtil(int v, bool visited[],stack<int> &Stack){
    visited[v] = true;//marca o nó que ele está como visitado

    // aqui ele vai verificar os vertices adjacentes ao vertice atual v.

    list<AdjListNode>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i){
        AdjListNode node = *i;
        if (!visited[node.getV()])
            topologicalSortUtil(node.getV(), visited, Stack);
    }

    Stack.push(v);//empilha o vertice atual na pilha Stach
}

/*
encontrar a maior distancia a partir de um vertice s.
topologicalSortUtil() é usado para pegar a ordem topologica
*/

void Graph::longestPath(int s)
{
    stack<int> Stack; // uma pilha da classe 'stack' para empilhar os nós visitados
    int dist[V];

    //Inicializa todos os vertices como nao visitados
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Call the recursive helper function to store Topological
    // Sort starting from all vertices one by one
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, Stack);

    /*
    vai inicializar o vetor de distancias dist() com NINF, no caso
    isso é apenas pra preencher o vetor com "nada" por assim dizer,
    e a posiçao do no origem s ele preenche com zero, pra saber quando é a origem
    e nao calcular a distancia até ele
    */
    for (int i = 0; i < V; i++)
        dist[i] = NINF;
    dist[s] = 0;

    // Process vertices in topological order
    while (Stack.empty() == false){ // verifica se a pilha está vazia
        // pega o proximo vertice da ordem topologica
        int u = Stack.top();
        Stack.pop(); //desempilha a pilha

        //atualiza as distancias de todos os vertices
        list<AdjListNode>::iterator i;
        if (dist[u] != NINF){
            for (i = adj[u].begin(); i != adj[u].end(); ++i){
                if(dist[i->getV()] < dist[u] + i->getWeight())
                    dist[i->getV()] = dist[u] + i->getWeight();
            }
        }
    }

    //a maior distancia do vertice de origem para todos os vertices
    for (int i = 0; i < V; i++)
        (dist[i] == NINF)? cout << "INF ": cout << dist[i] << " ";
}

int main(void){
    // 0=r, 1=s, 2=t, 3=x, 4=y, 5=z
    Graph g(6);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 2);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 5, 1);
    g.addEdge(3, 4, -1);
    g.addEdge(4, 5, -2);

    int s;
    cout <<"entre com o no de origem: ";
    cin >> s;

    cout << "as distancias maximas do no de origem para todos os outros " << s <<" \n";
    g.longestPath(s);

    return 0;
}
