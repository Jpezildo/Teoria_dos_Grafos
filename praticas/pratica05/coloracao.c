#include <stdio.h>
#include <stdlib.h>
#include "coloracao.h"

typedef struct {
    int id;
    int grau;
} VerticeGrau;

GrafoLista* criar_grafo(int vertices) {
    GrafoLista* g = (GrafoLista*)malloc(sizeof(GrafoLista));
    g->num_vertices = vertices;
    g->lista_adj = (No**)malloc(vertices * sizeof(No*));
    for (int i = 0; i < vertices; i++) {
        g->lista_adj[i] = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoLista* g, int origem, int destino) {

    No* novo_no1 = (No*)malloc(sizeof(No));
    novo_no1->destino = destino;
    novo_no1->prox = g->lista_adj[origem];
    g->lista_adj[origem] = novo_no1;

    No* novo_no2 = (No*)malloc(sizeof(No));
    novo_no2->destino = origem;
    novo_no2->prox = g->lista_adj[destino];
    g->lista_adj[destino] = novo_no2;
}

void liberar_grafo(GrafoLista* g) {
    for (int i = 0; i < g->num_vertices; i++) {
        No* atual = g->lista_adj[i];
        while (atual != NULL) {
            No* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->lista_adj);
    free(g);
}

void coloracao_gulosa(GrafoLista *g, int *num_cores) {
    int V = g->num_vertices;
    int *resultado = (int*)malloc(V * sizeof(int));
    bool *disponivel = (bool*)malloc(V * sizeof(bool));


    for (int i = 0; i < V; i++) {
        resultado[i] = -1;
        disponivel[i] = true;
    }

    resultado[0] = 0;
    int max_cor = 0;


    for (int u = 1; u < V; u++) {

        No* atual = g->lista_adj[u];
        while (atual != NULL) {
            if (resultado[atual->destino] != -1) {
                disponivel[resultado[atual->destino]] = false;
            }
            atual = atual->prox;
        }


        int cor;
        for (cor = 0; cor < V; cor++) {
            if (disponivel[cor]) break;
        }

        resultado[u] = cor;
        if (cor > max_cor) max_cor = cor;

   
        atual = g->lista_adj[u];
        while (atual != NULL) {
            if (resultado[atual->destino] != -1) {
                disponivel[resultado[atual->destino]] = true;
            }
            atual = atual->prox;
        }
    }

    *num_cores = max_cor + 1;

    printf("\n[Coloracao Gulosa] Cores atribuidas:\n");
    for (int i = 0; i < V; i++) {
        printf("Vertice %d ---> Cor %d\n", i, resultado[i]);
    }

    free(resultado);
    free(disponivel);
}


int comparar_graus(const void *a, const void *b) {
    VerticeGrau *v1 = (VerticeGrau *)a;
    VerticeGrau *v2 = (VerticeGrau *)b;
    return v2->grau - v1->grau;
}

void coloracao_welsh_powell(GrafoLista *g, int *num_cores) {
    int V = g->num_vertices;
    VerticeGrau *vg = (VerticeGrau*)malloc(V * sizeof(VerticeGrau));
    int *resultado = (int*)malloc(V * sizeof(int));
    bool *disponivel = (bool*)malloc(V * sizeof(bool));

    for (int i = 0; i < V; i++) {
        vg[i].id = i;
        vg[i].grau = 0;
        resultado[i] = -1;
        disponivel[i] = true;

        No* atual = g->lista_adj[i];
        while (atual != NULL) {
            vg[i].grau++;
            atual = atual->prox;
        }
    }


    qsort(vg, V, sizeof(VerticeGrau), comparar_graus);

    int max_cor = 0;

    // Aplica a estratégia gulosa na ordem estabelecida
    for (int i = 0; i < V; i++) {
        int u = vg[i].id;

        No* atual = g->lista_adj[u];
        while (atual != NULL) {
            if (resultado[atual->destino] != -1) {
                disponivel[resultado[atual->destino]] = false;
            }
            atual = atual->prox;
        }

        int cor;
        for (cor = 0; cor < V; cor++) {
            if (disponivel[cor]) break;
        }

        resultado[u] = cor;
        if (cor > max_cor) max_cor = cor;

        atual = g->lista_adj[u];
        while (atual != NULL) {
            if (resultado[atual->destino] != -1) {
                disponivel[resultado[atual->destino]] = true;
            }
            atual = atual->prox;
        }
    }

    *num_cores = max_cor + 1;

    printf("\n[Welsh-Powell] Cores atribuidas (processado por grau):\n");
    for (int i = 0; i < V; i++) {
        printf("Vertice %d (Grau %d) ---> Cor %d\n", vg[i].id, vg[i].grau, resultado[vg[i].id]);
    }

    free(vg);
    free(resultado);
    free(disponivel);
}

int eh_bipartido(GrafoLista *g) {
    int V = g->num_vertices;
    int *cor = (int*)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) cor[i] = -1;

    int *fila = (int*)malloc(V * sizeof(int));
    
    for (int i = 0; i < V; i++) {
        if (cor[i] == -1) {
            int inicio = 0, fim = 0;
            cor[i] = 1;
            fila[fim++] = i;

            while (inicio < fim) {
                int u = fila[inicio++];
                No* atual = g->lista_adj[u];
                
                while (atual != NULL) {
                    int v = atual->destino;
                    
                
                    if (cor[v] == cor[u]) {
                        free(cor);
                        free(fila);
                        return 0; 
                    }
                 
                    if (cor[v] == -1) {
                        cor[v] = 1 - cor[u];
                        fila[fim++] = v;
                    }
                    atual = atual->prox;
                }
            }
        }
    }
    
    free(cor);
    free(fila);
    return 1; 
}