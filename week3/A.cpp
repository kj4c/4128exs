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
    ll numStudents;
    cin >> numStudents;

    vector<vector<ll>> s(2, vector<ll>(numStudents));
    vector<vector<ll>> opt(2, vector<ll>(numStudents));
    ll height;
    REPi(numStudents) {
        cin >> height;
        s[0][i] = height;
    }

    REPi(numStudents) {
        cin >> height;
        s[1][i] = height;
    }

    // Base case i = 0
    // opt(0,j) = height[i]
    // opt(1,j) = height[i] + opt(0, !j) 
    
    // Recursive case:
    // opt(i, j) = max(opt(i - 1, j), opt(i - 2, !j) + value, opt(i - 1, !j) + value)

    // Base cases
    opt[0][0] = s[0][0];
    opt[1][0] = s[1][0];

    opt[0][1] = opt[1][0] + s[0][1];
    opt[1][1] = opt[0][0] + s[1][1];

    for (int i = 2; i < numStudents; i++) {
        for (int j = 0; j <= 1; j++) {
            opt[j][i] = max({opt[j][i - 1], opt[!j][i - 2] + s[j][i], opt[!j][i-1] + s[j][i]});
        }
    }
    cout << max(opt[0][numStudents - 1], opt[1][numStudents - 1]);

    return 0;
}