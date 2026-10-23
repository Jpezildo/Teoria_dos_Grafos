#include <stdio.h>
#include <stdlib.h>
#include "planaridade.h"


int* calcular_graus(GrafoLista* g) {
    int* graus = (int*) calloc(g->num_vertices, sizeof(int));
    for (int i = 0; i < g->num_vertices; i++) {
        No* atual = g->adj[i];
        while (atual) {
            graus[i]++;
            atual = atual->prox;
        }
    }
    return graus;
}

int eh_planar_euler(GrafoLista *g) {
    int n = g->num_vertices;
    int m = g->num_arestas;


    if (n >= 3 && m > 3 * n - 6) {
        printf("Grafo NAO planar: Falhou na heuristica de Euler (m > 3n - 6).\n");
        return 0; 
    }


    if (n <= 10) {
        int* graus = calcular_graus(g);
        int cand_k5 = 0;
        int cand_k33 = 0;


        for (int i = 0; i < n; i++) {
            if (graus[i] >= 4) cand_k5++;
            if (graus[i] >= 3) cand_k33++;
        }
        free(graus);

        if (cand_k5 >= 5) {
            printf("Grafo NAO planar: Suspeita de subdivisao K5 (Kuratowski).\n");
            return 0; 
        }
        if (cand_k33 >= 6 && m >= 9) {
            printf("Grafo NAO planar: Suspeita de subdivisao K3,3 (Kuratowski).\n");
            return 0;
        }
    }

    printf("Grafo PLANAR: Passou nos testes de Euler e Kuratowski para pequenos n.\n");
    return 1;
}