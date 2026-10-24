#include <stdio.h>
#include <stdlib.h>
#include "bellman_ford.h"

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

void reconstruir_ciclo_negativo(int vertice_ciclo, int *pred, int num_vertices) {
    int *ciclo = (int *)malloc(num_vertices * sizeof(int));
    int atual = vertice_ciclo;


    for (int i = 0; i < num_vertices; i++) {
        atual = pred[atual];
    }

    int inicio_ciclo = atual;
    int cont = 0;


    do {
        ciclo[cont++] = atual;
        atual = pred[atual];
    } while (atual != inicio_ciclo);
    
    ciclo[cont++] = inicio_ciclo; 

    printf("Ciclo negativo detectado: ");

    for (int i = cont - 1; i >= 0; i--) {
        printf("%d%s", ciclo[i], (i > 0) ? " -> " : "\n");
    }

    free(ciclo);
}

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    int V = g->num_vertices;

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        pred[i] = -1;
    }
    dist[origem] = 0;


    for (int i = 1; i < V; i++) {
        for (int u = 0; u < V; u++) {
            NoAresta *adj = g->array[u].cabeca;
            while (adj != NULL) {
                int v = adj->destino;
                int peso = adj->peso;
                
          
                if (dist[u] != INF && dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                    pred[v] = u;
                }
                adj = adj->prox;
            }
        }
    }

  
    for (int u = 0; u < V; u++) {
        NoAresta *adj = g->array[u].cabeca;
        while (adj != NULL) {
            int v = adj->destino;
            int peso = adj->peso;
            
            if (dist[u] != INF && dist[u] + peso < dist[v]) {
                pred[v] = u; 
                reconstruir_ciclo_negativo(v, pred, V);
                return 0; 
            }
            adj = adj->prox;
        }
    }

    return 1; 
}