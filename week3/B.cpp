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
vector<vector<ll>> rules(n, vector<ll>(n, 0));
vll satisfaction(n + 1, 0);
vector<vector<ll>> bitScore(1<<n, vector<ll>(n, 0));

void r(int bitset, int lastDish) {
    if (__builtin_popcount(bitset) == m) {
        return;
    }

    REPi(n) {
        // if already ate this dish skip
        if ((bitset & (1 << i)) != 0) {
            continue;
        }
        int newBitset = bitset | (1 << i);
        
        // calculate score
        ll score = satisfaction[i] + rules[lastDish][i] + bitScore[bitset][lastDish];
        bitScore[newBitset][i] = max(bitScore[newBitset][i], score);

        // recurse using newBitset
        r(newBitset, i);
    }

    return;
}

int main()
{
    cin >> n >> m >> k;
    
    rules.assign(n, vector<ll>(n, 0));
    satisfaction.assign(n, 0);
    bitScore.assign(1 << n, vector<ll>(n, 0));

    REPi(n) {
        cin >> satisfaction[i];
    }

    ll x, y, z;
    REPi(k) {
        cin >> x >> y >> z;
        x--;
        y--;
        rules[x][y] = z;
    }

    // try every single combination
    // base cases
    REPi(n) {
        bitScore[1<<i][i] = satisfaction[i];
    }

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int lastDish = 0; lastDish < n; lastDish++) {
            // if this mask does not contain the last dish then just ignore
            if (!(mask & (1 << lastDish))) {
                continue;
            }

            // since it contains the last dish, check the rules of eating the last dish
            // before this next dish munchy munch
            for (int nextDish = 0; nextDish < n; nextDish++) {
                // if already in the subset then skip
                if (mask & (1 << nextDish)) {
                    continue;
                }

                // make new mask
                int newMask = mask | (1 << nextDish);

                // new score
                ll score = satisfaction[nextDish] + rules[lastDish][nextDish] + bitScore[mask][lastDish];
                bitScore[newMask][nextDish] = max(bitScore[newMask][nextDish], score);
            }
        }
    }

    ll maxScore = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (__builtin_popcount(mask) == m) {
            for (int lastDish = 0; lastDish < n; lastDish++) {
                maxScore = max(maxScore, bitScore[mask][lastDish]);
            }
        }
    }
    
    cout << maxScore << endl;

    return 0;
}