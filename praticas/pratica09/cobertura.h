#ifndef COBERTURA_H
#define COBERTURA_H

#define MAX_VERTICES 15 

typedef struct {
    int u;
    int v;
} Aresta;

int eh_cobertura(Aresta *a, int *cobertura, int m);
void cobertura_minima_bt(Aresta *a, int n, int m, int *melhor_cobertura, int *tamanho_minimo);
void cobertura_gulosa(Aresta *a, int n, int m, int *cobertura_resultado);

#endif