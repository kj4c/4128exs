#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;

typedef long long ll;

const ll INF = LLONG_MAX;

struct Edge {
    int to, rev;
    ll cap, flow;
};

struct FlowNetwork {
    int n;
    vector<vector<Edge>> adjList;
    vector<int> level, uptochild;
    vector<bool> mark;

    FlowNetwork(int _n) : n(_n) {
        adjList.resize(n);
        level.resize(n);
        uptochild.resize(n);
        mark.resize(n, false);
    }

    void add_edge(int u, int v, ll c) {
        adjList[u].push_back({v, (int)adjList[v].size(), c, 0});
        adjList[v].push_back({u, (int)adjList[u].size() - 1, c, 0}); 
    }

    void flow_edge(Edge& e, ll c) {
        e.flow += c;
        adjList[e.to][e.rev].flow -= c;
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            uptochild[u] = 0;
            for (auto& e : adjList[u]) {
                if (e.cap > e.flow && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    ll augment(int u, int t, ll f) {
        if (u == t) return f;
        for (int& i = uptochild[u]; i < adjList[u].size(); i++) {
            Edge& e = adjList[u][i];
            if (e.cap > e.flow && level[e.to] == level[u] + 1) {
                ll rf = augment(e.to, t, min(f, e.cap - e.flow));
                if (rf > 0) {
                    flow_edge(e, rf);
                    return rf;
                }
            }
        }
        return 0;
    }

    ll dinic(int s, int t) {
        ll res = 0;
        while (bfs(s, t)) {
            for (ll x = augment(s, t, INF); x; x = augment(s, t, INF))
                res += x;
        }
        return res;
    }

    void dfs_norm(int now) {
        mark[now] = true;
        for (auto& e : adjList[now]) {
            if (!mark[e.to] && e.cap > e.flow) { 
                dfs_norm(e.to);
            }
        }
    }

    void dfs_residual(int now) {
        mark[now] = true;
        for (auto& e : adjList[now]) {
            Edge& rev = adjList[e.to][e.rev];
            if (!mark[e.to] && rev.cap - rev.flow > 0) {
                dfs_residual(e.to);
            }
        }
    }

    string check_uniqueness(int s, int t) {
        fill(mark.begin(), mark.end(), false);

        dfs_norm(s);
        dfs_residual(t);

        for (int i = 0; i < n; i++) {
            // means that node unreachablefrom both
            // source n sink so mult solutions
            if (!mark[i]) {
                return "AMBIGUOUS";
            }
        }

        return "UNIQUE";
    }
};

int main() {
    int n, m, a, b;
    cin >> n >> m >> a >> b;

    FlowNetwork network(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        network.add_edge(u - 1, v - 1, c);
    }

    network.dinic(a - 1, b - 1); 

    cout << network.check_uniqueness(a - 1, b - 1) << endl;

    return 0;
}
