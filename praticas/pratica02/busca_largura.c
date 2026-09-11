#include <stdio.h>
#include <stdlib.h>
#include "busca_largura.h"

Fila* criar_fila(int capacidade) {
    Fila *f = (Fila*)malloc(sizeof(Fila));
    f->dados = (int*)malloc(capacidade * sizeof(int));
    f->capacidade = capacidade;
    f->inicio = 0;
    f->fim = -1;
    f->tamanho = 0;
    return f;
}

void enfileirar(Fila *f, int valor) {
    if (f->tamanho == f->capacidade) return;
    f->fim = (f->fim + 1) % f->capacidade;
    f->dados[f->fim] = valor;
    f->tamanho++;
}

int desenfileirar(Fila *f) {
    if (f->tamanho == 0) return -1;
    int valor = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;
    return valor;
}

void liberar_fila(Fila *f) {
    free(f->dados);
    free(f);
}

void bfs(GrafoLista *g, int origem, int *dist, int *pred) {
    Fila *f = criar_fila(g->num_vertices);
    for (int i = 0; i < g->num_vertices; i++) {
        dist[i] = -1;
        pred[i] = -1;
    }
    
    dist[origem] = 0;
    enfileirar(f, origem);
    
    while (f->tamanho > 0) {
        int u = desenfileirar(f);
        No *adj = g->adj[u];
        
        while (adj != NULL) {
            int v = adj->vertice;
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                pred[v] = u;
                enfileirar(f, v);
            }
            adj = adj->prox;
        }
    }
    liberar_fila(f);
}

int eh_bipartido(GrafoLista *g) {
    int *cor = (int*)malloc(g->num_vertices * sizeof(int));
    for (int i = 0; i < g->num_vertices; i++) cor[i] = -1;
    
    for (int i = 0; i < g->num_vertices; i++) {
        if (cor[i] != -1) continue;
        
        Fila *f = criar_fila(g->num_vertices);
        cor[i] = 0;
        enfileirar(f, i);
        
        while (f->tamanho > 0) {
            int u = desenfileirar(f);
            No *adj = g->adj[u];
            
            while (adj != NULL) {
                int v = adj->vertice;
                if (cor[v] == -1) {
                    cor[v] = 1 - cor[u];
                    enfileirar(f, v);
                } else if (cor[v] == cor[u]) {
                    liberar_fila(f);
                    free(cor);
                    return 0; // Não é bipartido
                }
                adj = adj->prox;
            }
        }
        liberar_fila(f);
    }
    free(cor);
    return 1; // É bipartido
}