#include <cstdio>
#include <cstdlib>
#include <climits>
#include <vector>

using namespace std;

typedef unsigned int uint;

/* Variáveis para o grafo */
vector< vector<int> > adj;
vector< vector<int> > pesos;
vector<int> adjnum;

/* Variáveis auxiliares para o Bellman-Ford */
vector<int> d;
vector<int> nv;
vector<int> pi;

/* Protótipos das funções */
bool bellmanFord(int s);
void initialiseSingleSource(int s);
void relax(int u, int v, int w);
void mostraResultado(int s);
void mostraCaminho(int v);


int main(int argc, char *argv[]) {
    int n, m;
    int de, para, peso;
    int inicio;

    /* Lê as dimensões do grafo e redimensiona os vetores de acordo */
    scanf("%d %d", &n, &m);
    adj.resize(n, vector<int>(n, -1));
    pesos.resize(n, vector<int>(n, 0));
    adjnum.resize(n, 0);

    d.resize(n);
    nv.resize(n, 1);
    pi.resize(n);

    /* Lê as arestas com seus pesos */
    for(int i=0; i<m; i++) {
        scanf("%d %d %d", &de, &para, &peso);
        adj[de][adjnum[de]] = para;
        pesos[de][adjnum[de]] = peso;
        adjnum[de]++;
    }

    /* Lê o vértice a partir do qual as distâncias e caminhos serão calculados */
    scanf("%d", &inicio);

    /* Chama a função de Bellman-Ford para calcular os caminhos mínimos */
    if(bellmanFord(inicio) == true) {
        mostraResultado(inicio);
    }
    else {
        printf("Ciclo de peso negativo detectado!\n");
    }

    return EXIT_SUCCESS;
}


/* Função que implementa o algoritmo de Bellman-Ford para o cálculo das
 * distâncias mínimas a partir de um vértice inicial
 *
 * @param s Vértice inicial
 *
 * @return false se o grafo contiver ciclo negativo e true caso contrário */
bool bellmanFord(int s) {
    initialiseSingleSource(s);

    for(uint i=0; i<adj.size()-1; i++) {
        for(uint u=0; u<adj.size(); u++) {
            for(int k=0; k<adjnum[u]; k++) {
                relax(u, adj[u][k], pesos[u][k]);
            }
        }
    }

    /* Verificação da presença ou não de ciclos negativos no grafo */
    for(uint u=0; u<adj.size(); u++) {
        for(int i=0; i<adjnum[u]; i++) {
            if(d[u] < INT_MAX && d[adj[u][i]] > d[u] + pesos[u][i]) {
                return false;
            }
        }
    }

    return true;
}


/* Função que inicializa as variáveis auxiliares
 *
 * @param s Vértice inicial */
void initialiseSingleSource(int s) {
    for(uint v=0; v<adj.size(); v++) {
        d[v] = INT_MAX;
        nv[v] = 1;
        pi[v] = -1;
    }

    d[s] = 0;
}


/* Função que relaxa arestas do grafo
 *
 * @param u Vértice origem da aresta
 *
 * @param v Vértice destino da aresta
 *
 * @param w Peso da aresta */
void relax(int u, int v, int w) {
    if(d[u] == INT_MAX) return;

    if(d[v] > d[u] + w) {
        d[v] = d[u] + w;
        nv[v] = nv[u] + 1;
        pi[v] = u;
    }
}


/* Função que mostra o resultado do algoritmo de Bellman-Ford
 *
 * @param s Vértice inicial */
void mostraResultado(int s) {
    printf("Distâncias mínimas do vértice origem (vértice %d):\n", s);
    for(uint i=0; i<d.size(); i++) {
        printf("d[%d]: %d\n", i, d[i]);
    }

    printf("\nÁrvore de caminhos mínimos:\n");
    for(uint i=0; i<pi.size(); i++) {
        if(pi[i] == -1) continue;
        printf("%d->%d\n", pi[i], i);
    }
    printf("\n");

    for(uint v=0; v<d.size(); v++) {
        if(d[v] == INT_MAX) {
            printf("Não há caminho de %d para %d", s, v);
        }
        else {
            printf("Caminho de %d para %d com peso %d e %d vértice", s, v, d[v], nv[v]);
            printf((nv[v] > 1)?"s:":":");

            mostraCaminho(v);
        }
        printf("\n");
    }
}

/* Função recursiva que mostra os vértices de um caminho
 *
 * @param v Vértice sendo considerado */
void mostraCaminho(int v) {
    if(v == -1) return;
    mostraCaminho(pi[v]);
    printf(" %d", v);
}
