#ifndef DIJKSTRA_H
#define DIJKSTRA_H


#define INF INT_MAX


typedef struct NoAresta {
    int destino;
    int peso;
    struct NoAresta *prox;
} NoAresta;

typedef struct {
    NoAresta *cabeca;
} ListaAdjacencia;

typedef struct {
    int num_vertices;
    ListaAdjacencia *array;
} GrafoListaPonderado;


typedef struct {
    int vertice;
    int distancia;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade, tamanho;
    int *posicao;
} MinHeap;


GrafoListaPonderado* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoListaPonderado *g, int origem, int destino, int peso);
void liberar_grafo(GrafoListaPonderado *g);


MinHeap* criar_min_heap(int capacidade);
void extrair_minimo(MinHeap *h, int *vertice_min, int *dist_min);
void diminuir_chave(MinHeap *h, int vertice, int distancia);
void liberar_min_heap(MinHeap *h);


void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_caminho(int origem, int destino, int *pred);

#endif