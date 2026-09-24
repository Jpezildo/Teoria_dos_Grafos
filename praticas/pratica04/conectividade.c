#include <stdio.h>
#include <stdlib.h>
#include "conectividade.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

GrafoLista* criar_grafo(int n) {
    GrafoLista* g = (GrafoLista*) malloc(sizeof(GrafoLista));
    g->num_vertices = n;
    g->num_arestas = 0;
    g->adj = (No**) calloc(n, sizeof(No*));
    return g;
}

void adicionar_aresta(GrafoLista* g, int u, int v) {
    No* novo_u = (No*) malloc(sizeof(No));
    novo_u->vertice = v;
    novo_u->prox = g->adj[u];
    g->adj[u] = novo_u;

    No* novo_v = (No*) malloc(sizeof(No));
    novo_v->vertice = u;
    novo_v->prox = g->adj[v];
    g->adj[v] = novo_v;

    g->num_arestas++;
}

void liberar_grafo(GrafoLista* g) {
    for (int i = 0; i < g->num_vertices; i++) {
        No* atual = g->adj[i];
        while (atual) {
            No* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->adj);
    free(g);
}


void tarjan_articulacoes_dfs(GrafoLista* g, int u, int p, int* tempo, int* descoberta, int* low, int* eh_articulacao) {
    int filhos = 0;
    descoberta[u] = low[u] = ++(*tempo);

    No* atual = g->adj[u];
    while (atual != NULL) {
        int v = atual->vertice;
        
        if (v == p) {
            atual = atual->prox;
            continue;
        }
        
        if (descoberta[v]) { 
            low[u] = MIN(low[u], descoberta[v]);
        } else { 
            filhos++;
            tarjan_articulacoes_dfs(g, v, u, tempo, descoberta, low, eh_articulacao);
            low[u] = MIN(low[u], low[v]);


            if (p != -1 && low[v] >= descoberta[u]) {
                eh_articulacao[u] = 1;
            }
        }
        atual = atual->prox;
    }
    
    if (p == -1 && filhos > 1) {
        eh_articulacao[u] = 1;
    }
}

void dfs_articulacoes(GrafoLista *g) {
    int n = g->num_vertices;
    int *descoberta = (int*) calloc(n, sizeof(int));
    int *low = (int*) calloc(n, sizeof(int));
    int *eh_articulacao = (int*) calloc(n, sizeof(int));
    int tempo = 0;

    for (int i = 0; i < n; i++) {
        if (!descoberta[i]) {
            tarjan_articulacoes_dfs(g, i, -1, &tempo, descoberta, low, eh_articulacao);
        }
    }

    printf("Vertices de corte (Articulacoes): ");
    int encontrou = 0;
    for (int i = 0; i < n; i++) {
        if (eh_articulacao[i]) {
            printf("%d ", i);
            encontrou = 1;
        }
    }
    if (!encontrou) printf("Nenhum");
    printf("\n");

    free(descoberta); free(low); free(eh_articulacao);
}


void tarjan_pontes_dfs(GrafoLista* g, int u, int p, int* tempo, int* descoberta, int* low) {
    descoberta[u] = low[u] = ++(*tempo);

    No* atual = g->adj[u];
    while (atual != NULL) {
        int v = atual->vertice;
        
        if (v == p) {
            atual = atual->prox;
            continue;
        }
        
        if (descoberta[v]) { 
            low[u] = MIN(low[u], descoberta[v]);
        } else { // Aresta de árvore
            tarjan_pontes_dfs(g, v, u, tempo, descoberta, low);
            low[u] = MIN(low[u], low[v]);

            if (low[v] > descoberta[u]) {
                printf("(%d, %d) ", u, v);
            }
        }
        atual = atual->prox;
    }
}

void detectar_pontes(GrafoLista *g) {
    int n = g->num_vertices;
    int *descoberta = (int*) calloc(n, sizeof(int));
    int *low = (int*) calloc(n, sizeof(int));
    int tempo = 0;

    printf("Pontes (Arestas de corte): ");
    for (int i = 0; i < n; i++) {
        if (!descoberta[i]) {
            tarjan_pontes_dfs(g, i, -1, &tempo, descoberta, low);
        }
    }
    printf("\n");

    free(descoberta); free(low);
}