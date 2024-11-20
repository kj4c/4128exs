 #include <iostream>
#include <vector>

using namespace std;

const int N = 5000 + 5;
int n, m;
vector<pair<int, int>> edges[N];
vector<bool> seen(N, false);
vector<bool> active(N, false);
vector<int> color(N, 1);
int finalColors[N];
bool hasCycle = false;
vector<pair<int, int>> inputEdges;

void dfs(int u, int parentColor) {
    seen[u] = true;
    active[u] = true;

    for (pair<int, int> edge : edges[u]) {
        cerr << "from: " << u << " " << "to: " << edge.first << endl;
        // cycle found on this current edge so change to new color.
        // if this is a child edge
        if (!seen[edge.first]) {
            // keep same as parent.
            finalColors[edge.second] =  parentColor;
            dfs(edge.first, parentColor);
        } else if (active[edge.first]) {
            // this is a backedge so don't recurse;
            // make it alternate from the parent
            finalColors[edge.second] = 3 - parentColor;
            hasCycle = true;
        } else {
            // not a backedge but visited without a color for the edge.
            if (finalColors[edge.second] == 0) finalColors[edge.second] = parentColor;
        }
      
    }
    active[u] = false;
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        // i being the ith edge
        edges[u].push_back({v, i});
    }    

    // dfs for every vertex
    for (int i = 1; i <= n; i++) {
        dfs(i, 1);  
    }

    if (!hasCycle) {
        cout << 1 << endl;
        for (int i = 0; i < m; i++) {
            finalColors[i] = 1;
        }
    } else {
        cout << 2 << endl;
    }

    for (int i = 0; i < m; i++) {
        cout << finalColors[i] << " ";
    }


    return 0;
}
 