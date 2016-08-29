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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, k;
  while (cin >> n >> k, n) {
    deque<ll> line;
    for (l i = 1; i <= n; i++) {
      line.emplace_back(i, 40);
    }
    l current_cash = 0, next_cache = 1;
    vl answer;
    while (!line.empty()) {
      ll x = line.front(); line.pop_front();
      if (current_cash == 0) {
        current_cash = next_cache;
        next_cache = next_cache % k + 1;
      }
      if (x.second <= current_cash) {
        answer.push_back(x.first);
        current_cash -= x.second;
      } else {
        line.emplace_back(x.first, x.second - current_cash);
        current_cash = 0;
      }
    }
    for (auto i : answer) {
      cout << setfill(' ') << setw(3) << i;
    }
    cout << endl;
  }
}
