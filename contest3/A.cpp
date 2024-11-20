#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;
using ll = long long;

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
    int n;
    cin >> n;
    int s = 0; // Source is player 1
    int t = n + 1;
    // n node each node has 2 edges
    FlowNetwork network(n + 2);

    network.add_edge(s, 1, n);

    // Read the input and build the flow network
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        network.add_edge(i, a, INF);
        network.add_edge(i, b, INF);
        network.add_edge(i, t, 1);
    }

    if (network.dinic(s, t) == n) {
        cout << "Yes";
    } else {
        cout << "No";
    }

}
