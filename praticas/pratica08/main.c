#include <stdio.h>
#include <stdlib.h>
#include "agm.h"

int main() {
    int V = 5;
    int E = 7;

    Aresta arestas[] = {
        {0, 1, 2},
        {0, 3, 6},
        {1, 2, 3},
        {1, 3, 8},
        {1, 4, 5},
        {2, 4, 7},
        {3, 4, 9}
    };


    GrafoListaPonderado *g = criar_grafo(V);
    adicionar_aresta(g, 0, 1, 2); adicionar_aresta(g, 1, 0, 2);
    adicionar_aresta(g, 0, 3, 6); adicionar_aresta(g, 3, 0, 6);
    adicionar_aresta(g, 1, 2, 3); adicionar_aresta(g, 2, 1, 3);
    adicionar_aresta(g, 1, 3, 8); adicionar_aresta(g, 3, 1, 8);
    adicionar_aresta(g, 1, 4, 5); adicionar_aresta(g, 4, 1, 5);
    adicionar_aresta(g, 2, 4, 7); adicionar_aresta(g, 4, 2, 7);
    adicionar_aresta(g, 3, 4, 9); adicionar_aresta(g, 4, 3, 9);

    printf("Testando Kruskal\n");
    int peso_kruskal = kruskal(arestas, E, V);
    printf("Peso total da AGM: %d\n\n", peso_kruskal);

    printf("Testando Prim \n");
    int peso_prim = prim(g, 0);
    printf("Peso total da AGM: %d\n", peso_prim);

    liberar_grafo(g);
    return 0;
}