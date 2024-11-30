#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <tuple>
#include <algorithm>
#include <map>
#include <queue>
#include <stack>

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
    string s, u;
    stack<char> t;
    cin >> s;
    string mins = s;

    int j = s.size() - 1;
    char minChar = s[s.size() - 1];

    for (int i = s.size() - 1; i >= 0; i--) {
        if (s[i] < minChar) {
            minChar = s[i];
        }
        mins[j] = minChar;
        j--;
    }


    int i = 0;
    REPj(s.size()) {
        char min = mins[i];
        char e = s[j];
        while (!t.empty() && t.top() <= min) {
            u += t.top();
            t.pop();
        }

        if (e == min) {
            u += e;
        } else {
            t.push(e);
        }

        i++;
    }

    while (!t.empty()) {
        u += t.top();
        t.pop();
    }
    cout << u;

    return 0;
}
