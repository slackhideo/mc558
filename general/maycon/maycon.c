#include <stdio.h>
#include <stdlib.h>

#define gelt int
#define INF 0x7FFFFFFF

void exchange(int *a, int *b);
void minheapify(int *H, int *aux, int size, int i);
void buildminheap(int *H, int *aux, int size);
int heapminimum(int *H);
int heapextractmin(int *H, int *aux, int *size);
void heapdecreasekey(int *H, int *aux, int i, int key);
void minheapinsert(int *H, int *aux, int *size, int key);
int heapfind(int *aux, int size, int vertex);

typedef struct _Node {
    gelt node;
    int weight;
    struct _Node *next;
} Node;

typedef struct _List {
    Node *head;
    Node *tail;
} List;

typedef struct _Graph {
    int nv;
    int ne;
    List **adj;
} Graph;

/* Cria um grafo novo com espaço para n vértices */
Graph *createGraph(int n) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    List **adj = (List **)malloc(n * sizeof(List));
    int i;

    for(i = 0; i < n; i++) {
        adj[i] = NULL;
    }

    graph->nv = 0;
    graph->ne = 0;
    graph->adj = adj;

    return graph;
}

/* Procura um vértice no grafo e, se encontrar, retorna sua posição */
int findVertex(Graph *graph, gelt val) {
    int i;

    for(i = 0; i < graph->nv; i++) {
        if(graph->adj[i]->head->node == val) {
            return i;
        }
    }

    return -1;
}

/* Adiciona um vértice ao grafo */
void addVertex(Graph *graph, int nmax, gelt val) {
    List *adj = (List *)malloc(sizeof(List));
    Node *vert = (Node *)malloc(sizeof(Node));
    int i;

    vert->node = val;
    vert->weight = 0;
    vert->next = NULL;

    adj->head = vert;
    adj->tail = vert;

    i = 0;
    while(graph->adj[i] != NULL) {
        i++;
    }

    if(findVertex(graph, val) != -1) {
        printf("Erro! Vértice já está no grafo!\n");
        exit(1);
    }

    if(i == nmax) {
        printf("Erro! Grafo cheio!\n");
        exit(1);
    }

    graph->nv++;
    graph->adj[i] = adj;
}

/* Adiciona uma aresta ao grafo */
void addEdge(Graph *graph, gelt from, gelt to, int weight) {
    Node *neighbour;
    int i;

    i = findVertex(graph, from);
    if(i == -1) {
        printf("Erro! Vértice de origem não está no grafo!\n");
        exit(1);
    }

    if(findVertex(graph, to) == -1) {
        printf("Erro! Vértice de destino não está no grafo!\n");
        exit(1);
    }

    neighbour = (Node *)malloc(sizeof(Node));
    neighbour->node = to;
    neighbour->weight = weight;
    neighbour->next = NULL;

    graph->adj[i]->tail->next = neighbour;
    graph->adj[i]->tail = neighbour;
}

/* Executa o algoritmo de Prim de árvore geradora mínima */
void AGMPrim(Graph *graph, gelt r, gelt *Pi) {
    Node *vertP;
    int i, heapsize;
    gelt u;
    int *key, *aux;

    heapsize = graph->nv;
    key = (int *)malloc(graph->nv * sizeof(gelt));
    aux = (int *)malloc(graph->nv * sizeof(gelt));

    for(i = 0; i < graph->nv; i++) {
        u = graph->adj[i]->head->node;
        key[u] = INF;
        aux[i] = i;
        Pi[u] = -1;
    }

    key[r] = 0;
    buildminheap(key, aux, heapsize);

    while(heapsize > 0) {
        u = heapextractmin(key, aux, &heapsize);
        for(vertP = graph->adj[u]->head->next; vertP != NULL;
                vertP = vertP->next) {
            if(heapfind(aux, heapsize, vertP->node) != -1 &&
                    vertP->weight < key[vertP->node]) {
                Pi[vertP->node] = u;
                key[vertP->node] = vertP->weight;
                minheapify(key, aux, heapsize, vertP->node);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    Graph *graph;
    int i, weight;
    int n, m;
    gelt from, to;

    /* Lê o número de vértices e de arestas */
    scanf("%d %d", &n, &m);

    graph = createGraph(n);

    /* Insere os vértices no grafo */
    for(i = 0; i < n; i++) {
        addVertex(graph, n, i);
    }

    /* Lê as arestas e as insere no grafo */
    for(i = 0; i < m; i++) {
        scanf("%d %d %d", &from, &to, &weight);
        addEdge(graph, from, to, weight);
    }


    printf("FOI\n");

    return EXIT_SUCCESS;
}
