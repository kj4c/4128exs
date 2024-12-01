#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <tuple>
#include <algorithm>
#include <map>
#include <set>
// #include <bits/stdc++.h>

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

    vector<pair<ll, ll>> activities; 
    for (ll i = 0; i < n; i++) {
        ll s, f;
        cin >> s >> f;
        activities.push_back(make_pair(s, f));
    }

    // sort by the fastest ending time.
    sort(activities.begin(), activities.end(), [](const pair<ll, ll>& a, const pair<ll, ll>& b) {
        if (a.second == b.second) {
            return a.first < b.first;
        }
        return a.second < b.second;
    });

    multiset<int> endTimes;
    REPi(k) {
        endTimes.insert(0);
    }

    int r = 0;
    REPi(n) {
        pair<ll, ll> curr = activities[i];
        auto it = endTimes.lower_bound(curr.first);
        if (it != endTimes.begin()) {
            *it--;
            endTimes.erase(it);
            endTimes.insert(curr.second);
            r++;
        } 
    }

    cout << r;

    return 0;
}