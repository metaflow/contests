#include <bits/stdc++.h>

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

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

const l MAX_N = 300000;
const l MAX_M = 200;
l acc[MAX_N + 1];
l intervals[MAX_M];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc;
  cin >> tcc;
  acc[0] = 0;
  while (tcc--) {
    l n, m;
    cin >> n >> m;
    for (l i = 0; i < n; i++) {
      cin >> acc[i + 1];
      acc[i + 1] += acc[i];
    }
    for (l i = 0; i < m; i++) cin >> intervals[i];
    vl score(n);
    vl score_(n);
    for (l i = 0; i <= n - intervals[m-1]; i++)
      score[i] = acc[i + intervals[m-1]] - acc[i];
    for (l i = m - 2; i >= 0; i--) {
      // LOG << i << endl;
      l j;
      deque<ll> d;  // [(value * position)]
      l t = intervals[i];
      for (j = 0; j <= t - intervals[i + 1] - 2; j++) {
        while ((not d.empty()) and (d.back().first <= score[j])) d.pop_back();
        d.emplace_back(score[j], j);
      }
      // LOG << "a\n";
      for (l k = 0; k <= n - t; k++) {
        while ((not d.empty()) and (d.front().second <= k)) d.pop_front();
        while ((not d.empty()) and (d.back().first <= score[j])) d.pop_back();
        d.emplace_back(score[j], j);
        j++;
        score_[k] = acc[k + t] - acc[k] - d.front().first;
      }
      // LOG << "b\n";
      score.swap(score_);
    }
    l answer = 0;
    for (l i = 0; i <= n - intervals[0]; i++) {
      answer = max(answer, score[i]);
    }
    cout << answer << '\n';
  }
}
