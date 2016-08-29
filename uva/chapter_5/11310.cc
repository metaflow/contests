#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 41;

llu memo[MAX];

llu f(int n) {
  if (n < 0) return 0;
  llu &r = memo[n];
  if (r == 0) {
    if (n == 0 || n == 1) return r = 1;
    r = 2 * f(n - 3) + f(n - 1) + 4 * f(n - 2);
  }
  return r;
}

int main() {
  fill_n(memo, MAX, 0);
  int tcc;
  cin >> tcc;
  while (tcc--) {
    int n;
    cin >> n;
    cout << f(n) << endl;
  }
}
