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

map<string, l> m;
map<string, string> A;

string solve(string s);

string abbr(string s) {
  // cout << "abbr " << s << endl;
  if (A.count(s)) return A[s];
  if (s[0] > '1') return s;
  l j = s.size() - 1;
  while (j > 0) {
    // cout << j << endl;
    if (solve(s.substr(j)) == s) return s.substr(j);
    j--;
  }
  return s;
}

string solve(string s) {
  if (m.count(s)) {
    return to_string(m[s]);
  } else {
    if (s[0] == '0') {
      return "1" + s;
    }
    if (stoi(s) < 1989) return "1" + s;
    // cout << abbr(s) << endl;
    if (abbr(s) != s) s = "1" + s;
    // cout << "-> " << s << endl;
    return s;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);

  for (l i = 1989; i < 10000; i++) {
    auto s = to_string(i);
    l j = s.size() - 1;
    while (m.count(s.substr(j))) j--;
    m[s.substr(j)] = i;
    A[s] = s.substr(j);
  }

  l n;
  while (cin >> n) {
    while (n--) {
      string s; cin >> s;
      s = s.substr(4);
      cout << solve(s) << endl;
    }
  }
}
