#ifndef GRAFO_H
#define GRAFO_H

typedef struct No {
    int vertice;
    struct No *prox;
} No;

typedef struct {
    int num_vertices;
    No **adj;
} GrafoLista;

GrafoLista* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoLista *g, int u, int v);
void liberar_grafo(GrafoLista *g);

#endif