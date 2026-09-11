#include <stdio.h>
#include <stdlib.h>
#include "dag.h"

int* calcular_graus_entrada(GrafoLista *g) {
    int *grau = (int*)calloc(g->num_vertices, sizeof(int));
    for (int u = 0; u < g->num_vertices; u++) {
        No *adj = g->adj[u];
        while (adj != NULL) {
            grau[adj->vertice]++;
            adj = adj->prox;
        }
    }
    return grau;
}

int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho) {
    int *grau = calcular_graus_entrada(g);
    int *fila = (int*)malloc(g->num_vertices * sizeof(int));
    int inicio = 0, fim = 0;

    for (int i = 0; i < g->num_vertices; i++) {
        if (grau[i] == 0) {
            fila[fim++] = i;
        }
    }

    int *resultado = (int*)malloc(g->num_vertices * sizeof(int));
    int count = 0;

    while (inicio < fim) {
        int u = fila[inicio++];
        resultado[count++] = u;

        No *adj = g->adj[u];
        while (adj != NULL) {
            int v = adj->vertice;
            grau[v]--;
            if (grau[v] == 0) {
                fila[fim++] = v;
            }
            adj = adj->prox;
        }
    }

    free(grau);
    free(fila);

    if (count != g->num_vertices) {
        free(resultado);
        *tamanho = 0;
        return NULL; 
    }

    *tamanho = count;
    return resultado;
}

void dfs_topo(GrafoLista *g, int u, int *estado, int *pilha, int *topo, int *tem_ciclo) {
    estado[u] = 1; 
    No *adj = g->adj[u];
    
    while (adj != NULL) {
        int v = adj->vertice;
        if (estado[v] == 1) {
            *tem_ciclo = 1;
        } else if (estado[v] == 0) {
            dfs_topo(g, v, estado, pilha, topo, tem_ciclo);
        }
        adj = adj->prox;
    }
    estado[u] = 2; 
    pilha[(*topo)++] = u;
}

int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho) {
    int *estado = (int*)calloc(g->num_vertices, sizeof(int)); 
    int *pilha = (int*)malloc(g->num_vertices * sizeof(int));
    int topo = 0;
    int tem_ciclo = 0;

    for (int i = 0; i < g->num_vertices; i++) {
        if (estado[i] == 0) {
            dfs_topo(g, i, estado, pilha, &topo, &tem_ciclo);
        }
    }

    free(estado);

    if (tem_ciclo) {
        free(pilha);
        *tamanho = 0;
        return NULL;
    }

    int *resultado = (int*)malloc(g->num_vertices * sizeof(int));
    for (int i = 0; i < g->num_vertices; i++) {
        resultado[i] = pilha[topo - 1 - i];
    }

    free(pilha);
    *tamanho = g->num_vertices;
    return resultado;
}

int eh_dag(GrafoLista *g) {
    int tamanho = 0;
    int *res = ordenacao_topologica_kahn(g, &tamanho);
    if (res != NULL) {
        free(res);
        return 1;
    }
    return 0;
}