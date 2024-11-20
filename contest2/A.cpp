#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <tuple>
#include <algorithm>
#include <map>
#include <set>
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

ll plates;
priority_queue<ll> radiuses;
vector<ll> chosen;

int main()
{
    cin >> plates;
    REPi(plates) {
        ll radius;
        cin >> radius;
        radiuses.push(radius);
    }

    // greedy approach
    // take the largest radius and then take radius amount of the next one
    ll sr = radiuses.top();
    chosen.push_back(sr);
    radiuses.pop();
    while (sr > 0 && !radiuses.empty()) {
        sr--;
        if (sr <= 0) break; 
        chosen.push_back(radiuses.top());

        if (radiuses.top() < sr) {
            sr = radiuses.top();
        }
        radiuses.pop();
    }

    cout << chosen.size() << endl;
    for (ll val : chosen) {
        cout << val << " ";
    }


    return 0;
}