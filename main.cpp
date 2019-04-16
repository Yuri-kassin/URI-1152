#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <string.h> // memset
using namespace std;

class Aresta
{
    int vertice1, vertice2, peso;

public:

    Aresta(int v1, int peso, int v2)
    {
        vertice1 = v1;
        vertice2 = v2;
        this->peso = peso;
    }

    int obterVertice1()
    {
        return vertice1;
    }

    int obterVertice2()
    {
        return vertice2;
    }

    int obterPeso()
    {
        return peso;
    }

    // sobrescrita do operador "<"
    bool operator < (const Aresta& aresta2) const
    {
        return (peso < aresta2.peso);
    }
};

class Grafo
{
    int V; // número de vértices
    vector<Aresta> arestas; // vetor de arestas
    int R;

public:

    Grafo(int V)
    {
        this->V = V;
    }

    // função que adiciona uma aresta
    void adicionarAresta(int v1, int v2, int peso)
    {
        Aresta aresta(v1,peso, v2);
        arestas.push_back(aresta);
    }

    // função que busca o subconjunto de um elemento "i"
    int buscar(int subset[], int i)
    {
        if(subset[i] == -1)
            return i;
        return buscar(subset, subset[i]);
    }

    // função para unir dois subconjuntos em um único subconjunto
    void unir(int subset[], int v1, int v2)
    {
        int v1_set = buscar(subset, v1);
        int v2_set = buscar(subset, v2);
        subset[v1_set] = v2_set;
    }

    /// função que roda o algoritmo de Kruskal
    void kruskal()
    {
        vector<Aresta> arvore;
        int size_arestas = arestas.size();

        // ordena as arestas pelo menor peso
        sort(arestas.begin(), arestas.end());

        // aloca memória para criar "V" subconjuntos
        int * subset = new int[V];

        // inicializa todos os subconjuntos como conjuntos de um único elemento
        memset(subset, -1, sizeof(int) * V);

        for(int i = 0; i < size_arestas; i++)
        {
            int v1 = buscar(subset, arestas[i].obterVertice1());
            int v2 = buscar(subset, arestas[i].obterVertice2());

            if(v1 != v2)
            {
                // se forem diferentes é porque NÃO forma ciclo, insere no vetor
                arvore.push_back(arestas[i]);
                unir(subset, v1, v2); // faz a união
            }
        }

        int size_arvore = arvore.size();
        R=0;
        // mostra as arestas selecionadas com seus respectivos pesos
        for(int i = 0; i < size_arvore; i++)
        {
            int v1 = arvore[i].obterVertice1();
            int v2 = arvore[i].obterVertice2();
//            cout << "(" << v1 << ", " << v2 << ") = " << arvore[i].obterPeso() << endl;
            R+=arvore[i].obterPeso();
        }
    }
    int getR(){
        return R;
    }
};

int main(int argc, char *argv[])
{
    int M,N;
    cin>>M>>N;
    while(M!=0 && N!=0 ){
        int peso = 0;
        Grafo g(M);
        for (int i = 0; i < N; ++i) {
            int v1,v2,p;
            cin>>v1>>v2>>p;
            g.adicionarAresta(v1,v2,p);
            peso+=p;
        }
        g.kruskal();
        peso = peso-g.getR();
        cout<<peso<<endl;
        cin>>M>>N;
    }

    return 0;
}
