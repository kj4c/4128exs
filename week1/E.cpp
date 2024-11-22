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


int main()
{
    ll n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    string t;
    cin >> t;

    if (t == s || k == 1) {
        cout << n << "\n";
        return 0;
    }

    ll c = 0;
    ll combinations = 1;

    REPi(n) {
        // at each stage double the combinations
        combinations *= 2;

        // but if s is a b then you need to minus one possible combination as the lower 
        // bound is already max
        if (s[i] == 'b') combinations--;

        // same goes for t
        if (t[i] == 'a') combinations --;


        // since there are only k posisble strings, we bounded
        // by k possible combinations
        combinations = min(combinations, k);
        c += combinations;
    }

    cout << c << endl;

    return 0;
}