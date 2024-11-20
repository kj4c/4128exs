#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;
using ll = long long;

const ll INF = LLONG_MAX; 

struct Edge {
    int to;
    double capacity;
    int rev;
};

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

    void reset() {
        adjMat.clear();
        adjList.clear();
    }
};

int main() {
    int n, m, x;
    cin >> n >> m >> x;

    double max_capacity = 0;
    vector<vector<int>> edges;

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 1) max_capacity += c;
        --a; --b;
        edges.push_back({a, b, c});

    }
    
    double left = 0, right = max_capacity;
    double mid = (left + right) / 2;
    double max_flow = 0;

    for (int i = 0; i < 100; i++) {
        FlowNetwork flow_graph(n);
        // how much an indiivual bear should carry
        mid = (left + right) / 2;

        for (auto& edge : edges) {
            // to from
            int a = edge[0], b = edge[1];
            double divided_capacity = edge[2] / mid;
            flow_graph.add_edge(a, b, divided_capacity);
        }

        // max flow will be
        max_flow = flow_graph.dinic(0, n - 1);

        // each edge represents maximum amount of bears that can cross
        // the edge
        // max flow indicates if we can send at least X bears, if its >= x
        // try to look for a higher bound
        if (max_flow >= x) {
            left = mid;
        } else {
            right = mid;
        }
    }

    printf("%.10f\n", round(left * x * 1e10) / 1e10);
    return 0;
}
