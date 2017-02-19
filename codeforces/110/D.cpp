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

l intersect(l a, l b, l c, l d) {
  return max((l)0, min(b,d) - max(a,c) + 1);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  vl lucky = {0, 4, 7};
  {
    l from = 1;
    for (l i = 0; i < 9; i++) {
      l n = lucky.size();
      for (l j = from; j < n; j++) {
        lucky.emplace_back(lucky[j] * 10 + 4);
        lucky.emplace_back(lucky[j] * 10 + 7);
      }
      from = n;
    }
  }
  l pl, pr, ul, ur, k;
  while (cin >> pl >> pr >> ul >> ur >> k) {
    auto a = lucky.begin();
    auto b = ((k + 1) < lucky.size()) ? (lucky.begin() + k + 1) : lucky.end();
    l total = 0;
    while (b != lucky.end()) {
      l al = *a + 1, ar = *(a + 1), bl = *(b - 1), br = *b - 1;
      l d = intersect(al, ar, pl, pr) * intersect(bl, br, ul, ur) +
        intersect(al, ar, ul, ur) * intersect(bl, br, pl, pr);
      if (k == 1 and intersect(pl, pr, ar, ar) and intersect(ul, ur, ar, ar)) d--;
      total += d;
      a++;
      b++;
    }
    // LOG << "total" << total << endl;
    cout.precision(12);
    cout << fixed
         << ((double)total) / ((double)((pr - pl + 1) * (ur - ul + 1)))
         << '\n';
  }
}
