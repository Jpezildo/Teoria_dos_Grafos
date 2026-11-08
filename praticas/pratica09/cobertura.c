#include "cobertura.h"

int eh_cobertura(Aresta *a, int *cobertura, int m) {
    for(int i = 0; i < m; i++) {
        int u = a[i].u;
        int v = a[i].v;
        if (!cobertura[u] && !cobertura[v]) {
            return 0;
        }
    }
    return 1;
}


static void bt_recursivo(Aresta *a, int n, int m, int *melhor_cobertura, int *tamanho_minimo, int *cobertura_atual, int vertice_atual, int tamanho_atual) {

    if (tamanho_atual >= *tamanho_minimo) {
        return;
    }

    if (vertice_atual == n) {
        if (eh_cobertura(a, cobertura_atual, m)) {
            *tamanho_minimo = tamanho_atual;
            for (int i = 0; i < n; i++) {
                melhor_cobertura[i] = cobertura_atual[i];
            }
        }
        return;
    }


    cobertura_atual[vertice_atual] = 1;
    bt_recursivo(a, n, m, melhor_cobertura, tamanho_minimo, cobertura_atual, vertice_atual + 1, tamanho_atual + 1);


    cobertura_atual[vertice_atual] = 0;
    bt_recursivo(a, n, m, melhor_cobertura, tamanho_minimo, cobertura_atual, vertice_atual + 1, tamanho_atual);
}

void cobertura_minima_bt(Aresta *a, int n, int m, int *melhor_cobertura, int *tamanho_minimo) {
    int cobertura_atual[MAX_VERTICES] = {0};
    *tamanho_minimo = n + 1;

    bt_recursivo(a, n, m, melhor_cobertura, tamanho_minimo, cobertura_atual, 0, 0);
}

void cobertura_gulosa(Aresta *a, int n, int m, int *cobertura_resultado) {
    // Zera a cobertura
    for(int i = 0; i < n; i++) {
        cobertura_resultado[i] = 0;
    }

    int arestas_cobertas[MAX_VERTICES * MAX_VERTICES] = {0};
    int total_cobertas = 0;


    while (total_cobertas < m) {
        int grau[MAX_VERTICES] = {0};

        for (int i = 0; i < m; i++) {
            if (!arestas_cobertas[i]) {
                grau[a[i].u]++;
                grau[a[i].v]++;
            }
        }

        int maior_grau = -1;
        int vertice_escolhido = -1;

        for (int i = 0; i < n; i++) {
            if (cobertura_resultado[i] == 0 && grau[i] > maior_grau) {
                maior_grau = grau[i];
                vertice_escolhido = i;
            }
        }

     
        if (maior_grau == 0 || vertice_escolhido == -1) break;

        cobertura_resultado[vertice_escolhido] = 1;

   
        for (int i = 0; i < m; i++) {
            if (!arestas_cobertas[i] && (a[i].u == vertice_escolhido || a[i].v == vertice_escolhido)) {
                arestas_cobertas[i] = 1;
                total_cobertas++;
            }
        }
    }
}