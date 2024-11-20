#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1e7 + 10;

int main() {
    int n;
    cin >> n;
    vector<int> row1(n, -1);
    vector<int> row2(n, -1);
    vector<int> prime1(N, -1);
    vector<int> prime2(N, -1);

    // sieve but only for first 2 for  memoery purposes
    for (int i = 2; i < N; i++) {
        if (prime1[i] == -1) {
            for (int j = i; j < N; j += i) {
                if (prime1[j] == -1) {
                    prime1[j] = i; 
                } else if (prime2[j] == -1 && prime1[j] != i) {
                    prime2[j] = i; 
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;

        row1[i] = prime1[a];
        row2[i] = prime2[a];
        if (row2[i] == -1) row1[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        cout << row1[i] << " ";
    }

    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << row2[i] << " ";
    }

    return 0;
}
