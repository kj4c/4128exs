//globe trotter
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
 
using namespace std;
 
typedef long long ll;
// to vertex, weight, isTrain
const int N = 100100;
vector<int> edges[N];
ll dist[N];
bool seen[N];

priority_queue<int, vector<int>> pq;
 
ll trainsNotUsed = 0;
 
void dijkstra (ll s) {
    fill(seen,seen+N,false);
    fill(dist, dist + N, 1e18); 

    pq.push(0); // distance to s itself is zero
    dist[s] = 0;
 
    while (!pq.empty()) {   
        auto [v, d, isTrain] = pq.top();
        pq.pop();

        if (seen[v]) {
            continue;
        };

        dist[v] = d;
        seen[v] = true;
 
        // relax all edges from v
        for (auto [u, weight, newEdgeisTrain] : edges[v]) {
            ll newWeight = d + weight;
            if (!seen[u]) {
                pq.push(edge(u, newWeight, newEdgeisTrain));
            }
        }
    }
}
 
int main() {
    ll n, m, k;
    cin >> n >> m >> k;
 
    for (int i = 0; i < m; i++) {
        ll u, v, x;
        cin >> u >> v;
 
        edges[u].push_back(v);
    }
 
    dijkstra(1);
 
    cout << dist[n];
}