#include "hamiltoniano.h"
#include "tps.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void imprimir_sequencia(const char *titulo, const int *seq, int tam) {
    printf("%s: ", titulo);
    for (int i = 0; i < tam; i++) {
        printf("%d%s", seq[i], (i < tam - 1) ? " -> " : "\n");
    }
}

static int **gerar_matriz_aleatoria(int n, unsigned int seed) {
    srand(seed);
    int **dist = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        dist[i] = (int *)calloc(n, sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int peso = (rand() % 90) + 10;
            dist[i][j] = peso;
            dist[j][i] = peso;
        }
    }
    return dist;
}

static void testar_hamiltoniano_e_reducao(void) {
    printf("=== 1. Teste de Caminho/Ciclo Hamiltoniano e Reducao para TSP ===\n");
    int n = 5;
    Grafo *g = criar_grafo(n);

    adicionar_aresta(g, 0, 1);
    adicionar_aresta(g, 1, 2);
    adicionar_aresta(g, 2, 3);
    adicionar_aresta(g, 3, 4);
    adicionar_aresta(g, 4, 0);
    adicionar_aresta(g, 1, 3);

    int caminho[5];
    int ciclo[6];

    if (encontrar_caminho_hamiltoniano_bt(g, caminho)) {
        imprimir_sequencia("Caminho Hamiltoniano encontrado", caminho, n);
    } else {
        printf("Nenhum Caminho Hamiltoniano encontrado.\n");
    }

    if (encontrar_ciclo_hamiltoniano_bt(g, ciclo)) {
        imprimir_sequencia("Ciclo Hamiltoniano encontrado", ciclo, n + 1);
    } else {
        printf("Nenhum Ciclo Hamiltoniano encontrado.\n");
    }

    int **dist_reduzido = grafo_para_tsp(g);
    int rota_tsp[6];
    int custo_tsp = tsp_forca_bruta(n, dist_reduzido, rota_tsp);

    printf("Custo TSP no grafo reduzido: %d (esperado %d pois existe ciclo hamiltoniano)\n",
           custo_tsp, n);
    imprimir_sequencia("Rota TSP reduzida", rota_tsp, n + 1);

    liberar_matriz_tsp(dist_reduzido, n);
    liberar_grafo(g);
    printf("\n");
}

static void executar_experimento_tsp(void) {
    printf("=== 2. Experimento Comparativo TSP (n = 5, 8, 10, 12) ===\n");
    int tamanhos[] = {5, 8, 10, 12};
    int qtd = 4;

    printf("%-4s | %-18s | %-20s | %-18s\n",
           "n", "Forca Bruta", "Vizinho Mais Prox.", "Insercao Mais Prox.");
    printf("%-4s | %-8s %-9s | %-8s %-11s | %-8s %-9s\n",
           "", "Custo", "Tempo(ms)", "Custo", "Tempo(ms)", "Custo", "Tempo(ms)");
    printf("------------------------------------------------------------------------\n");

    for (int idx = 0; idx < qtd; idx++) {
        int n = tamanhos[idx];
        int **dist = gerar_matriz_aleatoria(n, 42 + n);
        int *rota = (int *)malloc((n + 1) * sizeof(int));

        clock_t ini = clock();
        int custo_fb = tsp_forca_bruta(n, dist, rota);
        clock_t fim = clock();
        double tempo_fb = ((double)(fim - ini) / CLOCKS_PER_SEC) * 1000.0;

        ini = clock();
        int custo_vmp = tsp_vizinho_mais_proximo(n, dist, rota);
        fim = clock();
        double tempo_vmp = ((double)(fim - ini) / CLOCKS_PER_SEC) * 1000.0;

        ini = clock();
        int custo_ins = tsp_insercao(n, dist, rota);
        fim = clock();
        double tempo_ins = ((double)(fim - ini) / CLOCKS_PER_SEC) * 1000.0;

        printf("%-4d | %-8d %-9.3f | %-8d %-11.3f | %-8d %-9.3f\n",
               n, custo_fb, tempo_fb, custo_vmp, tempo_vmp, custo_ins, tempo_ins);

        free(rota);
        liberar_matriz_tsp(dist, n);
    }
}

int main(void) {
    testar_hamiltoniano_e_reducao();
    executar_experimento_tsp();
    return 0;
}