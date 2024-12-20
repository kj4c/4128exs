#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;
using ll = long long;

int n, m, k;
const ll INF = LLONG_MAX;  

struct FlowNetwork {
    int n;
    vector<vector<ll>> adjMat, adjList;
    vector<int> level, uptochild;

    FlowNetwork(int _n) : n(_n) {
        adjMat.resize(n, vector<ll>(n, 0));
        adjList.resize(n);
        level.resize(n);
        uptochild.resize(n);
    }

    void add_edge(int u, int v, ll c) {
        adjMat[u][v] += c;        
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void flow_edge(int u, int v, ll c) {
        adjMat[u][v] -= c;
        adjMat[v][u] += c;
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            uptochild[u] = 0;
            for (int v : adjList[u])
                if (adjMat[u][v] > 0 && level[v] == -1) {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
        }
        return level[t] != -1;
    }

    ll augment(int u, int t, ll f) {
        if (u == t) return f;
        for (int &i = uptochild[u]; i < adjList[u].size(); i++) {
            int v = adjList[u][i];
            if (adjMat[u][v] > 0 && level[v] == level[u] + 1) {
                ll rf = augment(v, t, min(f, adjMat[u][v]));
                if (rf > 0) {
                    flow_edge(u, v, rf);
                    return rf;
                }
            }
        }
        level[u] = -1;
        return 0;
    }

    ll dinic(int s, int t) {
        ll res = 0;
        while (bfs(s, t))
            for (ll x = augment(s, t, INF); x; x = augment(s, t, INF))
                res += x;
        return res;
    }
};

int main() {
    // heroes, monsters, potions
    cin >> n >> m >> k;
    FlowNetwork network(n + m + 3);

    int source = n + m;
    int potion = n + m + 1;
    int sink = n + m + 2;

    network.add_edge(source, potion, k);

    for (int i = 0; i < n; i++) {
        network.add_edge(potion, i, 1);
        network.add_edge(source, i, 1);
        int t;
        cin >> t;
        for (int j = 0; j < t; j++) {
            int mon;
            cin >> mon;

            // hero to monster
            network.add_edge(i, n + mon - 1, 1);
        }
    }

    for (int i = 0; i < m; i++) {
        network.add_edge(i + n, sink, 1);
    }

    cout << network.dinic(source, sink);

    return 0;
}
