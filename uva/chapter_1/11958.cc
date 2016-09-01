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
const l minutes_in_day = 24 * 60;

l read_time(string s) {
  l h = stol(s.substr(0, 2).c_str());
  l m = stol(s.substr(3, 2).c_str());
  return h * 60 + m;
}

l solve_case() {
  l buses; cin >> buses;
  string s; cin >> s;
  l now = read_time(s);
  l best = INF;
  for (l i = 0; i < buses; i++) {
      cin >> s;
      l arrival = read_time(s);
      l travel; cin >> travel;
      best = min(best, (arrival - now + minutes_in_day) % minutes_in_day + travel);
  }
  return best;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc; cin >> tcc;
  for (l tc = 1; tc <= tcc; tc++) {
      cout << "Case " << tc << ": ";
      cout << solve_case() << endl;
  }
}
