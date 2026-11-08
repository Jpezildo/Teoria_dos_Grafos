#include <stdio.h>
#include <stdlib.h>
#include "agm.h"


GrafoListaPonderado* criar_grafo(int num_vertices) {
    GrafoListaPonderado *g = (GrafoListaPonderado*) malloc(sizeof(GrafoListaPonderado));
    g->num_vertices = num_vertices;
    g->array = (ListaAdjacencia*) malloc(num_vertices * sizeof(ListaAdjacencia));
    for (int i = 0; i < num_vertices; i++) g->array[i].cabeca = NULL;
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


DSU* criar_dsu(int n) {
    DSU *d = (DSU*) malloc(sizeof(DSU));
    d->n = n;
    d->pai = (int*) malloc(n * sizeof(int));
    d->rank = (int*) calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) d->pai[i] = i;
    return d;
}

int find(DSU *d, int x) {
    if (d->pai[x] != x) {
        d->pai[x] = find(d, d->pai[x]);
    }
    return d->pai[x];
}

void unir(DSU *d, int x, int y) {
    int raizX = find(d, x);
    int raizY = find(d, y);

    if (raizX != raizY) {
        if (d->rank[raizX] < d->rank[raizY]) {
            d->pai[raizX] = raizY;
        } else if (d->rank[raizX] > d->rank[raizY]) {
            d->pai[raizY] = raizX;
        } else {
            d->pai[raizY] = raizX;
            d->rank[raizX]++;
        }
    }
}

void liberar_dsu(DSU *d) {
    free(d->pai);
    free(d->rank);
    free(d);
}


int comparar_arestas(const void *a, const void *b) {
    Aresta *a1 = (Aresta *)a;
    Aresta *a2 = (Aresta *)b;
    return a1->peso - a2->peso;
}

int kruskal(Aresta *arestas, int num_arestas, int num_vertices) {
    int peso_mst = 0;
    int arestas_adicionadas = 0;
    DSU *d = criar_dsu(num_vertices);

    qsort(arestas, num_arestas, sizeof(Aresta), comparar_arestas);

    printf("Arestas selecionadas (Kruskal):\n");
    for (int i = 0; i < num_arestas && arestas_adicionadas < num_vertices - 1; i++) {
        int u = arestas[i].u;
        int v = arestas[i].v;
        int peso = arestas[i].peso;

        if (find(d, u) != find(d, v)) {
            unir(d, u, v);
            peso_mst += peso;
            arestas_adicionadas++;
            printf("%d - %d \tPeso: %d\n", u, v, peso);
        }
    }

    liberar_dsu(d);
    return peso_mst;
}


MinHeap* criar_min_heap(int capacidade) {
    MinHeap *h = (MinHeap*) malloc(sizeof(MinHeap));
    h->capacidade = capacidade;
    h->tamanho = 0;
    h->dados = (NoHeap*) malloc(capacidade * sizeof(NoHeap));
    h->posicao = (int*) malloc(capacidade * sizeof(int));
    return h;
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

    if (esq < h->tamanho && h->dados[esq].chave < h->dados[menor].chave) menor = esq;
    if (dir < h->tamanho && h->dados[dir].chave < h->dados[menor].chave) menor = dir;

    if (menor != idx) {
        trocar_nos(h, menor, idx);
        min_heapify(h, menor);
    }
}

void extrair_minimo(MinHeap *h, int *vertice_min, int *chave_min) {
    if (h->tamanho == 0) return;

    NoHeap raiz = h->dados[0];
    NoHeap ultimo = h->dados[h->tamanho - 1];

    h->dados[0] = ultimo;
    h->posicao[ultimo.vertice] = 0;
    h->posicao[raiz.vertice] = -1;
    h->tamanho--;

    min_heapify(h, 0);

    *vertice_min = raiz.vertice;
    *chave_min = raiz.chave;
}

void diminuir_chave(MinHeap *h, int vertice, int chave) {
    int i = h->posicao[vertice];
    if (i == -1) return;

    h->dados[i].chave = chave;
    while (i != 0 && h->dados[i].chave < h->dados[(i - 1) / 2].chave) {
        trocar_nos(h, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}


int prim(GrafoListaPonderado *g, int origem) {
    int V = g->num_vertices;
    int peso_mst = 0;
    int chaves[V];
    int pred[V];
    MinHeap *h = criar_min_heap(V);

    for (int v = 0; v < V; v++) {
        chaves[v] = INF;
        pred[v] = -1;
        h->dados[v].vertice = v;
        h->dados[v].chave = INF;
        h->posicao[v] = v;
    }

    h->tamanho = V;
    chaves[origem] = 0;
    diminuir_chave(h, origem, chaves[origem]);

    printf("Arestas selecionadas (Prim):\n");
    while (h->tamanho > 0) {
        int u, chave_u;
        extrair_minimo(h, &u, &chave_u);

        if (chave_u == INF) break;

        if (pred[u] != -1) {
            peso_mst += chave_u;
            printf("%d - %d \tPeso: %d\n", pred[u], u, chave_u);
        }

        NoAresta *adj = g->array[u].cabeca;
        while (adj != NULL) {
            int v = adj->destino;
            int peso = adj->peso;

    
            if (h->posicao[v] != -1 && peso < chaves[v]) {
                chaves[v] = peso;
                pred[v] = u;
                diminuir_chave(h, v, chaves[v]);
            }
            adj = adj->prox;
        }
    }

    free(h->dados);
    free(h->posicao);
    free(h);
    return peso_mst;
}