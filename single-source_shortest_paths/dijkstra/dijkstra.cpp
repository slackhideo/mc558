#include <cstdio>
#include <cstdlib>
#include <climits>
#include <vector>

using namespace std;

#define START 0

typedef unsigned int uint;

vector< vector<int> > adj;
vector< vector<int> > pesos;
vector<int> adjnum;
vector<int> d;
vector<int> pi;

void dijkstra(int s);
void initialiseSingleSource(int s);
void relax(int u, int v, int w);
void buildMinHeap(vector<int> *A, vector<int> *B);
void minHeapify(vector<int> *A, vector<int> *B, int i);
int parent(int i);
int left(int i);
int right(int i);
void troca(int *a, int *b);
int heapMinimum(vector<int> B);
int heapExtractMin(vector<int> *A, vector<int> *B);
void heapDecreaseKey(vector<int> *A, vector<int> *B, int i, int chave);
void mostraResultado(void);

int main(int argc, char *argv[]) {
    int n, m;
    int de, para, peso;

    if(scanf("%d %d", &n, &m) < 2) exit(1);

    adj.resize(n, vector<int>(n, -1));
    pesos.resize(n, vector<int>(n, 0));
    adjnum.resize(n, 0);
    d.resize(n, -1);
    pi.resize(n, -1);

    for(int i=0; i<m; i++) {
        if(scanf("%d %d %d", &de, &para, &peso) < 3) exit(1);
        adj[de][adjnum[de]] = para;
        pesos[de][adjnum[de]] = peso;
        adjnum[de]++;
    }

    dijkstra(START);

    mostraResultado();

    return EXIT_SUCCESS;
}

void dijkstra(int s) {
    vector<int> A(adj.size()+1), B(adj.size()+1);
    int u;

    initialiseSingleSource(s);
    for(uint v=0; v<adj.size(); v++) {
        A[v+1] = d[v];
        B[v+1] = v;
    }

    buildMinHeap(&A, &B);

    while(A.size() > 0) {
        u = heapExtractMin(&A, &B);
        for(int i=0; i<adjnum[u]; i++) {
            relax(u, adj[u][i], pesos[u][i]);
            heapDecreaseKey(&A, &B, adj[u][i], d[adj[u][i]]);
        }
    }
}

void initialiseSingleSource(int s) {
    for(uint v=0; v<adj.size(); v++) {
        d[v] = INT_MAX;
        pi[v] = -1;
    }
    d[s] = 0;
}

void relax(int u, int v, int w) {
    if(d[u] == INT_MAX) return;

    if(d[v] > d[u] + w) {
        d[v] = d[u] + w;
        pi[v] = u;
    }
}

void buildMinHeap(vector<int> *A, vector<int> *B) {
    for(uint i=((*A).size()-1)/2; i>0; i--) {
        minHeapify(A, B, i);
    }
}

void minHeapify(vector<int> *A, vector<int> *B, int i) {
    uint l=left(i), r=right(i);
    int menor;

    if(l<(*A).size() && (*A)[l]<(*A)[i]) {
        menor = l;
    }
    else {
        menor = i;
    }

    if(r<(*A).size() && (*A)[r]<(*A)[menor]) {
        menor = r;
    }

    if(menor != i) {
        troca(&(*A)[i], &(*A)[menor]);
        troca(&(*B)[i], &(*B)[menor]);
        minHeapify(A, B, menor);
    }
}

int parent(int i) {
    return i/2;
}

int left(int i) {
    return 2*i;
}

int right(int i) {
    return 2*i+1;
}

void troca(int *a, int *b) {
//
printf("%d %d\n", *a, *b);
//
    int tmp=*a;
    *a = *b;
    *b = tmp;
}

int heapMinimum(vector<int> B) {
    return B[1];
}

int heapExtractMin(vector<int> *A, vector<int> *B) {
    int min;

    if((*A).size() < 2) {
        perror("Erro! Underflow do heap\n");
        exit(1);
    }

    min = (*B)[1];
    (*A)[1] = (*A)[(*A).size()-1];
    (*B)[1] = (*B)[(*A).size()-1];

    (*A).resize((*A).size()-1);
    (*B).resize((*B).size()-1);

    minHeapify(A, B, 1);

    return min;
}

void heapDecreaseKey(vector<int> *A, vector<int> *B, int i, int chave) {
    if(chave > (*A)[i]) {
        perror("Erro! Nova chave é maior que a atual\n");
        exit(1);
    }

    (*A)[i] = chave;

    while(i>1 && (*A)[parent(i)] > (*A)[i]) {
        troca(&(*A)[i], &(*A)[parent(i)]);
        troca(&(*B)[i], &(*B)[parent(i)]);
        i = parent(i);
    }
}

void mostraResultado(void) {
    printf("Distâncias mínimas do vértice origem (%d)\n", START);
    for(uint i=0; i<d.size(); i++) {
        printf("d[%d]: %d\n", i, d[i]);
    }
    printf("\nÁrvore de caminhos mínimos\n");
    for(uint i=0; i<pi.size(); i++) {
        if(pi[i] == -1) continue;
        printf("%d->%d\n", pi[i], i);
    }
}
