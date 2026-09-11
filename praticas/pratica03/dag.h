#ifndef DAG_H
#define DAG_H
#include "grafo.h"

int eh_dag(GrafoLista *g);
int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho);
int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho);

#endif