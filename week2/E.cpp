#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <tuple>
#include <algorithm>
#include <map>
#include <queue>
#include <set>

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

const int N = 500100;
int parent[N];
int subtree_size[N];  
ll sums[N];
multiset<ll> totalSum;
vector<int> population(N, 0);
vector<pair<int, int>> roads(N);

void init(int n) {
  for (int i = 1; i <= n; i++) {
    parent[i] = i;
    subtree_size[i] = 1;
	sums[i] = population[i];
	totalSum.insert(sums[i]);
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

	auto itX = totalSum.find(sums[x]);
	if(itX != totalSum.end()) totalSum.erase(itX);

	auto itY = totalSum.find(sums[y]);
	if(itY != totalSum.end()) totalSum.erase(itY);

  // size heuristic
  // hang smaller subtree under root of larger subtree
  if (subtree_size[x] < subtree_size[y]) {
    parent[x] = y;
    subtree_size[y] += subtree_size[x];
	sums[y] += sums[x];
	totalSum.insert(sums[y]);
  } else {
    parent[y] = x;
    subtree_size[x] += subtree_size[y];
	sums[x] += sums[y];
	totalSum.insert(sums[x]);
  }
}

void update(int index, int newVal) {
    int rootIndex = root(index);
    
    auto it = totalSum.find(sums[rootIndex]);
    if(it != totalSum.end()) totalSum.erase(it);
    
    int oldVal = population[index];
    int diff = newVal - oldVal;
    population[index] = newVal;
    
    sums[rootIndex] += diff;
    
    totalSum.insert(sums[rootIndex]);
}

int main()
{
    int n, m, q;
    cin >> n >> m >> q;

    REP1i(n) {
        int p;
        cin >> p;
        population[i] = p;
    }

    //edges
    REP1i(m) {
        cin >> roads[i].first;
        cin >> roads[i].second;
    }

    vector<tuple<char, int, int>> queries(q);
    vector<int> deleted(m + 1, 0);
    vector<vector<int>> prev_pops(N + 1, vector<int>());

    REPi(q) {
		char type;
		cin >> type;
      
		if (type == 'D') {
			int edge;
			cin >> edge;
			queries[i] = {type, edge, -1};
			deleted[edge] = 1;
		} else if (type == 'P') {
			int town, p;
			cin >> town >> p;
			queries[i] = {type, town, p};
			prev_pops[town].push_back(population[town]);
			population[town] = p;
		}
    }

	// initialise the union with all the current populations
	// connect edges that were not deleted
	init(n);
	REP1i(m) {
		// not deleted join it up
		if (!deleted[i]) {
			pair<int, int> currRoad = roads[i];
			join(currRoad.first, currRoad.second);
		}
	}

	reverse(queries.begin(), queries.end());
	vector<ll> results(q);

	for (int i = 0; i < q; i++) {
    	auto &[type, option, unused] = queries[i];
		// total sum would have the most populated at the back
		if(!totalSum.empty()) {
        	results[i] = *totalSum.rbegin();
    	} else {
        	results[i] = 0; // If no components
    	}

		if (type == 'D') {
			// add edge back in
			pair<int, int> road = roads[option];
			join(road.first, road.second);
		} else {
			// update the population
			if (!prev_pops[option].empty()){
				int newPop = prev_pops[option].back();
				prev_pops[option].pop_back();

				update(option, newPop);
			}
		}
	}

	for (int i = q - 1; i >= 0; i--) {
        cout << results[i] << '\n';
    }
    return 0;
}