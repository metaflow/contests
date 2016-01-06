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

vl as;
l n;

vl lis_frames(function<bool(l)> p) {
  vl seq;
  vl per_frame;
  per_frame.push_back(0);
  for (l k = 0; k < n; k++) {
    for (l i = 0; i < n; i++) {
      auto x = as[i];
      if (!p(x)) continue;
      auto q = upper_bound(seq.begin(), seq.end(), x);
      if (q == seq.end()) {
        seq.push_back(x);
      } else {
        *q = x;
      }
    }
    per_frame.push_back(seq.size());
  }
  return per_frame;
}

const l MAX = 500;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  while (cin >> n) {
    l t; cin >> t;
    as.resize(n);
    vl counts(MAX);
    for (l i = 0; i < n; i++) cin >> as[i];
    for (auto a : as) counts[a]++;
    vb checked(MAX);
    l best = 0;
    for (int i = 0; i < n; i++) {
      auto x = as[i];
      if (checked[x]) continue;
      checked[x] = true;
      vl lis_start = lis_frames(bind2nd(less_equal<l>(), x));
      vl lis_end =   lis_frames(bind2nd(greater_equal<l>(), x));
      for (l a = 0; a <= min(n, t); a++) {
        for (l b = 0; b <= min(t - a, n); b++) {
          best = max(best, lis_start[a] + counts[x] * (t - a - b) + lis_end[b]);
        }
      }
    }
    cout << best << endl;
  }
}
