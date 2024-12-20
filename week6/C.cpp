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
    int K, N;
    cin >> K;

    for (int i = 0; i < K; i++) {
        cin >> N;

        vector<vector<char>> input(N, vector<char>(N));
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                cin >> input[j][k];
            }
        }

        FlowNetwork network(N*N + 2);
        int source = N * N;
        int sink = N * N + 1;

        // make the graph
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                // j is row, k is col
                if (input[j][k] != '#') continue;
                
                // if it's even then connect source
                if ((j + k) % 2 == 0) {
                    int curr = (j * N) + k;
                    network.add_edge(source, curr, 1);

                    if (j > 0 && input[j - 1][k] == '#') {
                        network.add_edge(curr, (j - 1) * N + k, 1);
                    }
                    if (j < N - 1 && input[j + 1][k] == '#') {
                        network.add_edge(curr, (j + 1) * N + k, 1);
                    }
                    if (k > 0 && input[j][k - 1] == '#') {
                        network.add_edge(curr, j * N + (k - 1), 1);
                    }
                    if (k < N - 1 && input[j][k + 1] && '#') {
                        network.add_edge(curr, j * N + (k + 1), 1);
                    }
                } else {
                    // attach to sink
                    network.add_edge(j * N + k, sink, 1);
                }
            }
        }

        // flow time
        cout << "Case " << i + 1 << ": " <<  network.dinic(source, sink) << endl;

    }

    return 0;
}
