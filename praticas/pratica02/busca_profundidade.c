#include <stdio.h>
#include <stdlib.h>
#include "busca_profundidade.h"

void dfs_recursiva(GrafoLista *g, int u, int *visitado) {
    visitado[u] = 1;
    No *adj = g->adj[u];
    
    while (adj != NULL) {
        int v = adj->vertice;
        if (!visitado[v]) {
            dfs_recursiva(g, v, visitado);
        }
        adj = adj->prox;
    }
}

int contar_componentes(GrafoLista *g) {
    int *visitado = (int*)calloc(g->num_vertices, sizeof(int));
    int componentes = 0;
    
    for (int i = 0; i < g->num_vertices; i++) {
        if (!visitado[i]) {
            componentes++;
            dfs_recursiva(g, i, visitado);
        }
    }
    free(visitado);
    return componentes;
}

// Função auxiliar para rastrear o pai e evitar falsos positivos em grafos não-direcionados
int dfs_ciclo(GrafoLista *g, int u, int pai, int *visitado) {
    visitado[u] = 1;
    No *adj = g->adj[u];
    
    while (adj != NULL) {
        int v = adj->vertice;
        if (!visitado[v]) {
            if (dfs_ciclo(g, v, u, visitado)) return 1;
        } else if (v != pai) {
            return 1; // Achou um vizinho já visitado que não é o pai
        }
        adj = adj->prox;
    }
    return 0;
}

int tem_ciclo(GrafoLista *g) {
    int *visitado = (int*)calloc(g->num_vertices, sizeof(int));
    for (int i = 0; i < g->num_vertices; i++) {
        if (!visitado[i]) {
            if (dfs_ciclo(g, i, -1, visitado)) {
                free(visitado);
                return 1;
            }
        }
    }
    free(visitado);
    return 0;
}