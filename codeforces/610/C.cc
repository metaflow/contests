#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

void print_solution(vvl& s) {
  for (auto u : s) {
    for (auto i : u) {
      if (i > 0) {
        cout << "+";
      } else {
        cout << "*";
      }
    }
    cout << endl;
  }
}

l multiply(vl a, vl b) {
  l n = a.size();
  l t = 0;
  for (l i = 0; i < n; i++) {
    t += a[i] * b[i];
  }
  return t;
}

bool check(vvl s, l k) {
  l n = s.size();
  l t = 1; for (l i = 0; i < k; i++) t *= 2;
  if (n != t) return false;
  if (s[0].size() != t) return false;
  for (l i = 0; i < n; i++) {
    for (l j = i + 1; j < n; j++) {
      if (multiply(s[i], s[j])) return false;
    }
  }
  return true;
}

vvl generate(l k) {
  l n = 1; for (l i = 0; i < k; i++) n *= 2;
  l p = n;
  vvl s(1, vl(n, 1));
  for (l i = 0; i < k; i++) {
    l t = s.size();
    p /= 2;
    for (l j = 0; j < t; j++) {
      vl u = s[j];
      for (l e = 0; e < n; e++) {
        if ((e / p) % 2) u[e] *= -1;
      }
      s.push_back(u);
    }
  }
  return s;
}

vvl generate2(l k) {
  vvl a;
  a.emplace_back(vl(1,1));
  for (l i = 0; i < k; i++) {
    l n = a[0].size();
    vvl b;
    for (auto p : a) {
      vl q;
      q.insert(q.end(), p.begin(), p.end());
      q.insert(q.end(), p.begin(), p.end());
      assert(q.size() == n * 2);
      b.push_back(q);
      for (l j = 0; j < n; j++) q[j] *= -1;
      b.push_back(q);
    }
    swap(a, b);
    // print_solution(a);
  }
  return a;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l k;
  while (cin >> k) {
    auto s = generate2(k);
    print_solution(s);
  }
  return 0;
  for (l k = 0; k < 10; k++) {
    vvl s = generate2(k);
    cout << k;
    if (check(s, k)) {
      cout << " ok" << endl;
    } else {
      cout << endl;
      print_solution(s);
      cout << " bad" << endl;
      break;
    }
  }
}
