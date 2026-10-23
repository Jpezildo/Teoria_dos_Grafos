#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

GrafoListaPonderado* criar_grafo(int num_vertices) {
    GrafoListaPonderado *g = (GrafoListaPonderado*) malloc(sizeof(GrafoListaPonderado));
    g->num_vertices = num_vertices;
    g->array = (ListaAdjacencia*) malloc(num_vertices * sizeof(ListaAdjacencia));
    for (int i = 0; i < num_vertices; i++) {
        g->array[i].cabeca = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoListaPonderado *g, int origem, int destino, int peso) {
    NoAresta *novo_no = (NoAresta*) malloc(sizeof(NoAresta));
    novo_no->destino = destino;
    novo_no->peso = peso;
    novo_no->prox = g->array[origem].cabeca;
    g->array[origem].cabeca = novo_no;
}

void liberar_grafo(GrafoListaPonderado *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        NoAresta *atual = g->array[i].cabeca;
        while (atual != NULL) {
            NoAresta *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->array);
    free(g);
}

MinHeap* criar_min_heap(int capacidade) {
    MinHeap *h = (MinHeap*) malloc(sizeof(MinHeap));
    h->capacidade = capacidade;
    h->tamanho = 0;
    h->dados = (NoHeap*) malloc(capacidade * sizeof(NoHeap));
    h->posicao = (int*) malloc(capacidade * sizeof(int));
    return h;
}

void liberar_min_heap(MinHeap *h) {
    free(h->dados);
    free(h->posicao);
    free(h);
}

void trocar_nos(MinHeap *h, int i, int j) {
    NoHeap temp = h->dados[i];
    h->dados[i] = h->dados[j];
    h->dados[j] = temp;
    h->posicao[h->dados[i].vertice] = i;
    h->posicao[h->dados[j].vertice] = j;
}

void min_heapify(MinHeap *h, int idx) {
    int menor = idx;
    int esq = 2 * idx + 1;
    int dir = 2 * idx + 2;

    if (esq < h->tamanho && h->dados[esq].distancia < h->dados[menor].distancia)
        menor = esq;
    if (dir < h->tamanho && h->dados[dir].distancia < h->dados[menor].distancia)
        menor = dir;

    if (menor != idx) {
        trocar_nos(h, menor, idx);
        min_heapify(h, menor);
    }
}

void extrair_minimo(MinHeap *h, int *vertice_min, int *dist_min) {
    if (h->tamanho == 0) return;

    NoHeap raiz = h->dados[0];
    NoHeap ultimo = h->dados[h->tamanho - 1];

    h->dados[0] = ultimo;
    h->posicao[ultimo.vertice] = 0;
    h->posicao[raiz.vertice] = -1; 
    h->tamanho--;

    min_heapify(h, 0);

    *vertice_min = raiz.vertice;
    *dist_min = raiz.distancia;
}

void diminuir_chave(MinHeap *h, int vertice, int distancia) {
    int i = h->posicao[vertice];
    if (i == -1) return; 

    h->dados[i].distancia = distancia;
    while (i != 0 && h->dados[i].distancia < h->dados[(i - 1) / 2].distancia) {
        trocar_nos(h, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    int V = g->num_vertices;
    MinHeap *h = criar_min_heap(V);

    for (int v = 0; v < V; v++) {
        dist[v] = INF;
        pred[v] = -1;
        h->dados[v].vertice = v;
        h->dados[v].distancia = INF;
        h->posicao[v] = v;
    }

    h->tamanho = V;
    dist[origem] = 0;
    diminuir_chave(h, origem, dist[origem]);

    while (h->tamanho > 0) {
        int u, d_u;
        extrair_minimo(h, &u, &d_u);

        if (d_u == INF) break; 

        NoAresta *adj = g->array[u].cabeca;
        while (adj != NULL) {
            int v = adj->destino;
            int peso = adj->peso;

            if (h->posicao[v] != -1 && dist[u] != INF && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pred[v] = u;
                diminuir_chave(h, v, dist[v]);
            }
            adj = adj->prox;
        }
    }
    liberar_min_heap(h);
}

void reconstruir_caminho(int origem, int destino, int *pred) {
    if (origem == destino) {
        printf("%d", origem);
        return;
    }
    if (pred[destino] == -1) {
        printf("Nenhum caminho de %d para %d", origem, destino);
        return;
    }
    reconstruir_caminho(origem, pred[destino], pred);
    printf(" -> %d", destino);
}