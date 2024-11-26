#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;
#define ll long long

const ll INF= 1e18;
// n: number of trees
// m: number of colors
// k: beauty of the color
int n, m, k;
vector<ll> trees;
vector<vector<ll>> paint;

int main() {
    cin >> n >> m >> k;

    trees.resize(n);
    paint.resize(n, vector<ll>(m));

    for (int i = 0; i < n; i++) {
        cin >> trees[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> paint[i][j];
        }
    }

    vector<vector<vector<ll>>> dp(n + 1, vector<vector<ll>>(k + 1, vector<ll>(m + 1, INF)));

    // base cases
    if (trees[0] != 0) {
        // tree already colored so set the cost is 0 paint
        dp[0][1][trees[0]] = 0;
    } else {
        //  give all the initial colors
        for (int i = 1; i <= m; i++) {
            dp[0][1][i] = paint[0][i - 1];
        }
    }

    // current index
    for (int i = 1; i < n; i++) {
        // try beauty scores
        for (int b = 1; b <= k; b++) {
            // try colors
            for (int prev_color = 1; prev_color <= m; prev_color++) {
                // if this point the beauty is not reachable
                if (dp[i - 1][b][prev_color] == INF) continue;

                // already colored tree, set it
                if (trees[i] != 0) {
                    int curr_color = trees[i];
                    if (curr_color == prev_color) {
                        dp[i][b][curr_color] = min(dp[i][b][curr_color], dp[i-1][b][prev_color]);
                    } else if (b + 1 <= k) {
                        dp[i][b + 1][curr_color] = min(dp[i][b + 1][curr_color], dp[i - 1][b][prev_color]);
                    }
                } else {
                    // color with every color
                    for (int current_color = 1; current_color <= m; current_color++) {
                        if (prev_color == current_color) {
                            // if its the same color, don't update beauty and add the paint for this color on it.
                            dp[i][b][current_color] = min(dp[i][b][current_color], dp[i-1][b][prev_color] + paint[i][current_color - 1]);
                            // check if the new beauty is possible
                        } else if (b + 1 <= k) {
                            dp[i][b + 1][current_color] = min(dp[i][b + 1][current_color], dp[i-1][b][prev_color] + paint[i][current_color - 1]);
                        }
                    }
                }
            }
        }
    }
    
    // find the answer for min
    ll min = INF;
    for (int i = 1; i <= m; i++) {
        if (dp[n - 1][k][i] < min) {
            min = dp[n - 1][k][i];
        }
    }

    if (min == INF) {
        cout << -1;
    } else {
        cout << min;
    }

    return 0;
}