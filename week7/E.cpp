#include <iostream>
#include <cassert>

using namespace std;

const int MOD = 998244353;

// class for modular arithmetic
class ModInt {
public:
    int val;

    ModInt(long long v = 0) {
        if (v < 0) v = v % MOD + MOD;
        if (v >= MOD) v %= MOD;
        val = int(v);
    }

    ModInt& operator += (const ModInt& other) {
        val += other.val;
        if (val >= MOD) val -= MOD;
        return *this;
    }

    ModInt& operator -= (const ModInt& other) {
        val -= other.val;
        if (val < 0) val += MOD;
        return *this;
    }

    ModInt& operator *= (const ModInt& other) {
        val = int((long long) val * other.val % MOD);
        return *this;
    }

    friend ModInt power(ModInt a, long long b) {
        ModInt res = 1;
        while (b > 0) {
            if (b % 2 == 1) res *= a;
            a *= a;
            b /= 2;
        }
        return res;
    }

    ModInt inv() const {
        return power(*this, MOD - 2);
    }

    ModInt& operator /= (const ModInt& other) {
        return (*this) *= other.inv();
    }

    friend ModInt operator + (ModInt a, const ModInt& b) { return a += b; }
    friend ModInt operator - (ModInt a, const ModInt& b) { return a -= b; }
    friend ModInt operator * (ModInt a, const ModInt& b) { return a *= b; }
    friend ModInt operator / (ModInt a, const ModInt& b) { return a /= b; }

    friend ostream& operator << (ostream& os, const ModInt& mi) {
        return os << mi.val;
    }
};

const int MAXN = 5005;

int n;
int elements[MAXN];
//frequency of each number
int frequency[MAXN];   
// prefix sum of frequencies     
int prefixFrequency[MAXN];
// modular inverses
ModInt inverse[MAXN];
ModInt noFree[MAXN][MAXN];  
ModInt freePick[MAXN][MAXN];

void solve() {
    cin >> n;

    // precompute modular inverses
    for (int i = 1; i <= n; ++i) {
        inverse[i] = ModInt(1) / ModInt(i);
    }

    //count frequencies
    for (int i = 0; i < n; ++i) {
        cin >> elements[i];
        frequency[elements[i]]++;
    }

    // prefix sums
    for (int i = 1; i <= n + 1; ++i) {
        prefixFrequency[i] = prefixFrequency[i - 1] + frequency[i - 1];
    }

    for (int i = n; i >= 1; --i) {
        for (int j = 0; j <= prefixFrequency[i]; ++j) {
            int totalRemaining = j + (n - prefixFrequency[i]);

            if (totalRemaining == 0) continue;

            // calculate noFree[i][j] the value when not given a free pick
            noFree[i][j] = ModInt(totalRemaining - j - frequency[i]) * inverse[totalRemaining] * freePick[i + 1][j + frequency[i]];

            if (totalRemaining > 1) {
                noFree[i][j] += ModInt(frequency[i]) * inverse[totalRemaining] *
                    (ModInt(frequency[i] - 1) * inverse[totalRemaining - 1]
                    + ModInt(totalRemaining - frequency[i] - j) * inverse[totalRemaining - 1] * freePick[i + 1][j + frequency[i] - 1]);
            }

            // freepick[i][j]
            if (totalRemaining != j) {
                freePick[i][j] = ModInt(totalRemaining - j - frequency[i]) * inverse[totalRemaining - j] * freePick[i + 1][j + frequency[i]];

                if (totalRemaining > 1) {
                    freePick[i][j] += ModInt(frequency[i]) * inverse[totalRemaining - j] *
                        (ModInt(frequency[i] - 1) * inverse[totalRemaining - 1]
                        + ModInt(totalRemaining - frequency[i] - j) * inverse[totalRemaining - 1] * freePick[i + 1][j + frequency[i] - 1]);
                }
            }
        }
    }

    // output the result
    cout << noFree[1][0] << '\n';
}

int main() {
    solve();
    return 0;
}
