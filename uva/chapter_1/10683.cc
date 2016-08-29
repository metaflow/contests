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

l strto24(string time) {
  l h = stol(time.substr(0, 2).c_str());
  l m = stol(time.substr(2, 2).c_str());
  l s = stol(time.substr(4, 2).c_str());
  l c = stol(time.substr(6, 2).c_str());
  // cerr << h << " " << m << " " << s << " " << c << endl;
  m += h * 60;
  s += m * 60;
  c += s * 100;
  return c;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  string s;
  while (cin >> s) {
    l c = strto24(s);
    l day = 24 * 60 * 60 * 100;
    // part of the day = c / (24 * 60 * 60 * 100)
    c *= 10;
    l h = c / day;
    c -= h * day;
    c *= 100;
    l m = c / day;
    c -= m * day;
    c *= 100;
    l s = c / day;
    c -= s * day;
    c *= 100;
    l cc = c / day;
    cout << setfill('0') << h << setw(2) << m << setw(2) << s << setw(2) << cc << endl;
    // cout << seconds << endl;
  }
}
