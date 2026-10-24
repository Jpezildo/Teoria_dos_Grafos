#ifndef AGM_H
#define AGM_H

#include <limits.h>

#define INF INT_MAX


typedef struct NoAresta {
    int destino;
    int peso;
    struct NoAresta *prox;
} NoAresta;

typedef struct {
    NoAresta *cabeca;
} ListaAdjacencia;

typedef struct {
    int num_vertices;
    ListaAdjacencia *array;
} GrafoListaPonderado;


typedef struct {
    int u, v, peso;
} Aresta;


typedef struct {
    int *pai, *rank;
    int n;
} DSU;


typedef struct {
    int vertice;
    int chave;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade, tamanho;
    int *posicao; 
} MinHeap;


GrafoListaPonderado* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoListaPonderado *g, int origem, int destino, int peso);
void liberar_grafo(GrafoListaPonderado *g);


DSU* criar_dsu(int n);
int find(DSU *d, int x);
void unir(DSU *d, int x, int y);
void liberar_dsu(DSU *d);


int kruskal(Aresta *arestas, int num_arestas, int num_vertices);
int prim(GrafoListaPonderado *g, int origem);

#endif