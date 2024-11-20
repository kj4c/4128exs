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
#define REP1j(n) for (int j = 1; j <= n; j++)i
#define REP1k(n) for (int k = 1; k <= n; k++)

ll n;


vector<ll> findPrimes(ll n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (ll i = 2; i * i <= n; ++i) {
        if (isPrime[i]) {
            // Mark multiples of i as not prime
            for (ll j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    vector<ll> primes;
    for (ll i = 2; i <= n; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

bool isprime(ll x) {
    if (x < 2) return false;

    for (ll f = 2; f*f <= x; f++)
        if (x % f == 0)
            return false;
    return true;
}

bool isDivisible(ll value, ll prime) {
    return value % prime == 0;
}

// this would divide 
ll divideUntilNotDivisible(ll value, ll prime) {
    while (isDivisible(value, prime)) {
        value /= prime;
    }

    return value;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;

    vector<ll> array;
    for (ll i = 0; i < n; ++i) {
        ll value; 
        cin >> value;
        array.push_back(value);
    }

    vector<ll> allPrimes = findPrimes(n);

    vector<ll> topRow(n);
    vector<ll> bottomRow(n);

    for (ll i = 0; i < n; ++i) {
        if (isprime(array[i])) {
            topRow[i] = -1;
            bottomRow[i] = -1;
        } else {
            bool divided = false;
            for (ll j = 0; j < allPrimes.size() && allPrimes[j] * allPrimes[j] <= array[i]; ++j) {
                if (isDivisible(array[i], allPrimes[j])) {
                    ll divisor = divideUntilNotDivisible(array[i], allPrimes[j]);
                    if (divisor != 1) {
                        topRow[i] = allPrimes[j];
                        bottomRow[i] = divisor;
                        divided = true;
                        break;
                    }
                }
            }

            if (!divided) {
                topRow[i] = -1;
                bottomRow[i] = -1;
            }
        }
    }

    for (ll i = 0; i < n; ++i) {
        cout << topRow[i] << " ";
    }
    cout << "\n";

    for (ll i = 0; i < n; ++i) {
        cout << bottomRow[i] << " ";

    }

    cout << "\n";

    return 0;
}