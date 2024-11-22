#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

long long max_prefixes(int n, long long k, const string& s, const string& t) {
    // We will keep track of the number of distinct stringse we have processed
    long long num_strings = 0;

    // Find the first position where s and t differ
    int first_diff = -1;
    for (int i = 0; i < n; ++i) {
        if (s[i] != t[i]) {
            first_diff = i;
            break;
        }
    }

    // If there's no difference, all strings are identical, so the number of distinct prefixes is n.
    if (first_diff == -1) {
        return min(static_cast<long long>(n), k);
    }

    // Start counting distinct prefixes
    long long total_prefixes = 0;

    // Count distinct prefixes from the fixed part up to the first differing character
    total_prefixes += first_diff + 1;  // Prefixes up to the first differing point

    // Now calculate the potential number of distinct prefixes after the first differing position
    long long range = 1;  // We start with one possibility (the first differing character)
    long long extra_strings = 0;

    // Simulate exponential growth of possible strings after first_diff
    for (int i = first_diff + 1; i < n; ++i) {
        range *= 2;  // Every position doubles the number of possibilities (a or b)
        extra_strings += range;
        if (extra_strings >= k) {
            // If we exceed k strings, we limit ourselves to k
            extra_strings = k - (num_strings + 1);  // Remaining strings we can select
            break;
        }
    }

    // Now total strings selected is bounded by k
    num_strings += min(extra_strings, k - num_strings);

    // Every selected string can generate prefixes
    total_prefixes += extra_strings;  // Add the number of distinct prefixes from the extra strings

    return total_prefixes;
}

int main() {
    int n;
    long long k;
    string s, t;

    // Input reading
    cin >> n >> k;
    cin >> s >> t;

    // Output the result
    cout << max_prefixes(n, k, s, t) << endl;

    return 0;
}
