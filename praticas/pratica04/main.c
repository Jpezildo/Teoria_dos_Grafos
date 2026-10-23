#include <stdio.h>
#include "conectividade.h"
#include "planaridade.h"

int main() {
    printf("Conectividade e Planaridade\n\n");


    GrafoLista* g1 = criar_grafo(5);
  
    adicionar_aresta(g1, 0, 1);
    adicionar_aresta(g1, 0, 3);
    adicionar_aresta(g1, 1, 4);
    adicionar_aresta(g1, 3, 4);
    adicionar_aresta(g1, 1, 2); 

    printf("Teste 1: Grafo de Conectividade\n");
    dfs_articulacoes(g1);
    detectar_pontes(g1);
    eh_planar_euler(g1); 
    printf("\n");

    GrafoLista* k5 = criar_grafo(5);
    for(int i = 0; i < 5; i++) {
        for(int j = i + 1; j < 5; j++) {
            adicionar_aresta(k5, i, j);
        }
    }

    printf("Teste 2: Grafo Planaridade\n");
    eh_planar_euler(k5); 
    
    liberar_grafo(g1);
    liberar_grafo(k5);

    return 0;
}