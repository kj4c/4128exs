#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef long long ll;

const ll INF = LLONG_MAX;

struct Edge {
    int to, rev;
    ll cap;
};

struct FlowNetwork {
    int n;
    vector<vector<Edge>> adjList;
    vector<int> level, uptochild;
    vector<int> col; 
    // 0: unvisited, 1: visited in dfs1, 2: visited in dfs2
    int arr[3]; 
    // arr[1]: count of nodes visited in dfs1, arr[2]: in dfs2

    FlowNetwork(int _n) : n(_n) {
        adjList.resize(n);
        level.resize(n);
        uptochild.resize(n);
        col.resize(n, 0);
        arr[1] = arr[2] = 0;
    }

    void add_edge(int u, int v, ll c) {
        Edge uv = {v, (int)adjList[v].size(), c};
        Edge vu = {u, (int)adjList[u].size(), 0};
        adjList[u].push_back(uv);
        adjList[v].push_back(vu);
    }

    void add_undirected_edge(int u, int v, ll c) {
        add_edge(u, v, c);
        add_edge(v, u, c);
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
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    ll dfs(int u, int t, ll f) {
        if (u == t) return f;
        for (int& i = uptochild[u]; i < adjList[u].size(); i++) {
            Edge& e = adjList[u][i];
            if (e.cap > 0 && level[e.to] == level[u] + 1) {
                ll rf = dfs(e.to, t, min(f, e.cap));
                if (rf > 0) {
                    e.cap -= rf;
                    adjList[e.to][e.rev].cap += rf;
                    return rf;
                }
            }
        }
        return 0;
    }

    ll dinic(int s, int t) {
        ll res = 0;
        while (bfs(s, t)) {
            fill(uptochild.begin(), uptochild.end(), 0);
            while (ll x = dfs(s, t, INF)) {
                res += x;
            }
        }
        return res;
    }

    void dfs1(int now) {
        col[now] = 1;
        arr[1]++;
        for (auto& e : adjList[now]) {
            if (e.cap > 0 && col[e.to] == 0) {
                dfs1(e.to);
            }
        }
    }

    void dfs2(int now) {
        col[now] = 2;
        arr[2]++;
        for (auto& e : adjList[now]) {
            Edge& rev = adjList[e.to][e.rev];
            if (rev.cap > 0 && col[e.to] == 0) {
                dfs2(e.to);
            }
        }
    }

    string check_uniqueness(int s, int t) {
        fill(col.begin(), col.end(), 0);
        arr[1] = arr[2] = 0;

        dfs1(s);
        dfs2(t);

        if (arr[1] + arr[2] == n) {
            return "UNIQUE";
        } else {
            return "AMBIGUOUS";
        }
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
        u--; v--;
        network.add_undirected_edge(u, v, c);
    }

    network.dinic(a - 1, b - 1);

    cout << network.check_uniqueness(a - 1, b - 1) << endl;

    return 0;
}
