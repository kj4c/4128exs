#include<bits/stdc++.h>
using namespace std;

const int N = 200005; 
const int LOG = 20; // max depth

struct Edge {
    int u, v;
    long long weight;
    int index;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

vector<Edge> edges;                  
vector<pair<int, long long>> mst_adj[N];
int parent[N][LOG], depth[N];  
long long max_edge[N][LOG];
int n, m;

// Union-Find
int uf_parent[N];
int subtree_size[N];  

void init(int n) {
  for (int i = 1; i <= n; i++) {
    uf_parent[i] = i;
    subtree_size[i] = 1;
  }
}

int root(int x) {
  // only roots are their own parents
  return uf_parent[x] == x ? x : root(uf_parent[x]);
}

void join(int x, int y) {
  // join roots
  x = root(x); y = root(y);
  // test whether already connected
  if (x == y)
    return;
  // size heuristic
  // hang smaller subtree under root of larger subtree
  if (subtree_size[x] < subtree_size[y]) {
    uf_parent[x] = y;
    subtree_size[y] += subtree_size[x];
  } else {
    uf_parent[y] = x;
    subtree_size[x] += subtree_size[y];
  }
}

// Kruskal's MST
long long kruskal(int n) {
    sort(edges.begin(), edges.end());
    init(n);

    long long mst_weight = 0;
    for (const Edge& e : edges) {
        if (root(e.u) != root(e.v)) {
            join(e.u, e.v);
            mst_adj[e.u].push_back({e.v, e.weight});
            mst_adj[e.v].push_back({e.u, e.weight});
            mst_weight += e.weight;
        }
    }
    return mst_weight;
}

// binary lifting keeping track of max_edge;
void dfs(int u, int p, long long weight) {
    parent[u][0] = p;
    max_edge[u][0] = weight;
    for (int i = 1; i < LOG; i++) {
        if (parent[u][i - 1] != -1) {
            parent[u][i] = parent[parent[u][i - 1]][i - 1];
            max_edge[u][i] = max(max_edge[u][i - 1], max_edge[parent[u][i - 1]][i - 1]);
        }
    }

    for (auto [v, w] : mst_adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u, w);
        }
    }
}

// get heaviest edge from u to v
long long query_heaviest_edge(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    long long max_weight = 0;

    // same depth
    for (int i = LOG - 1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            max_weight = max(max_weight, max_edge[u][i]);
            u = parent[u][i];
        }
    }

    if (u == v) return max_weight;

    // make parents match find lca
    for (int i = LOG - 1; i >= 0; i--) {
        if (parent[u][i] != -1 && parent[u][i] != parent[v][i]) {
            max_weight = max({max_weight, max_edge[u][i], max_edge[v][i]});
            u = parent[u][i];
            v = parent[v][i];
        }
    }

    // max weight incld the immediate parents
    max_weight = max({max_weight, max_edge[u][0], max_edge[v][0]});
    return max_weight;
}

int main() {
    cin >> n >> m;

    edges.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
        edges[i].index = i;
    }

    // defauly mst weight
    long long mst_weight = kruskal(n);

    // compute the parents
    memset(parent, -1, sizeof(parent));
    dfs(1, -1, 0);

    vector<pair<int, long long>> results;
    for (const Edge& e : edges) {
        int u = e.u, v = e.v;
        long long w = e.weight;

        long long heaviest_edge = query_heaviest_edge(u, v);

        long long new_mst_weight = mst_weight + w - heaviest_edge;

        results.push_back({e.index, new_mst_weight});
    }

    sort(results.begin(), results.end());

    for (auto& res : results) {
        cout << res.second << endl;
    }

    return 0;
}
