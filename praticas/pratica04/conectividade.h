#ifndef CONECTIVIDADE_H
#define CONECTIVIDADE_H

typedef struct No {
    int vertice;
    struct No* prox;
} No;

typedef struct {
    int num_vertices;
    int num_arestas;
    No** adj;
} GrafoLista;

GrafoLista* criar_grafo(int n);
void adicionar_aresta(GrafoLista* g, int u, int v);
void liberar_grafo(GrafoLista* g);

void dfs_articulacoes(GrafoLista *g);
void detectar_pontes(GrafoLista *g);

#endif