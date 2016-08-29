#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 20000001;

vi v(MAX), p2(MAX), p5(MAX), vm(67108863 + 1);

int query_vm(int p, int l, int r, int f, int t) {
  if (l + 1 == r) return vm[p];
  if (l == f && r == t) return vm[p];
  int m = l + (r - l) / 2;
  int a = 1;
  if (f < m) a *= query_vm(2 * p, l, m, f, min(m, t));
  if (t > m) a *= query_vm(2 * p + 1, m, r, max(m, f), t);
  return a % 10;
}

int max_p = 0;

int build_vm(int p, int l, int r) {
  max_p = max(p, max_p);
  if (l + 1 == r) return vm[p] = v[l];
  int m = l + (r - l) / 2;
  vm[p] = (build_vm(2 * p, l, m) * build_vm(2 * p + 1, m, r)) % 10;
  return vm[p];
}

int build_fenvik(vi &v) {
  int s = v.size();
  for (int i = 1; i < s; i++) {
    int z = i + (i & (-i));
    if (z < s) v[z] += v[i];
  }
}

int req_fenvik(vi &v, int n) {
  int s = 0;
  while (n) {
    s += v[n];
    n -= (n & -n);
  }
  return s;
}

int p(int n, int m) {
  if (n == 0 || m == 0) return 1;
  ll t2 = 0, t5 = 0;
  t2 = req_fenvik(p2, n) - req_fenvik(p2, n - m);
  t5 = req_fenvik(p5, n) - req_fenvik(p5, n - m);
  ll a = query_vm(1, 1, MAX, n - m + 1, n + 1);
  int k = min(t2, t5);
  t2 -= k;
  t5 -= k;
  if (t2) a *= (2 << ((t2 + 3) % 4));
  if (t5) a *= 5;
  a %= 10;
  return a;
}



int main() {
  ll n, m;
  for (int i = 1; i < MAX; i++) {
    int &t = v[i];
    t = i;
    while (t % 2 == 0) {
      p2[i]++; t /= 2;
    }
    while (t % 5 == 0) {
      p5[i]++; t /= 5;
    }
    t %= 10;
  }

  build_fenvik(p2);
  build_fenvik(p5);
  build_vm(1, 1, MAX);
  while (cin >> n >> m) {
    cout << p(n, m) << endl;
  }
}
