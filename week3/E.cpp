#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;

int main() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;

    vector<vector<int>> cnt(m, vector<int>(m, 0));
    for (int i = 1; i < n; i++) {
        int prev = s[i - 1] - 'a';
        int curr = s[i] - 'a';
        cnt[prev][curr]++;
        cnt[curr][prev]++;
    }

    int subsets = 1 << m;

    // dp is min slowness for given mask of letters
    vector<int> dp(subsets, INF);
    dp[0] = 0;

    // this will count how many bits are in each mask
    vector<int> totalBits(subsets, 0);
    for (int msk = 1; msk < subsets; msk++) {
        totalBits[msk] = totalBits[msk & (msk - 1)] + 1;
    }

    // add up all the transitions for each element x for each mask
    vector<vector<int>> d(subsets, vector<int>(m, 0));
    for (int msk = 1; msk < subsets; msk++) {
        for (int x = 0; x < m; x++) {
            if ((msk >> x) & 1) {
                for (int y = 0; y < m; y++) {
                    d[msk][y] += cnt[x][y];
                }
            }
        }
    }

    for (int msk = 0; msk < subsets; msk++) {
        for (int x = 0; x < m; x++) {
            // x already in mask
            if ((msk >> x) & 1) continue;
            // add it to the new mask
            int nmsk = msk | (1 << x);
            // current position for X 
            int pos = totalBits[msk]; 
            // current position * 
            // (amount of transitions with all the elements in the mask - amount of transitions with all elements not in mask)
            dp[nmsk] = min(dp[nmsk], dp[msk] + pos * (d[msk][x] - d[subsets - 1 - nmsk][x]));
        }
    }

    cout << dp[subsets - 1] << endl;

    return 0;
}
