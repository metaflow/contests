#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

default_random_engine source(random_device{}());

l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b)(source);
}

bool random_bool() {
  return random_in_range(0, 1) == 1;
}

string random_string(int length) {
  string s = "";
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size() - 1)];
  }
  return s;
}

bool stable(vl& v, l i) {
  return (v[i] == v[i - 1] || v[i] == v[i + 1]);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    vl v(n);
    for (l i = 0; i < n; i++) {
      cin >> v[i];
    }
    v.emplace_back(v.back());
    l f = 1;
    l m = 0;
    for (l i = 1; i < n + 1; i++) {
      if (v[i] != v[i - 1]) continue;
      l t = i - 1;
      l k = (t - f + 1) / 2;
      m = max(m, k);
      for (l j = 0; j < k; j++) {
        v[j + f] = v[f - 1];
      }
      for (l j = 0; j < k; j++) {
        v[t - j - 1] = v[t];
      }
      f = i + 1;
    }
    cout << m << endl;
    for (l i = 0; i < n; i++) {
      if (i) cout << " ";
      cout << v[i];
    }
    cout << endl;
  }
}
