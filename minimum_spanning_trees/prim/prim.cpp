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

vector<int> key;
vector<int> pi;

void prim(int r);
void buildMinHeap(vector<int> *A, vector<int> *B, vector<int> *C);
void minHeapify(vector<int> *A, vector<int> *B, vector<int> *C, int i);
int parent(int i);
int left(int i);
int right(int i);
void troca(int *a, int *b);
int heapMinimum(vector<int> B);
int heapExtractMin(vector<int> *A, vector<int> *B, vector<int> *C);
void heapDecreaseKey(vector<int> *A, vector<int> *B, vector<int> *C,
        int i, int chave);
void mostraResultado(void);

int main(int argc, char *argv[]) {
    int n, m;
    int de, para, peso;

    if(scanf("%d %d", &n, &m) < 2) exit(1);

    adj.resize(n, vector<int>(n, -1));
    pesos.resize(n, vector<int>(n, 0));
    adjnum.resize(n, 0);

    key.resize(n, INT_MAX);
    pi.resize(n, -1);

    for(int i=0; i<m; i++) {
        if(scanf("%d %d %d", &de, &para, &peso) < 3) exit(1);
        adj[de][adjnum[de]] = para;
        pesos[de][adjnum[de]] = peso;
        adjnum[de]++;

        adj[para][adjnum[para]] = de;
        pesos[para][adjnum[para]] = peso;
        adjnum[para]++;
    }

    prim(START);

    mostraResultado();

    return EXIT_SUCCESS;
}

void prim(int r) {
    vector<int> A(adj.size()+1), B(adj.size()+1), C(adj.size());
    int u, v;

    key[r] = 0;

    for(uint v=0; v<adj.size(); v++) {
        A[v+1] = key[v];
        B[v+1] = v;
        C[v] = v+1;
    }

    buildMinHeap(&A, &B, &C);

    while(A.size() > 1) {
        u = heapExtractMin(&A, &B, &C);
        for(int i=0; i<adjnum[u]; i++) {
            v = adj[u][i];
            if(C[v] != -1 && pesos[u][i] < key[v]) {
                pi[v] = u;
                key[v] = pesos[u][i];
                heapDecreaseKey(&A, &B, &C, C[v], key[v]);
            }
        }
    }
}

void buildMinHeap(vector<int> *A, vector<int> *B, vector<int> *C) {
    for(uint i=((*A).size()-1)/2; i>0; i--) {
        minHeapify(A, B, C, i);
    }
}

void minHeapify(vector<int> *A, vector<int> *B, vector<int> *C, int i) {
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
        troca(&(*C)[(*B)[i]], &(*C)[(*B)[menor]]);
        minHeapify(A, B, C, menor);
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
    int tmp=*a;
    *a = *b;
    *b = tmp;
}

int heapMinimum(vector<int> B) {
    return B[1];
}

int heapExtractMin(vector<int> *A, vector<int> *B, vector<int> *C) {
    int min;

    if((*A).size() < 2) {
        printf("Erro! Underflow do heap\n");
        exit(1);
    }

    min = (*B)[1];
    (*A)[1] = (*A)[(*A).size()-1];
    (*B)[1] = (*B)[(*A).size()-1];
    (*C)[(*B)[1]] = 1;
    (*C)[min] = -1;

    (*A).resize((*A).size()-1);
    (*B).resize((*B).size()-1);

    minHeapify(A, B, C, 1);

    return min;
}

void heapDecreaseKey(vector<int> *A, vector<int> *B, vector<int> *C,
        int i, int chave) {
    if(chave > (*A)[i]) {
        printf("Erro! Nova chave é maior que a atual\n");
        exit(1);
    }

    (*A)[i] = chave;

    while(i>1 && (*A)[parent(i)] > (*A)[i]) {
        troca(&(*A)[i], &(*A)[parent(i)]);
        troca(&(*B)[i], &(*B)[parent(i)]);
        troca(&(*C)[(*B)[i]], &(*C)[(*B)[parent(i)]]);
        i = parent(i);
    }
}

void mostraResultado(void) {
    int soma = 0;

    for(uint i=0; i<key.size(); i++) {
        soma += key[i];
    }

    printf("Prim a partir do vértice %d\n", START);
    printf("Peso do grafo: %d\n", soma);
    for(uint i=0; i<pi.size(); i++) {
        if(pi[i] == -1) continue;
        printf("%d<->%d\n", pi[i], i);
    }
}
