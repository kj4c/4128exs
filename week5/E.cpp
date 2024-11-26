#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <tuple>
#include <algorithm>
#include <map>
#include <queue>
#include <climits>

using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<pll> vpll;
typedef pair<char, int> pci;
const ll INF = LLONG_MAX;
#define REPi(n) for (int i = 0; i < n; i++)
#define REPj(n) for (int j = 0; j < n; j++)
#define REPk(n) for (int k = 0; k < n; k++)
#define REP1i(n) for (int i = 1; i <= n; i++)
#define REP1j(n) for (int j = 1; j <= n; j++)
#define REP1k(n) for (int k = 1; k <= n; k++)

int n, m;
int M = 150000;
int N = 500;
struct edge {
    int u;
    int v;
    ll w;
};
vector<edge> edges;
vector<vector<ll>> dist(N, vector<ll>(N));
vector<vector<ll>> inEdges(N, vector<ll>(N));
vector<vector<ll>> results(N, vector<ll>(N));


void inEdgesCount() {
    for (int s = 0; s < n; ++s) {
        for (const auto& e : edges) {
            int u = e.u, v = e.v;
            ll w = e.w;
            if (dist[s][u] + w == dist[s][v]) {
                inEdges[s][v]++;
            }
            if (dist[s][v] + w == dist[s][u]) {
                inEdges[s][u]++;
            }
        }
    }
}

void findRes() {
    for (int s = 0; s < n; s++)
        for (int t = 0; t < n; t++)
            for (int i = 0; i < n; i++) {
                if ((dist[s][i] + dist[i][t]) == dist[s][t]) {
                    results[s][t] += inEdges[s][i];
                }
            }
}


void floyd() {
    for (int u = 0; u < n; ++u)
        for (int v = 0; v < n; ++v)
            dist[u][v] = INF;
    // update the distances for every directed edge
    for (edge e : edges) {
    // each edge u -> v with weight w
        dist[e.u][e.v] = min(dist[e.u][e.v], e.w);
        dist[e.v][e.u] = min(dist[e.v][e.u], e.w);
    }

    // every vertex can reach itself
    for (int u = 0; u < n; ++u)
        dist[u][u] = 0;

    for (int i = 0; i < n; i++)
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++) {
                if (dist[u][i] < INF && dist[i][v] < INF) {
                    dist[u][v] = min(dist[u][v], dist[u][i] + dist[i][v]);
                }
            }
            // dist[u][v] is the length of the shortest path from u to v using only 0 to i as intermediate vertices
            // now that we're allowed to also use i, the only new path that could be shorter is u -> i -> v
}



int main()
{   
    cin >> n >> m;
    REPi(m) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--, v--;
        edges.push_back({v, u, w}); 
    }

    floyd();
    inEdgesCount();
    findRes();

    for (int i = 0; i < n; i++ ){
        for (int j = i + 1; j < n; j++) {
            cout << results[i][j] << " ";
        }
    }


    
    return 0;
}