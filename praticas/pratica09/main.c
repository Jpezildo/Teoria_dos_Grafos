#include <stdio.h>
#include <time.h>
#include "cobertura.h"


void gerar_grafo_teste(int n, Aresta *arestas, int *m) {
    *m = 0;

    for (int i = 0; i < n - 1; i++) {
        arestas[*m].u = i;
        arestas[*m].v = i + 1;
        (*m)++;
    }

    if (n > 3) {
        arestas[*m].u = 0; 
        arestas[*m].v = n - 1; 
        (*m)++;
    }
}

int main() {
    int valores_n[] = {5, 8, 10, 12, 15};
    int quantidade_testes = 5;

    printf("=== EXPERIMENTO: COBERTURA DE VERTICES ===\n\n");

    for (int i = 0; i < quantidade_testes; i++) {
        int n = valores_n[i];
        int m;
        Aresta arestas[MAX_VERTICES * MAX_VERTICES]; 
        
        gerar_grafo_teste(n, arestas, &m);

        int melhor_cobertura_bt[MAX_VERTICES] = {0};
        int tamanho_minimo_bt = n;
        int cobertura_resultado_gulosa[MAX_VERTICES] = {0};

        printf("Testando para n = %d (Arestas = %d)\n", n, m);


        clock_t inicio_bt = clock();
        cobertura_minima_bt(arestas, n, m, melhor_cobertura_bt, &tamanho_minimo_bt);
        clock_t fim_bt = clock();
        double tempo_bt = (double)(fim_bt - inicio_bt) / CLOCKS_PER_SEC;

        clock_t inicio_gulosa = clock();
        cobertura_gulosa(arestas, n, m, cobertura_resultado_gulosa);
        clock_t fim_gulosa = clock();
        double tempo_gulosa = (double)(fim_gulosa - inicio_gulosa) / CLOCKS_PER_SEC;

        printf("  -> Tempo Backtracking: %f segundos\n", tempo_bt);
        printf("  -> Tempo Gulosa      : %f segundos\n", tempo_gulosa);
        printf("----------------------------------------\n");
    }

    return 0;
}