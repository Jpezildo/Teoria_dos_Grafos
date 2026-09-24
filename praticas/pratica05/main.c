#include <stdio.h>
#include "coloracao.h"

int main() {
  
    int num_vertices = 5;
    GrafoLista* g = criar_grafo(num_vertices);

    
    adicionar_aresta(g, 0, 1);
    adicionar_aresta(g, 0, 2);
    adicionar_aresta(g, 0, 3);
    adicionar_aresta(g, 0, 4);
    
    printf("--- Testando Grafo 1 (Estrela) ---\n");
    int num_cores_gulosa = 0;
    coloracao_gulosa(g, &num_cores_gulosa);
    printf("Total de cores (Gulosa): %d\n", num_cores_gulosa);

    int num_cores_wp = 0;
    coloracao_welsh_powell(g, &num_cores_wp);
    printf("Total de cores (Welsh-Powell): %d\n", num_cores_wp);

    if (eh_bipartido(g)) {
        printf("\nO grafo eh Bipartido! (Numero cromatico <= 2)\n");
    } else {
        printf("\nO grafo NAO eh Bipartido!\n");
    }

   
    adicionar_aresta(g, 1, 2);
    
    printf("\n--- Testando Grafo 2 (Estrela + Aresta 1-2) ---\n");
    if (eh_bipartido(g)) {
        printf("O grafo eh Bipartido! (Numero cromatico <= 2)\n");
    } else {
        printf("O grafo NAO eh Bipartido! (Foi encontrado um ciclo impar)\n");
    }

    liberar_grafo(g);
    return 0;
}