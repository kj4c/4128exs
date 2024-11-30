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
    // ll n;
    // cin >> n;

    // ll sum = 0;
    // ll product = 1;

    // for (int i = 0; i < n)
    string n;
    cin >> n;

    ll sum = int(n[0]) - '0';
    ll product = int(n[0]) - '0';
    for (int i = 1; i < n.size(); i++) {
        sum += int(n[i]) - '0';
        product *= int(n[i])  - '0';

    }   


    if (sum * product != stol(n)) {
        cout << "NO";
    } else {
        cout << "YES";
    }

    return 0;
}