#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
using namespace std;
 
typedef long long ll;
const ll INF = 1e18;
 
ll n, m, L, s, t;
 
// u, v, weight, isEmpty
typedef tuple<ll, ll, ll, ll> edge;
 
const int N = 100100;
vector<vector<edge>> edges;
vector<pair<ll, ll>> givenEdges;
vector<vector<ll>> weights;
vector<vector<bool>> isEmpty;
vector<vector<bool>> usington;
vector<pair<ll, ll>> used;
vector<ll> previous(N, -1);
set<string> seenEdges;
ll dist[N];
bool seen[N];
 
struct CompareWeight {
    bool operator()(const edge& e1, const edge& e2) {
        return get<2>(e1) > get<2>(e2);
    }
};
 
priority_queue<edge, vector<edge>, CompareWeight> pq;
priority_queue<edge, vector<edge>, CompareWeight> pq2;
 
int dijkstra(ll s) {
    fill(seen, seen+N, false);
    fill(dist, dist + N, INF); 
    fill(previous.begin(), previous.end(), -1);
    used.clear();
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            usington[i][j] = false;
            usington[j][i] = false;
        }
    }
 
    pq2.push(edge(-1, s, 0, 0)); // distance to s itself is zero
    dist[s] = 0;
 
    while (!pq2.empty()) {   
        auto [u, v, d, isEmpty] = pq2.top();
        pq2.pop();
 
        if (seen[v]) {
            continue;
        };
 
        dist[v] = d;
        seen[v] = true;
        previous[v] = u;
 
        // relax all edges from v
        for (auto [from, u, x, empty] : edges[v]) {
            ll weight = weights[from][u];
            ll newWeight = d + weight;
            if (!seen[u]) {
                pq2.push(edge(from, u, newWeight, empty));
            }
        }
    }

    if (dist[t] > L) {
        return -1;
    }
    
    ll edgesUsed = 0;
    for (int i = t; previous[i] != -1; i = previous[i]) {
        ll prevting = previous[i];
        if (isEmpty[prevting][i] || isEmpty[i][prevting]) {
            used.push_back({prevting, i});
            usington[prevting][i] = true;
            usington[i][prevting] = true;
            edgesUsed++;
        }
    }

    // make everything else infinity
    for (tuple<ll, ll> e : givenEdges) {
        int i = get<0>(e); 
        int j = get<1>(e);
        // for not used edge
        if (!usington[i][j] && isEmpty[i][j]) {
            weights[i][j] = INF;
            weights[j][i] = INF;
        }
    }
 
    // need to account for the 1's we added
    ll remainingWeight = (L - dist[t]);

    auto[i, j] = used[0];
    weights[i][j] += remainingWeight;
    weights[j][i] += remainingWeight;
 
    return dist[t];
}
 
int dijkstraNoEmpty(ll s) {
    fill(seen,seen+N,false);
    fill(dist, dist + N, INF); 
 
    pq.push(edge(-1, s, 0, 0)); // distance to s itself is zero
    dist[s] = 0;
 
    while (!pq.empty()) {   
        auto [u, v, d, isEmpty] = pq.top();
        pq.pop();
        if (isEmpty) {
            continue;
        }
 
        if (seen[v]) {
            continue;
        };
 
        dist[v] = d;
        seen[v] = true;
 
        // relax all edges from v
        for (auto [from, u, weight, empty] : edges[v]) {
            ll newWeight = d + weight;
            if (!seen[u] && !empty) {
                pq.push(edge(from, u, newWeight, empty));
            }
        }
    }
 
    // if the shortest distance is smaller then no
    if (dist[t] < L) {
        return -1;
    }
 
    return 0;
}
 
int main() {
    cin >> n >> m >> L >> s >> t;
    edges.resize(n);
    weights.resize(n, vector<ll>(n, -1));
    isEmpty.resize(n, vector<bool>(n, false));
    usington.resize(n, vector<bool>(n, false));
    previous.resize(n, -1);
 
    for (int i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        if (w == 0) {
            // empty edges filled with weight of 1
            edges[u].push_back({u, v, 1, true});
            edges[v].push_back({v, u, 1, true});
            isEmpty[u][v] = true;
            isEmpty[v][u] = true;
            weights[u][v] = 1;
            weights[v][u] = 1;
        } else {
            edges[u].push_back({u, v, w, false});
            edges[v].push_back({v, u, w, false});
            weights[u][v] = w;
            weights[v][u] = w;
        }
 
        givenEdges.push_back({u, v});
    }
 
    int code = dijkstraNoEmpty(s);
    if (code == -1) {
        cout << "NO";
        return 0;
    }
 
    ll currshort = dijkstra(s);
    if (currshort == -1) {
        cout << "NO";
        return 0;
    }

    while (currshort != L) {
        currshort = dijkstra(s);
    }
 
 
    cout << "YES" << endl;
    // print all the edges
    // given as 0 means unused bih
    for (tuple<ll, ll> e : givenEdges) {
        int i = get<0>(e); 
        int j = get<1>(e);
        cout << i << " " << j << " " << weights[i][j] << endl;
    }
 
    return 0;
}