#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "dag.h"


void adicionar_aresta_direcionada(GrafoLista *g, int u, int v) {
    No *novo = (No*)malloc(sizeof(No));
    novo->vertice = v;
    novo->prox = g->adj[u];
    g->adj[u] = novo;
}

int main() {
    int num_vertices = 6;
    GrafoLista *g = criar_grafo(num_vertices);


    adicionar_aresta_direcionada(g, 5, 2);
    adicionar_aresta_direcionada(g, 5, 0);
    adicionar_aresta_direcionada(g, 4, 0);
    adicionar_aresta_direcionada(g, 4, 1);
    adicionar_aresta_direcionada(g, 2, 3);
    adicionar_aresta_direcionada(g, 3, 1);

    printf("=== VERIFICACAO DE DAG ===\n");
    printf("O grafo eh um DAG? %s\n\n", eh_dag(g) ? "Sim" : "Nao");

    printf("=== ORDENACAO TOPOLOGICA (KAHN) ===\n");
    int tam_kahn = 0;
    int *res_kahn = ordenacao_topologica_kahn(g, &tam_kahn);
    if (res_kahn) {
        printf("Ordem: ");
        for (int i = 0; i < tam_kahn; i++) printf("%d ", res_kahn[i]);
        printf("\n");
        free(res_kahn);
    } else {
        printf("Ciclo detectado!\n");
    }
    printf("\n");

    printf("=== ORDENACAO TOPOLOGICA (DFS) ===\n");
    int tam_dfs = 0;
    int *res_dfs = ordenacao_topologica_dfs(g, &tam_dfs);
    if (res_dfs) {
        printf("Ordem: ");
        for (int i = 0; i < tam_dfs; i++) printf("%d ", res_dfs[i]);
        printf("\n");
        free(res_dfs);
    } else {
        printf("Ciclo detectado!\n");
    }

    liberar_grafo(g);
    return 0;
}