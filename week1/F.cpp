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

vector<ll> arr;

int cmp(pair<int, int> x, pair<int, int> y) {
    if (x.second != y.second) {
        return x.second > y.second;
    }
    // if the second index ties then sort by value
    if (arr[x.first] != arr[y.first]) return arr[x.first] < arr[y.first];
    // if value ties as well
    // sort by ascending order of the first index
    return x.first < y.first;

}
int main()
{
    int n;
    cin >> n;

    arr.resize(n);
    REPi(n) {
        ll luh;
        cin >> luh;
        arr[i] = luh;
    }

    vector<pair<int, int>> inversions;
    // find all inversions and add to the vector 
    REPi(n) {
        int curr = arr[i];
        for (int j = 0; j < i; j++) {
            if (arr[j] > curr) {
                inversions.push_back({j, i});
            }
        }
    }

    // sort the inversions based on second index descending order
    sort(inversions.begin(), inversions.end(), cmp);
    cout << inversions.size() << endl;
    for (auto &val : inversions) cout << val.first + 1 << " " << val.second + 1 << endl;
    return 0;
}