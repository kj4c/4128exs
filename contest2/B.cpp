#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <tuple>
#include <algorithm>
#include <map>
#include <set>
#include <deque>
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

// find the minimum for each row
vector<int> sliding_window_min(const vector<int>& arr, int k) {
    deque<int> dq;
    vector<int> result;

    // loop thru the entire row, and push the minimal value of each
    // possible grid of size k
    for (int i = 0; i < arr.size(); i++) {

        // if out of bounds for current window
        if (!dq.empty() && dq.front() == i - k) {
            dq.pop_front();
        }

        // if the new element is element is the new minimal get rid of 
        // existing minimals
        while (!dq.empty() && arr[dq.back()] >= arr[i]) {
            dq.pop_back();
        }

        // add it to the dq
        dq.push_back(i);

        // if alrdy processed k elements then put the front
        // most element in deque into my results vector
        if (i >= k - 1) {
            result.push_back(arr[dq.front()]);
        }
    }

    return result;
}

// same but for max
vector<int> sliding_window_max(const vector<int>& arr, int k) {
    deque<int> dq;
    vector<int> result;

    for (int i = 0; i < arr.size(); i++) {
        if (!dq.empty() && dq.front() == i - k) {
            dq.pop_front();
        }

        while (!dq.empty() && arr[dq.back()] <= arr[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        if (i >= k - 1) {
            result.push_back(arr[dq.front()]);
        }
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int r, c, k;
    cin >> r >> c >> k;

    vector<vector<int>> grid(r, vector<int>(c));
    vector<int> sorted_vals;

    // read the grid
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int val;
            cin >> val;
            grid[i][j] = val;
            sorted_vals.push_back(val);
        }
    }

    sort(sorted_vals.begin(), sorted_vals.end());

    // find all the min and max for each row.
    vector<vector<int>> row_min(r), row_max(r);

    for (int i = 0; i < r; i++) {
        row_min[i] = sliding_window_min(grid[i], k);
        row_max[i] = sliding_window_max(grid[i], k);
    }

    // create 2d array for the max and min for each possible grid
    vector<vector<int>> grid_mins(r - k + 1, vector<int>(c - k + 1));
    vector<vector<int>> grid_maxs(r - k + 1, vector<int>(c - k + 1));

    for (int j = 0; j < c - k + 1; j++) {
        vector<int> colMin, colMax;

        for (int i = 0; i < r; i++) {
            // get the minimum for the row at the specified col
            colMin.push_back(row_min[i][j]);
            colMax.push_back(row_max[i][j]);
        }

        // will find the minimum n max in the entire grid now cus you 
        // account for the min n max in row and then also the cols.
        vector<int> min_vals = sliding_window_min(colMin, k);
        vector<int> max_vals = sliding_window_max(colMax, k);

        // save dat shi
        for (int i = 0; i < r - k + 1; i++) {
            grid_mins[i][j] = min_vals[i];
            grid_maxs[i][j] = max_vals[i];
        }
    }

    // brute force checkin
    for (int i = 0; i <= r - k; i++) {
        for (int j = 0; j <= c - k; j++) {
            int minVal = grid_mins[i][j];
            int maxVal = grid_maxs[i][j];

            int left = lower_bound(sorted_vals.begin(), sorted_vals.end(), minVal) - sorted_vals.begin();
            int right = upper_bound(sorted_vals.begin(), sorted_vals.end(), maxVal) - sorted_vals.begin();

            // numbers in between the ranges
            int range = right- left;

            // if the range equals the total amount in the grid
            // means all other values lay outside this range.
            if (range == k * k) {
                cout << "YES" << endl;
                cout << i + 1 << " " << j + 1 << endl;
                return 0;
            }
        }
    }

    cout << "NO" << endl;
    return 0;
}
