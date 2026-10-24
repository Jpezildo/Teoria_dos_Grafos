#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

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


GrafoListaPonderado* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoListaPonderado *g, int origem, int destino, int peso);
void liberar_grafo(GrafoListaPonderado *g);


int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_ciclo_negativo(int vertice_ciclo, int *pred, int num_vertices);

#endif