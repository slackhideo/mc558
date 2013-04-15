#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>

using namespace std;

#define TAM 500

enum cores {BRANCO, CINZA, PRETO};

int adj[TAM][TAM];
int pesos[TAM][TAM];
int arst[TAM][TAM];
int adjnum[TAM];
int pi[TAM];
int rank[TAM];

void makeset(int x);
void link(int x, int y);
int findset(int x);
void setunion(int x, int y);
void mstKruskal(int n, int m);
int cmparestas(const void *p1, const void *p2);
void mostrarMatrizes(int n);

int main(int argc, char *argv[]) {
    int n, m;
    int de, para, peso;

    memset(adjnum, 0, sizeof(adjnum));

    scanf("%d %d", &n, &m);

    for(int i=0; i<m; i++) {
        scanf("%d %d %d", &de, &para, &peso);
        adj[de][adjnum[de]] = para;
        adj[para][adjnum[para]] = de;
        arst[de][adjnum[de]] = 1;
        arst[para][adjnum[para]] = 0;
        pesos[de][adjnum[de]++] = peso;
        pesos[para][adjnum[para]++] = peso;
    }

    mstKruskal(n, m);

    return EXIT_SUCCESS;
}

void makeset(int x) {
    pi[x] = x;
    rank[x] = 0;
}

void link(int x, int y) {
    if(rank[x] > rank[y]) {
        pi[y] = x;
    }
    else {
        pi[x] = y;
        if(rank[x] == rank[y]) {
            rank[y]++;
        }
    }
}

int findset(int x) {
    if(x != pi[x]) {
        pi[x] = findset(pi[x]);
    }

    return pi[x];
}

void setunion(int x, int y) {
    link(findset(x), findset(y));
}

void mstKruskal(int n, int m) {
    int arestas[m][3], A[m][2];
    int peso=0, k=0, l=0;

    for(int i=0; i<n; i++) {
        makeset(i);
        for(int j=0; j<adjnum[i]; j++) {
            if(arst[i][j] == 1) {
                arestas[k][0] = i;
                arestas[k][1] = adj[i][j];
                arestas[k][2] = pesos[i][j];
                k++;
            }
        }
    }

    qsort(arestas, k, 3*sizeof(int), cmparestas);

    printf("Kruskal\n");

    for(int i=0; i<k; i++) {
        if(findset(arestas[i][0]) != findset(arestas[i][1])) {
            A[l][0] = arestas[i][0];
            A[l][1] = arestas[i][1];
            l++;
            peso += arestas[i][2];
            setunion(arestas[i][0], arestas[i][1]);
        }
    }

    printf("Peso do grafo: %d\n", peso);

    for(int i=0; i<l; i++) {
        printf("%d %d\n", A[i][0], A[i][1]);
    }
}

int cmparestas(const void *p1, const void *p2) {
    int a = ((int *)p1)[2];
    int b = ((int *)p2)[2];

    return a - b;
}

void mostrarMatrizes(int n) {
    printf("Mostrar matrizes\n");

    for(int i=0; i<n; i++) {
        for(int j=0; j<adjnum[i]; j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for(int i=0; i<n; i++) {
        for(int j=0; j<adjnum[i]; j++) {
            printf("%d ", pesos[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for(int i=0; i<n; i++) {
        for(int j=0; j<adjnum[i]; j++) {
            printf("%d ", arst[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
