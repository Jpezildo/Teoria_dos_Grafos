#include <stdio.h>
#include "grafo_matriz.h"
#include "grafo_lista.h"

int main() {
    printf("Matriz de Adjacencia\n");
    GrafoMatriz *gm = criar_grafo_matriz(4);
    inserir_aresta_matriz(gm, 0, 1);
    inserir_aresta_matriz(gm, 1, 2);
    printf("Grau do vertice 1: %d\n", grau_matriz(gm, 1));
    printf("0 e 1 sao adjacentes? %s\n", sao_adjacentes_matriz(gm, 0, 1) ? "Sim" : "Nao");
    remover_aresta_matriz(gm, 0, 1);
    printf("0 e 1 sao adjacentes apos remocao? %s\n", sao_adjacentes_matriz(gm, 0, 1) ? "Sim" : "Nao");
    liberar_grafo_matriz(gm);

    printf("\nLista de Adjacencia \n");
    GrafoLista *gl = criar_grafo_lista(4);
    inserir_aresta_lista(gl, 0, 1);
    inserir_aresta_lista(gl, 1, 2);
    printf("Grau do vertice 1: %d\n", grau_lista(gl, 1));
    printf("0 e 1 sao adjacentes? %s\n", sao_adjacentes_lista(gl, 0, 1) ? "Sim" : "Nao");
    remover_aresta_lista(gl, 0, 1);
    printf("0 e 1 sao adjacentes apos remocao? %s\n", sao_adjacentes_lista(gl, 0, 1) ? "Sim" : "Nao");
    liberar_grafo_lista(gl);

    return 0;
}