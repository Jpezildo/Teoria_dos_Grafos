#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "busca_largura.h"
#include "busca_profundidade.h"

int main() {
    int num_vertices = 6;
 
    GrafoLista *g = criar_grafo(num_vertices);

    
    adicionar_aresta(g, 1, 2);
    adicionar_aresta(g, 2, 3);
    adicionar_aresta(g, 3, 4);
    adicionar_aresta(g, 3, 5);
    adicionar_aresta(g, 4, 5); 

    printf("=== TESTE DE BFS (Busca em Largura) ===\n");
    int *dist = (int*)malloc(g->num_vertices * sizeof(int));
    int *pred = (int*)malloc(g->num_vertices * sizeof(int));
    
    bfs(g, 0, dist, pred);
    
    for (int i = 0; i < g->num_vertices; i++) {
        printf("Vertice %d -> Distancia: %d | Predecessor: %d\n", i, dist[i], pred[i]);
    }
    printf("\n");

    printf("=== TESTE DE PROPRIEDADES DO GRAFO ===\n");
    
    int componentes = contar_componentes(g);
    printf("Componentes conexos: %d\n", componentes);

    int possui_ciclo = tem_ciclo(g);
    printf("Possui ciclo? %s\n", possui_ciclo ? "Sim" : "Nao"); 

    int bipartido = eh_bipartido(g);
    printf("Eh bipartido? %s\n", bipartido ? "Sim" : "Nao"); 

    
    free(dist);
    free(pred);
    
    
    liberar_grafo(g);

    return 0;
}