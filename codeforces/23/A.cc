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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  string s;
  while (cin >> s) {
    l best = 0;
    for (l i = 0; i < s.size(); i++) {
      for (l j = 1; j + i <= s.size(); j++) {
        string a = s.substr(i, j);
        if (s.find(a, i + 1) != string::npos) best = max(best, j);
      }
    }
    cout << best << endl;
  }
}
