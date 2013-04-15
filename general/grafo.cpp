#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <list>

using namespace std;

#define TAM 500
#define INF 0x7FFFFFFF

typedef int gelt;

enum cores {BRANCO, CINZA, PRETO};

gelt adj[TAM][TAM];
int adjnum[TAM];

/* Grafo transposto */
gelt adjt[TAM][TAM];
int adjnumt[TAM];

int cor[TAM];
gelt pai[TAM];
list<gelt> lista; /* Para ordenação topológica */
list<gelt> listatmp;
int componentes[TAM];

void transpor(int);
void BFS(int, int);
void DFS(int, bool);
void DFS_VISIT(gelt, int *, int *, int *, int);

int main(int argc, char *argv[]) {
    int n, m;
    int de, para;

    /* Zera o vetor adjnum */
    memset(adjnum, 0, sizeof(adjnum));

    /* Lê o número de vértices e de arestas */
    scanf("%d %d", &n, &m);

    /* Lê as arestas */
    for(int i=0; i<m; i++) {
        scanf("%d %d", &de, &para);
        adj[de][adjnum[de]++] = para; /* Ida */
//        adj[para][adjnum[para]++] = de; /* Volta */
    }

    printf("\nBFS\n");
    BFS(n, 0);

    printf("\nDFS\n");
    DFS(n, false);

    printf("\nOrdenação topológica\n");
    for(list<gelt>::iterator it=lista.begin(); it != lista.end(); ++it) {
        printf(" %d", *it);
    }
    printf("\n");

    transpor(n);
    printf("\nDFS transposta\n");
    DFS(n, true);

    return EXIT_SUCCESS;
}

/* Transpõe o grafo */
void transpor(int n) {
    gelt u, v;

    /* Zera o vetor adjnumt */
    memset(adjnumt, 0, sizeof(adjnumt));

    for(int i=0; i<n; i++) {
        v = i;
        for(int j=0; j<adjnum[v]; j++) {
            u = adj[v][j];
            adjt[u][adjnumt[u]++] = v;
        }
    }

    memset(adj, 0, sizeof(adj));
    memset(adjnum, 0, sizeof(adjnum));

    memcpy(adj, adjt, sizeof(adjt));
    memcpy(adjnum, adjnumt, sizeof(adjnumt));
}


/* Realiza busca em largura */
void BFS(int n, int s) {
    gelt u, v;
    int d[TAM]; /* Distância */
    queue<gelt> fila;

    memset(cor, BRANCO, sizeof(cor));
    memset(d, INF, sizeof(d));

    cor[s] = CINZA;
    d[s] = 0;

    fila.push(s);

    while(!fila.empty()) {
        u = fila.front();
        fila.pop();

        for(int i=0; i<adjnum[u]; i++) {
            v = adj[u][i];
            if(cor[v] == BRANCO) {
                cor[v] = 1;
                d[v] = d[u] + 1;
                pai[v] = u;
                fila.push(v);
            }
        }
        cor[u] = PRETO;
        printf("Terminado: %d\n", u);
    }
}

/* Realiza busca em profundidade */
void DFS(int n, bool t) {
    gelt u;
    int d[TAM], f[TAM]; /* Tempos de descoberta e finalização */
    int tempo = 0;
    int comp = 0;

    memset(cor, BRANCO, sizeof(cor));
    memset(pai, 0, sizeof(pai));

    if(t == true) {
        if(lista.size() < 1) {
            printf("Chame DFS(n, false) primeiro!\n");
            return;
        }

        listatmp = lista;
        lista.clear();

        for(list<gelt>::iterator it=listatmp.begin(); it != listatmp.end(); ++it) {
            u = *it;
            if(cor[u] == BRANCO) {
                printf("Componente %d:\n", ++comp);
                componentes[u] = comp;
                DFS_VISIT(u, d, f, &tempo, comp);
            }
        }
    }
    else {
        for(int i=0; i<n; i++) {
            u = i;
            if(cor[u] == BRANCO) {
                printf("Componente %d:\n", ++comp);
                componentes[u] = comp;
                DFS_VISIT(u, d, f, &tempo, comp);
            }
        }
    }

    for(int i=0; i<n; i++) {
        printf("Componente de '%d' é %d\n", i, componentes[i]);
    }
}

void DFS_VISIT(gelt u, int *d, int *f, int *tempo, int comp) {
    gelt v;

    cor[u] = CINZA;
    d[u] = ++(*tempo);

    for(int i=0; i<adjnum[u]; i++) {
        v = adj[u][i];
        if(cor[v] == BRANCO) {
            pai[v] = u;
            componentes[v] = comp;
            DFS_VISIT(v, d, f, tempo, comp);
        }
    }

    cor[u] = PRETO;
    f[u] = ++(*tempo);
    lista.push_front(u);
    printf("\tTerminado: %d (%d, %d)\n", u, d[u], f[u]);
}

