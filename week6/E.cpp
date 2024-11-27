#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <tuple>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<pll> vpll;
typedef pair<char, int> pci;
#define REPi(n) for (int i = 0; i < n; i++)
#define REPj(n) for (int j = 0; j < n; j++)
#define REPk(n) for (int k = 0; k < n; k++)
#define REP1i(n) for (int i = 1; i <= n; i++)
#define REP1j(n) for (int j = 1; j <= n; j++)
#define REP1k(n) for (int k = 1; k <= n; k++)

int n, t;

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

vector<vector<ll>> contamTime;
vector<vector<ll>> sciTime;
vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
vector<vector<char>> scis;
vector<vector<int>> pods;

void computeContamination(int x, int y) {
    vector<vector<ll>> prev(n, vector<ll>(n));
    queue<pair<int, int>> q;

    contamTime[x][y] = 0;

    q.push({x, y});

    while (!q.empty()) {
        pair<int, int> front = q.front();
        int x = front.first;
        int y = front.second;
        q.pop();
        for (int d = 0; d < 4; d++) {
            pair<int, int> direc = directions[d];
            int nx = x + direc.first;
            int ny = y + direc.second;

            if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                if (scis[nx][ny] != 'Y' && scis[nx][ny] != 'Z' && contamTime[nx][ny] == INF) {
                    contamTime[nx][ny] = contamTime[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }
}

// for each scientist bfs dat bih
vector<pair<int, int>> sciBfs(int x, int y) {
    vector<pair<int, int>> validSources;
    queue<pair<int, int>> q;
    sciTime.clear();
    sciTime.assign(n, vector<ll>(n, INF));
    sciTime[x][y] = 0;
    q.push({x, y,});

    // edge ur on is alrdy a pod
    if (pods[x][y] != 0) {
        // connect an edge for this bradah
        validSources.push_back({x, y});
    }
    while (!q.empty()) {
        pair<int, int> front = q.front();
        int x = front.first;
        int y = front.second;
        q.pop();
        for (int d = 0; d < 4; d++) {
            pair<int, int> direc = directions[d];
            int nx = x + direc.first;
            int ny = y + direc.second;

            if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                if (scis[nx][ny] != 'Y' && scis[nx][ny] != 'Z' && sciTime[nx][ny] == INF) {
                    sciTime[nx][ny] = sciTime[x][y] + 1;
                    // ur dead so dont further explore
                    // if you aint dead then chill keep going
                    if (sciTime[nx][ny] < contamTime[nx][ny]) {
                        q.push({nx, ny});
                    }

                    // check if you reached a pod and also you havent exploded yet
                    if (sciTime[nx][ny] <= contamTime[nx][ny] && pods[nx][ny] != 0 && sciTime[nx][ny] <= t) {
                        // connect an edge for this bradah
                        validSources.push_back({nx, ny});
                    }
                }
            }
        }
    }
    return validSources;
}

int getId(int x, int y, int k) {
    return (x * n) + y + (k * n*n);
}


int main()
{
    cin >> n >> t;

    scis.resize(n, vector<char>(n));
    pods.resize(n, vector<int>(n, 0));
    contamTime.resize(n, vector<ll>(n, INF));
    sciTime.resize(n, vector<ll>(n, INF));
    pair<int, int> malf;
    REPi(n) {
        string row;
        cin >> row;
        REPj(n) {
            char loco = row[j];
            scis[i][j] = loco;
            if (loco == 'Z') {
                malf = {i, j};
            }
        }
    }    

    REPi(n) {
        string row;
        cin >> row;
        REPj(n) {
            char pod = row[j];
            if (pod != 'Y' && pod != 'Z') {
                pods[i][j] = pod - '0';
            }
        }
    }

    computeContamination(malf.first, malf.second);

    // REPi(n) {
    //     REPj(n) {
    //         if (contamTime[i][j] == INF) {
    //             cerr << "INF";
    //         } else {
    //             cerr << contamTime[i][j];
    //         }
    //         cerr << " ";
    //     }
    //     cerr << '\n';
    // }

    
    int source = 2*n*n + 1;
    int sink = 2*n*n + 2;
    FlowNetwork net(210);

    REPi(n) {
        REPj(n) {
            // connect sources to scientist
            if (scis[i][j] != 'Y' && scis[i][j] != 'Z' && scis[i][j] != '0') {
                net.add_edge(source, getId(i, j, 0), scis[i][j] - '0');
                // cout << "MY ID: " << getId(i, j, 0) << endl;
            
                // find tings to connect to
                for (pair<int, int> caps : sciBfs(i, j)) {
                    net.add_edge(getId(i, j, 0), getId(caps.first, caps.second, 1), INF);
                }
            }

            // is a pod
            if (pods[i][j] != 0) {
                net.add_edge(getId(i, j, 1), sink, pods[i][j]);
            }
        }
    }

    cout << net.dinic(source, sink);

    return 0;
}