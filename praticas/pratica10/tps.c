#include "tps.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

int **grafo_para_tsp(const Grafo *g) {
    if (!g || g->n <= 0) return NULL;

    int n = g->n;
    int **dist = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        dist[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else if (g->adj[i][j] == 1) {
                dist[i][j] = 1;
            } else {
                dist[i][j] = 2;
            }
        }
    }
    return dist;
}

void liberar_matriz_tsp(int **dist, int n) {
    if (!dist) return;
    for (int i = 0; i < n; i++) {
        free(dist[i]);
    }
    free(dist);
}

static void trocar(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void permutar_tsp(int n, int **dist, int *perm, int inicio, int custo_atual,
                         int *melhor_custo, int *melhor_rota) {
    if (custo_atual >= *melhor_custo) {
        return;
    }

    if (inicio == n) {
        int custo_total = custo_atual + dist[perm[n - 1]][0];
        if (custo_total < *melhor_custo) {
            *melhor_custo = custo_total;
            if (melhor_rota) {
                for (int i = 0; i < n; i++) {
                    melhor_rota[i] = perm[i];
                }
                melhor_rota[n] = 0;
            }
        }
        return;
    }

    for (int i = inicio; i < n; i++) {
        trocar(&perm[inicio], &perm[i]);
        int novo_custo = custo_atual + dist[perm[inicio - 1]][perm[inicio]];
        permutar_tsp(n, dist, perm, inicio + 1, novo_custo, melhor_custo, melhor_rota);
        trocar(&perm[inicio], &perm[i]);
    }
}

int tsp_forca_bruta(int n, int **dist, int *melhor_rota) {
    if (n <= 0 || !dist) return 0;
    if (n == 1) {
        if (melhor_rota) {
            melhor_rota[0] = 0;
            melhor_rota[1] = 0;
        }
        return 0;
    }

    int *perm = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        perm[i] = i;
    }

    int melhor_custo = INT_MAX;
    permutar_tsp(n, dist, perm, 1, 0, &melhor_custo, melhor_rota);

    free(perm);
    return melhor_custo;
}

int tsp_vizinho_mais_proximo(int n, int **dist, int *rota) {
    if (n <= 0 || !dist) return 0;

    bool *visitado = (bool *)calloc(n, sizeof(bool));
    int atual = 0;
    visitado[0] = true;
    if (rota) rota[0] = 0;

    int custo_total = 0;

    for (int passo = 1; passo < n; passo++) {
        int proximo = -1;
        int menor_dist = INT_MAX;

        for (int v = 0; v < n; v++) {
            if (!visitado[v] && dist[atual][v] < menor_dist) {
                menor_dist = dist[atual][v];
                proximo = v;
            }
        }

        visitado[proximo] = true;
        custo_total += menor_dist;
        atual = proximo;
        if (rota) rota[passo] = atual;
    }

    custo_total += dist[atual][0];
    if (rota) rota[n] = 0;

    free(visitado);
    return custo_total;
}

int tsp_insercao(int n, int **dist, int *rota) {
    if (n <= 0 || !dist) return 0;
    if (n == 1) {
        if (rota) {
            rota[0] = 0;
            rota[1] = 0;
        }
        return 0;
    }

    bool *no_ciclo = (bool *)calloc(n, sizeof(bool));
    int *ciclo = (int *)malloc((n + 1) * sizeof(int));

    int mais_proximo = 1;
    for (int v = 2; v < n; v++) {
        if (dist[0][v] < dist[0][mais_proximo]) {
            mais_proximo = v;
        }
    }

    ciclo[0] = 0;
    ciclo[1] = mais_proximo;
    ciclo[2] = 0;
    no_ciclo[0] = true;
    no_ciclo[mais_proximo] = true;
    int tam_ciclo = 2;

    while (tam_ciclo < n) {
        int v_escolhido = -1;
        int menor_dist_ciclo = INT_MAX;

        for (int v = 0; v < n; v++) {
            if (!no_ciclo[v]) {
                for (int i = 0; i < tam_ciclo; i++) {
                    if (dist[v][ciclo[i]] < menor_dist_ciclo) {
                        menor_dist_ciclo = dist[v][ciclo[i]];
                        v_escolhido = v;
                    }
                }
            }
        }

        int melhor_pos = 1;
        int menor_aumento = INT_MAX;

        for (int i = 0; i < tam_ciclo; i++) {
            int u = ciclo[i];
            int w = ciclo[i + 1];
            int aumento = dist[u][v_escolhido] + dist[v_escolhido][w] - dist[u][w];
            if (aumento < menor_aumento) {
                menor_aumento = aumento;
                melhor_pos = i + 1;
            }
        }

        for (int i = tam_ciclo + 1; i > melhor_pos; i--) {
            ciclo[i] = ciclo[i - 1];
        }
        ciclo[melhor_pos] = v_escolhido;
        no_ciclo[v_escolhido] = true;
        tam_ciclo++;
    }

    int custo_total = 0;
    for (int i = 0; i < n; i++) {
        custo_total += dist[ciclo[i]][ciclo[i + 1]];
        if (rota) rota[i] = ciclo[i];
    }
    if (rota) rota[n] = 0;

    free(no_ciclo);
    free(ciclo);
    return custo_total;
}