#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

const int I = 0;
const int V = 1;
const int X = 2;
const int L = 3;
const int C = 4;

const char digits[] = {'i', 'v', 'x', 'l', 'c'};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  vvi counts(101);
  for (ll i = 0; i < 101; i++) {
    auto &d = counts[i];
    if (i == 0) {
      d.resize(5);
      continue;
    }
    d = counts[i - 1];
    string s = "";
    switch (i / 10) {
      case 1: s += "x"; break;
      case 2: s += "xx"; break;
      case 3: s += "xxx"; break;
      case 4: s += "xl"; break;
      case 5: s += "l"; break;
      case 6: s += "lx"; break;
      case 7: s += "lxx"; break;
      case 8: s += "lxxx"; break;
      case 9: s += "xc"; break;
      case 10: s += "c"; break;
    }
    switch (i % 10) {
      case 1: s += "i"; break;
      case 2: s += "ii"; break;
      case 3: s += "iii"; break;
      case 4: s += "iv"; break;
      case 5: s += "v"; break;
      case 6: s += "vi"; break;
      case 7: s += "vii"; break;
      case 8: s += "viii"; break;
      case 9: s += "ix"; break;
    }
    for (auto c : s) {
      for (int i = 0; i < 5; i++) if (digits[i] == c) d[i]++;
    }
  }
  ll n;
  while (cin >> n, n) {
    auto &d = counts[n];
    cout << n << ": ";
    for (int i = 0; i < 5; i++) {
      if (i) cout << ", ";
      cout << d[i] << ' ' << digits[i];
    }
    cout << endl;
  }
}
