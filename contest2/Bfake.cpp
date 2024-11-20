#include <bits/stdc++.h>
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

// sliding window type hsi

ll r, c, k;

// this would compute the smallest in the 1d array 
vector<ll> sliding_window_min(const vector<ll> &arr, int window_size) {
    vector<ll> answer;
    deque<int> dq;
    for(int i = 0; i < arr.size(); ++i){
        while(!dq.empty() && arr[dq.back()] >= arr[i]){
            dq.pop_back();
        }
        
        dq.push_back(i);
        while(!dq.empty() && dq.front() <= i - window_size){
            dq.pop_front();
        }

        if(i >= window_size - 1){
            answer.push_back(arr[dq.front()]);
        }
    }
    return answer;
}

// same code as min but it would js find hte sliding window for hte lragest for 1d
// this would compute the maximum in this one d arrayand the window can js be k
vector<ll> sliding_window_max(const vector<ll> &arr, int window_size) {
    vector<ll> answer;
    deque<int> dq;

    for(int i = 0; i < arr.size(); ++i){
        while(!dq.empty() && arr[dq.back()] <= arr[i]){
            dq.pop_back();
        }

        dq.push_back(i);
        while(!dq.empty() && dq.front() <= i - window_size){
            dq.pop_front();
        }

        if(i >= window_size - 1){
            answer.push_back(arr[dq.front()]);
        }
    }
    return answer;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // scan it in for hte array
    cin >> r >> c >> k;
    vector<vector<ll>> g(r, vector<ll>(c));
    for(int i = 0; i < r; ++i){
        for(int j = 0; j < c; ++j){
            cin >> g[i][j];
        }
    }

    // this gives me all the possible values linearly.
    vector<ll> all_vals;
    all_vals.reserve(r * c);
    for(int i = 0; i < r; ++i){
        for(int j = 0; j < c; ++j){
            all_vals.push_back(g[i][j]);
        }
    }

    // this would sort all of thevalues out  there
    vector<ll> sorted_vals = all_vals;
    sort(sorted_vals.begin(), sorted_vals.end());

    vector<vector<ll>> minRow(r, vector<ll>());
    vector<vector<ll>> maxRow(r, vector<ll>());

    // this would find the minimum for each row 
    for(int i = 0; i < r; ++i){
        minRow[i] = sliding_window_min(g[i], k);
        maxRow[i] = sliding_window_max(g[i], k);
    }

    // this would find the number of sub rows
    int num_subrows = r - k + 1;
    int num_subcols = c - k + 1;
    vector<vector<ll>> minGrid(num_subrows, vector<ll>(num_subcols));
    vector<vector<ll>> maxGrid(num_subrows, vector<ll>(num_subcols));

    // this would find the number of subcolumns
    for(int j = 0; j < num_subcols; ++j){
        vector<ll> col_min;
        vector<ll> col_max;

        // this would find hte col and the col
        col_min.reserve(r);
        col_max.reserve(r);


        // this would push the column min based on the minimum row and max row
        for(int i = 0; i < r; ++i){
            col_min.push_back(minRow[i][j]);
            col_max.push_back(maxRow[i][j]);
        }

        // this would from the columns of htem inimum this would also find the smallest for htis case
        // binary search for the sliding minimum 
        vector<ll> sliding_min_vals = sliding_window_min(col_min, k);
        vector<ll> sliding_max_vals = sliding_window_max(col_max, k);

        for(int i = 0; i < sliding_min_vals.size(); ++i){
            minGrid[i][j] = sliding_min_vals[i];
            maxGrid[i][j] = sliding_max_vals[i];
        }
    }

    // find if theres a possible x and y
    bool found = false;
    int res_i = -1, res_j = -1;

    // this would for loop
    for(int i = 0; i < num_subrows && !found; ++i){
        for(int j = 0; j < num_subcols && !found; ++j){
            
            ll subgridMin = minGrid[i][j];
            ll subgridMax = maxGrid[i][j];

            // this would find hte the left and right for this case and see if its in the range 
            // based on the sorted values 
            int left = lower_bound(sorted_vals.begin(), sorted_vals.end(), subgridMin) - sorted_vals.begin();
            int right = upper_bound(sorted_vals.begin(), sorted_vals.end(), subgridMax) - sorted_vals.begin();
            int count_in_range = right - left;

            // see if its in range
            if(count_in_range == k * k){
                found = true;
                res_i = i + 1;
                res_j = j + 1;
            }
        }
    }

    if(found){
        cout << "YES\n" << res_i << " " << res_j;
    }
    else{
        cout << "NO";
    }
}