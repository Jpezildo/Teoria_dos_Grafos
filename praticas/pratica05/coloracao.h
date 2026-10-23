#ifndef COLORACAO_H
#define COLORACAO_H

#include <stdbool.h>


typedef struct No {
    int destino;
    struct No* prox;
} No;


typedef struct GrafoLista {
    int num_vertices;
    No** lista_adj;
} GrafoLista;


GrafoLista* criar_grafo(int vertices);
void adicionar_aresta(GrafoLista* g, int origem, int destino);
void liberar_grafo(GrafoLista* g);


void coloracao_gulosa(GrafoLista *g, int *num_cores);
void coloracao_welsh_powell(GrafoLista *g, int *num_cores);
int eh_bipartido(GrafoLista *g);

#endif