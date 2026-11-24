#ifndef HAMILTONIANO_H
#define HAMILTONIANO_H

#include <stdbool.h>

typedef struct {
    int n;
    int **adj;
} Grafo;

Grafo *criar_grafo(int n);
void liberar_grafo(Grafo *g);
void adicionar_aresta(Grafo *g, int u, int v);

bool encontrar_caminho_hamiltoniano_bt(const Grafo *g, int *caminho);
bool encontrar_ciclo_hamiltoniano_bt(const Grafo *g, int *ciclo);

#endif