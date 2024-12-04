#include <vector>
#include <iostream>

using namespace std;
typedef long long ll;

const ll mod = 1000 * 1000 * 1000 + 7;
/*
 * matrix exp
 */

// Implementation for square matrices.
struct Matrix {
  int n;
  vector<vector<long long>> v;
  Matrix(int _n) : n(_n) {
    v.resize(n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        v[i].push_back(0);
  }

  Matrix operator*(const Matrix &o) const {
    Matrix res(n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        for (int k = 0; k < n; k++) {
          res.v[i][j] += v[i][k] % mod * o.v[k][j] % mod;
          res.v[i][j] %= mod;
        }
    return res;
  }

  static Matrix getIdentity(int n) {
    Matrix res(n);
    for (int i = 0; i < n; i++)
      res.v[i][i] = 1;
    return res;
  }
  
  Matrix operator^(long long k) const {
    Matrix res = Matrix::getIdentity(n);
    Matrix a = *this;
    while (k) { // building up in powers of two
      if (k&1) res = res*a;
      a = a*a;
      k /= 2;
    }
    return res;
  }
};



int main() {
    ll N, M;

    cin >> N >> M;

    Matrix mat(M);
    mat.v[0][0] = 1;
    mat.v[0][M - 1] = 1;

    // diagonals;
    for (ll i = 1; i < M; i++) {
        mat.v[i][i - 1] = 1;
    }

    // find 
    mat = mat^N;

    cout << mat.v[0][0] % mod;

}