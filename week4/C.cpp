#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int N = 1e5 + 5;
int preorder[N];
int visited[N];
set<pair<int, int>> downedge;
set<pair<int, int>> upedge;

vector<int> edges[N];


int T = 0;
int reach[N];
bool bridge_found = false;

void dfs(int u, int from  = -1) {
    preorder[u] = T++;
    reach[u] = preorder[u];

    for (int v : edges[u]) if (v != from) {
        if (preorder[v] == -1) {
            downedge.insert(make_pair(u, v));
            dfs(v, u);

            if (reach[v] == preorder[v]) {
                // is a bridge must be vital so cannot make one way
                bridge_found = true;
                return;
            }
        }
        reach[u] = min(reach[u], reach[v]);
    }
}

void visit(int u) {
    visited[u] = true;

    for (int v : edges[u]) {
        // if we haven't visited them keep traversing down
        if (!visited[v]) {
            visit(v);
        } else {
            // if we visited u before visiting v
            // means u is a parent of v so v should form an upedge to it's parent
            if (preorder[u] < preorder[v]) {
                upedge.insert(make_pair(v, u));
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;


    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
    
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        preorder[i] = -1;
        visited[i] = false;
    }

    dfs(1);

    if (bridge_found) {
        cout << 0;
        return 0;
    }

    visit(1);

    cerr << "HEY" << endl;

    for (pair<int, int> gang : downedge) {
        cout << gang.first << " " << gang.second << endl;
    }

    cerr << "POOP" << endl;
    for (pair<int, int> gang : upedge) {
        cout << gang.first << " " << gang.second << endl;
    }
    return 0;
}