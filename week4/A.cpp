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

int employees, applis;
const int N = 10000;

struct edge {
    int u, v;
    ll w;
};

vector<edge> edges;  

bool operator < (const edge& a, const edge& b) {
    return a.w < b.w;
}

int parent[N];
int subtree_size[N];  
bool supervisor[N]; 

void init(int n) {
  for (int i = 0; i < n; i++) {
    parent[i] = i;
    subtree_size[i] = 1;
    supervisor[i] = false;
  }
}

int root(int x) {
  // only roots are their own parents
  return parent[x] == x ? x : root(parent[x]);
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
    parent[x] = y;
    subtree_size[y] += subtree_size[x];
  } else {
    parent[y] = x;
    subtree_size[x] += subtree_size[y];
  }
}


ll mst(int n) {
  sort(edges.begin(), edges.end()); // sort by increasing weight
  ll total_weight = 0;
  ll edges_used = 0;

  for (const auto& e : edges) {
    // if the endpoints are in different trees, join them
    // if they don't have a supervisor already as well
    if (root(e.u) != root(e.v) && !supervisor[e.v]) {
      total_weight += e.w;
      join(e.u, e.v);
      edges_used++;
      supervisor[e.v] = true;

      if (edges_used == n - 1) {
        break;
      }
    }
  }
  return (edges_used == n - 1) ? total_weight : -1;
}

int main()
{
    cin >> employees;

    REPi(employees) {
        int voide;
        cin >> voide;
    }

    init(employees);

    cin >> applis;

    REPi(applis) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        edges.push_back({a, b, c});
    }

    if (applis == 0 && employees > 1) {
        cout << -1 << endl;
        return 0;
    }

    cout << mst(employees);

    return 0;
}