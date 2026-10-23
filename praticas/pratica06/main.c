#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

int main() {
    int V = 6; 
    GrafoListaPonderado *g = criar_grafo(V);

   
    adicionar_aresta(g, 0, 1, 4);
    adicionar_aresta(g, 1, 0, 4);
    
    
    adicionar_aresta(g, 0, 2, 2);
    adicionar_aresta(g, 2, 0, 2);
    
   
    adicionar_aresta(g, 1, 2, 1);
    adicionar_aresta(g, 2, 1, 1);
    
   
    adicionar_aresta(g, 1, 3, 5);
    adicionar_aresta(g, 3, 1, 5);
    
    
    adicionar_aresta(g, 1, 4, 8);
    adicionar_aresta(g, 4, 1, 8);
    
   
    adicionar_aresta(g, 2, 3, 4);
    adicionar_aresta(g, 3, 2, 4);
    
    
    adicionar_aresta(g, 2, 4, 10);
    adicionar_aresta(g, 4, 2, 10);
    
   
    adicionar_aresta(g, 3, 4, 2);
    adicionar_aresta(g, 4, 3, 2);
    
    
    adicionar_aresta(g, 3, 5, 1);
    adicionar_aresta(g, 5, 3, 1);
    
  
    adicionar_aresta(g, 4, 5, 3);
    adicionar_aresta(g, 5, 4, 3);

    int dist[V];
    int pred[V];
    int origem = 0; 

    dijkstra(g, origem, dist, pred);

    char nomes[] = {'A', 'B', 'C', 'D', 'E', 'F'};

    printf("Distancias a partir da origem %c:\n", nomes[origem]);
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INF) {
            printf("Vertice %c \t Distancia: INF\n", nomes[i]);
        } else {
            printf("Vertice %c \t Distancia: %d\n", nomes[i], dist[i]);
        }
    }

    printf("\nCaminhos reconstruidos:\n");
    for (int i = 0; i < V; i++) {
        printf("Para %c: ", nomes[i]);
        
        int atual = i;
        if (i == origem) {
            printf("%c\n", nomes[origem]);
        } else if (pred[i] == -1) {
            printf("Inacessivel\n");
        } else {
            int caminho[V];
            int cont = 0;
            while (atual != -1) {
                caminho[cont++] = atual;
                atual = pred[atual];
            }
            for (int j = cont - 1; j >= 0; j--) {
                printf("%c%s", nomes[caminho[j]], (j > 0) ? " -> " : "");
            }
            printf("\n");
        }
    }

    liberar_grafo(g);
    return 0;
}