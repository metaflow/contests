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
const l e0=1, e3=1000, e5=100000, e6=e3*e3, e7=10*e6, e8=10*e7, e9=10*e8;
#define ALL(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

l max_subarray_brute(vl& a, l from, l to) {
  l best_sum = -10000;
  F(i, from, to) {
    l sum = 0;
    F(j, i, a.size()) {
      sum += a[j];
      best_sum = max(best_sum, sum);
    }
  }
  return best_sum;
}

l max_crossing_subarray(vl& a, l from, l m, l to) {
  l best = -INF;
  l s = 0;
  for (l i = m - 1; i >= from; i--) {
    s += a[i];
    best = max(s, best);
  }
  s = 0;
  for (l i = m; i < to; i++) {
    s += a[i];
    best = max(s, best);
  }
  return best;
}

l max_subarray_recursive(vl& a, l from, l to) {
  if (to - from == 1) return a[from];
  l m = from + (to - from) / 2;
  return max(max_crossing_subarray(a, from, m, to),
             max(max_subarray_recursive(a, from, m),
                 max_subarray_recursive(a, m, to)));
}

l max_subarray_recursive2(vl& a, l from, l to) {
  if (to - from < 20) return max_subarray_brute(a, from, to);
  l m = from + (to - from) / 2;
  return max(max_crossing_subarray(a, from, m, to),
             max(max_subarray_recursive(a, from, m),
                 max_subarray_recursive(a, m, to)));
}

l max_subarray_linear(vl& a, l from, l to) {
  l best = -INF;
  l s = 0;
  F(i, from, to) {
    s = max(s + a[i], a[i]);
    best = max(best, s);
  }
  return best;
}

l now() {
  return chrono::high_resolution_clock::now().time_since_epoch().count();
}

default_random_engine source(chrono::system_clock::now().time_since_epoch().count());

// [a, b)
l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b - 1)(source);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  for (l i = 1; i < 30; i++) {
    vl a(i);
    F(j, 0, i) {
      a[j] = random_in_range(-100, 100);
    }
    auto start = chrono::high_resolution_clock::now();
    vl r;
    F(j, 0, 100000) {
      l m = max_subarray_brute(a, 0, a.size());
      if (m < -INF) continue;
      r.push_back(m);
    }
    auto end = chrono::high_resolution_clock::now();
    cout << setw(6) << i << ' '
         << setw(6)
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << ' ';
    start = chrono::high_resolution_clock::now();
    F(j, 0, 100000) {
      l m = max_subarray_recursive(a, 0, a.size());
      if (m < -INF) continue;
      r.push_back(m);
    }
    end = chrono::high_resolution_clock::now();
    cout << setw(6) << chrono::duration_cast<chrono::milliseconds>(end - start).count() << ' ';
    start = chrono::high_resolution_clock::now();
    F(j, 0, 100000) {
      l m = max_subarray_recursive2(a, 0, a.size());
      if (m < -INF) continue;
      r.push_back(m);
    }
    end = chrono::high_resolution_clock::now();
    cout << setw(6) << chrono::duration_cast<chrono::milliseconds>(end - start).count() << ' ';
    start = chrono::high_resolution_clock::now();
    F(j, 0, 100000) {
      l m = max_subarray_linear(a, 0, a.size());
      if (m < -INF) continue;
      r.push_back(m);
    }
    end = chrono::high_resolution_clock::now();
    cout << setw(6) << chrono::duration_cast<chrono::milliseconds>(end - start).count() << ' ';
    cout << '\n';

  }
}
