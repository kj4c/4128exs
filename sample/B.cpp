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

auto cmp = [](pair<ll, ll>& a, pair<ll, ll>&b) {
    return a.second < b.second;
};

auto cmp1 = [](pair<ll, ll>& a, pair<ll, ll>&b) {
    return a.first > b.first;
};

int main()
{   
    int n;
    cin >> n;

    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, decltype(cmp)> pq(cmp);

    vpll fruits;

    ll last = 0;
    REPi(n) {
        ll expiry;
        cin >> expiry;
        ll hap;
        cin >> hap;
        fruits.emplace_back(expiry, hap);
        last = max(last, expiry);
    }

    sort(fruits.begin(), fruits.end(), cmp1);

    int fruit_index = 0;
    ll total = 0;
    for (int i = last; i >= 1; i--) {
        while (fruits[fruit_index].first >= i) {
            pq.push(fruits[fruit_index]);
            fruit_index++;
        }

        if (!pq.empty()) {
            pll fruitington = pq.top();
            total += fruitington.second;
            pq.pop();
        }
    }

    cout << total;    

    return 0;
}