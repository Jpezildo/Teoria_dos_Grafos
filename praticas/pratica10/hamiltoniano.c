#include "hamiltoniano.h"
#include <stdlib.h>

Grafo *criar_grafo(int n) {
    Grafo *g = (Grafo *)malloc(sizeof(Grafo));
    if (!g) return NULL;

    g->n = n;
    g->adj = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        g->adj[i] = (int *)calloc(n, sizeof(int));
    }
    return g;
}

void liberar_grafo(Grafo *g) {
    if (!g) return;
    for (int i = 0; i < g->n; i++) {
        free(g->adj[i]);
    }
    free(g->adj);
    free(g);
}

void adicionar_aresta(Grafo *g, int u, int v) {
    if (!g || u < 0 || u >= g->n || v < 0 || v >= g->n || u == v) return;
    g->adj[u][v] = 1;
    g->adj[v][u] = 1;
}

static bool bt_caminho(const Grafo *g, int *caminho, bool *visitado, int pos) {
    if (pos == g->n) {
        return true;
    }

    int anterior = caminho[pos - 1];
    for (int v = 0; v < g->n; v++) {
        if (!visitado[v] && g->adj[anterior][v] == 1) {
            visitado[v] = true;
            caminho[pos] = v;

            if (bt_caminho(g, caminho, visitado, pos + 1)) {
                return true;
            }

            visitado[v] = false;
        }
    }
    return false;
}

bool encontrar_caminho_hamiltoniano_bt(const Grafo *g, int *caminho) {
    if (!g || g->n <= 0 || !caminho) return false;

    bool *visitado = (bool *)calloc(g->n, sizeof(bool));
    if (!visitado) return false;

    for (int inicio = 0; inicio < g->n; inicio++) {
        for (int i = 0; i < g->n; i++) visitado[i] = false;

        caminho[0] = inicio;
        visitado[inicio] = true;

        if (bt_caminho(g, caminho, visitado, 1)) {
            free(visitado);
            return true;
        }
    }

    free(visitado);
    return false;
}

static bool bt_ciclo(const Grafo *g, int *ciclo, bool *visitado, int pos) {
    if (pos == g->n) {
        int ultimo = ciclo[pos - 1];
        if (g->adj[ultimo][ciclo[0]] == 1) {
            ciclo[pos] = ciclo[0];
            return true;
        }
        return false;
    }

    int anterior = ciclo[pos - 1];
    for (int v = 1; v < g->n; v++) {
        if (!visitado[v] && g->adj[anterior][v] == 1) {
            visitado[v] = true;
            ciclo[pos] = v;

            if (bt_ciclo(g, ciclo, visitado, pos + 1)) {
                return true;
            }

            visitado[v] = false;
        }
    }
    return false;
}

bool encontrar_ciclo_hamiltoniano_bt(const Grafo *g, int *ciclo) {
    if (!g || g->n < 3 || !ciclo) return false;

    bool *visitado = (bool *)calloc(g->n, sizeof(bool));
    if (!visitado) return false;

    ciclo[0] = 0;
    visitado[0] = true;

    bool encontrou = bt_ciclo(g, ciclo, visitado, 1);
    free(visitado);
    return encontrou;
}