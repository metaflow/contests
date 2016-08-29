#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 10000;

vi matrix_multiply(vi &a, vi &b) {
  vi r(4);
  r[0] = (a[0] * b[0] + a[1] * b[2]) % MAX;
  r[1] = (a[0] * b[1] + a[1] * b[3]) % MAX;
  r[2] = (a[2] * b[0] + a[3] * b[2]) % MAX;
  r[3] = (a[2] * b[1] + a[3] * b[3]) % MAX;
  return r;
}

vi matrix_power(vi& m, int n) {
  vi r;
  if (n == 1) {
    r = m;
    return r;
  }
  if (n % 2 == 0) {
    r = matrix_power(m, n / 2);
    return matrix_multiply(r, r);
  }
  r = matrix_power(m, n - 1);
  return matrix_multiply(m, r);
}

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    int a, b, n, m;
    cin >> a >> b >> n >> m;
    vi A = {b, a, 0, 0};
    vi B = {1, 1, 1, 0};
    if (n > 0) {
      B = matrix_power(B, n);
      A = matrix_multiply(A, B);
    }
    int q = 1;
    while (m--) q *= 10;
    cout << A[1] % q << endl;
  }
}

// time 32m
