#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H
#include "grafo.h"

typedef struct {
    int *dados;
    int topo, capacidade;
} Pilha;

// Funções da Pilha omitidas para brevidade (init, push, pop)

void dfs_recursiva(GrafoLista *g, int u, int *visitado);
int contar_componentes(GrafoLista *g);
int tem_ciclo(GrafoLista *g);

#endif