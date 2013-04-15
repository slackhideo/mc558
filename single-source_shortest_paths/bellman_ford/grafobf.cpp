#include <cstdio>
#include <cstdlib>
#include <climits>
#include <vector>

using namespace std;

#define START 3

typedef unsigned int uint;

vector< vector<int> > adj;
vector< vector<int> > pesos;
vector<int> adjnum;

vector<int> d;
vector<int> pi;

bool bellmanFord(int s);
void initialiseSingleSource(int s);
void relax(int u, int v, int w);

int main(int argc, char *argv[]) {
    int n, m;
    int de, para, peso;

    scanf("%d %d", &n, &m);
    adj.resize(n, vector<int>(n, -1));
    pesos.resize(n, vector<int>(n, 0));
    adjnum.resize(n, 0);

    d.resize(n);
    pi.resize(n);

    for(int i=0; i<m; i++) {
        scanf("%d %d %d", &de, &para, &peso);
        adj[de][adjnum[de]] = para;
        pesos[de][adjnum[de]] = peso;
        adjnum[de]++;
    }

    if(bellmanFord(START) == true) {
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
    else {
        printf("Ciclo de peso negativo detectado!\n");
    }

    return EXIT_SUCCESS;
}

bool bellmanFord(int s) {
    initialiseSingleSource(s);

    for(uint i=0; i<adj.size()-1; i++) {
        for(uint u=0; u<adj.size(); u++) {
            for(int k=0; k<adjnum[u]; k++) {
                relax(u, adj[u][k], pesos[u][k]);
            }
        }
    }

    for(uint u=0; u<adj.size(); u++) {
        for(int i=0; i<adjnum[u]; i++) {
            if(d[u] < INT_MAX && d[adj[u][i]] > d[u] + pesos[u][i]) {
                return false;
            }
        }
    }

    return true;
}

void initialiseSingleSource(int s) {
    for(uint i=0; i<adj.size(); i++) {
        d[i] = INT_MAX;
        pi[i] = -1;
    }

    d[s] = 0;
}

void relax(int u, int v, int w) {
    if(d[u] == INT_MAX) {
        return;
    }
    if(d[v] > d[u] + w) {
        d[v] = d[u] + w;
        pi[v] = u;
    }
}
