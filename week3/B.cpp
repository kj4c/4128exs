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

ll n, m, k;
vector<vector<vll>> rules(n, vector<vll>(n));
vll satisfaction(n + 1, 0);
vector<vector<vll>> bitScore(1<<m, vector<vll>(1<<m));

int r(int bitset, int lastDish) {

}

int main()
{
    cin >> n >> m >> k;
    

    REPi(n) {
        cin >> satisfaction[i];
    }


    ll x, y, z;
    REPi(k) {
        cin >> x >> y >> z;
        rules[x][y].push_back(z);
        rules[y][x].push_back(z);
    }

    // try every single combination


    return 0;
}