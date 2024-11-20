#include <iostream>
#include <cmath>  // For sqrt
using namespace std;


int main() {
    long long n;
    long long k;

    // n is num days
    cin >> n;

    // k is unused tix
    cin >> k;

    // quadratic formula derived from
    /*
    (d*(d+1))/2 - (n - d) = k

    n - d is the number of days spent booking activiities

    d^2 + d - 2(n - d) = 2k

    d^2 + 3d - 2n - 2k = 0

    d^2 + 3d -2(n + k) = 0;

    d = (-b + sqrt(b^2 - 4ac))/(2a);
    
    */
    long long a = 1;
    long long b = 3;
    long long c = -2 * (n + k);

    long long d = (-b + sqrt((b*b) - 4*(a)*(c)))/(2*(a));

    cout << (n - d) << endl;
    
    return 0;
}
