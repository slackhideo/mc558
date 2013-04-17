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
void minHeapify(vector<int> *A, vector<int> *B, int i);
int parent(int i);
int left(int i);
int right(int i);
void troca(vector<int> *a, vector<int> *b);

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

    return EXIT_SUCCESS;
}

void dijkstra(int s) {
    initialiseSingleSource(s);
}

void initialiseSingleSource(int s) {
    for(uint v=0; v<adj.size(); v++) {
        d[v] = INT_MAX;
        pi[v] = -1;
    }
    d[s] = 0;
}

void relax(int u, int v, int w) {
}

void minHeapify(vector<int> *A, vector<int> *B, int i) {
    uint l=left(i), r=right(i);
    int menor;

    if(l<=(*A).size() && (*A)[l]<(*A)[i]) {
        menor = l;
    }
    else {
        menor = i;
    }

    if(r<=(*A).size() && (*A)[r]<(*A)[menor]) {
        menor = r;
    }

    if(menor != i) {
        troca(&A[i], &A[menor]);
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

void troca(vector<int> *a, vector<int> *b) {
    int tmp=*a;
    *a = *b;
    *b = tmp;
}

