#include <iostream>
#include <string>
#include <math.h>
#include <vector>
using namespace std;
typedef long long ll;

int main() {
    ll a, b, c, d;
    cin >> a;
    cin >> b;
    cin >> c;
    cin >> d;

    if (a == 0 && b == 0 && c == 0 && d == 0) {
        cout << "0\n";
        return 0;
    }

    ll numZeroes, numOnes, i;

    numZeroes = (1 + sqrt(1+8*a)) / 2;
    if (numZeroes * (numZeroes - 1) /2 != a) {
        cout << "impossible\n";
        return 0;
    }

    numOnes = (1 + sqrt( 1 + 8*d)) / 2;
    if (numOnes*(numOnes - 1)/2 != d) {
        cout << "impossible\n";
        return 0;
    }

    if (a == 0 && d == 0) {
        if (b == 1 && c == 0) {
            cout << "01" << endl;
        } else if (c == 1 && b == 0) {
            cout << "10" << endl;
        } else {
            cout << "impossible\n";
        }
        return 0;

    }

    if (b == 0 && c == 0) {
        if (a == 0) {
            for (int i = 1; i <= numOnes; i++) cout << "1";
        } else if ( d == 0) {
            for (int i = 1; i <= numZeroes; i++) cout << "0";
        } else {
            cout << "impossible\n";
        }
        return 0;
    }

    if (numZeroes * numOnes != b + c) {
        cout << "impossible" << endl;
        return 0;
    }

    ll quotient = b / numOnes;
    ll remainder = b % numOnes;
    for (i = 1; i <= quotient; i++) {
        cout << "0";
    }

    for (int i = 1; i <= numOnes - remainder; i++) {
        cout << "1";
    }

    if (quotient != numZeroes) {
        cout << "0";
    }

    for (i = 1; i <= remainder; i++) {
        cout << "1";
    }

    for (i = 1; i <= numZeroes - quotient - 1; i++) {
        cout << "0";
    }
    return 0;
}