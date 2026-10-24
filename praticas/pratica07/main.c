#include <stdio.h>
#include <stdlib.h>
#include "bellman_ford.h"

int main() {
    int V = 4;
    GrafoListaPonderado *g = criar_grafo(V);

  
    adicionar_aresta(g, 0, 1, 4);
    adicionar_aresta(g, 0, 2, 5);
    adicionar_aresta(g, 1, 2, -2);
    adicionar_aresta(g, 2, 3, 3);

    int dist[V];
    int pred[V];
    int origem = 0;

    printf("Teste 1: Grafo sem ciclo negativo \n");
    if (bellman_ford(g, origem, dist, pred)) {
        printf("Distancias a partir da origem %d:\n", origem);
        for (int i = 0; i < V; ++i) {
            if (dist[i] == INF) printf("Vertice %d \t Distancia: INF\n", i);
            else printf("Vertice %d \t Distancia: %d\n", i, dist[i]);
        }
    }

    adicionar_aresta(g, 3, 1, -5);

    printf("\n--- Teste 2: Grafo com ciclo negativo ---\n");
    bellman_ford(g, origem, dist, pred);

    liberar_grafo(g);
    return 0;
}