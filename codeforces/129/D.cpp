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
const l e0 = 1, e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;
#define ALL(x) begin(x), end(x)

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr
const l MAX = 26;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  string s; l k;
  while (cin >> s >> k) {
    l n = s.size();
    if (k > (n + 1) * n / 2) {
      cout << "No such line.\n";
      continue;
    }
    vl v; for (auto c : s) v.emplace_back(c - 'a');
    vl starts(n); iota(ALL(starts), 0);
    string answer;
    for (l pos = 0; k > 0; pos++) {
      vl sym(MAX), suff(MAX);
      for (auto i : starts) {
        sym[v[i + pos]]++;
        suff[v[i + pos]] += n - i - pos;
      }
      for (l i = 0; i < MAX; i++) {
        if (suff[i] < k) { k -= suff[i]; continue; }
        k -= sym[i];
        answer += 'a' + i;
        for (l j = starts.size() - 1; j >= 0; j--) {
          if (starts[j] + pos + 1 >= n or v[starts[j] + pos] != i) {
            swap(starts[j], starts.back());
            starts.pop_back();
          }
        }
        break;
      }
    }
    cout << answer << '\n';
  }
}
