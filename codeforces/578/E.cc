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
    set<l> R, L;
    l n = s.size();
    for (l i = 0; i < n; i++) {
      if (s[i] == 'R') {
        R.emplace(i + 1);
      } else {
        L.emplace(i + 1);
      }
    }
    if ((R.size() != L.size() && R.size() < L.size()) ||
        (R.size() == L.size() && (*R.begin()) > (*L.begin()))) {
      swap(R, L);
    }
    l p = 0;
    l answer = 0;
    vl solution(n);
    for (l i = 0; i < n; i++) {
      auto b = R.lower_bound(p);
      if (b == R.end()) {
        answer++;
        b = R.begin();
      }
      p = *b;
      solution[i] = p;
      R.erase(b);
      swap(L, R);
    }
    cout << answer << endl;
    // cout << solution[0];
    // for (l i = 1; i < n; i++) cout << " " << solution[i];
    // cout << endl;
  }
}
