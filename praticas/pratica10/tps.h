#ifndef TPS_H
#define TPS_H

#include "hamiltoniano.h"

int **grafo_para_tsp(const Grafo *g);
void liberar_matriz_tsp(int **dist, int n);

int tsp_forca_bruta(int n, int **dist, int *melhor_rota);
int tsp_vizinho_mais_proximo(int n, int **dist, int *rota);
int tsp_insercao(int n, int **dist, int *rota);

#endif