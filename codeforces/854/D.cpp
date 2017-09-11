#if defined(LOCAL)
#define PROBLEM_NAME "D"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) debug(x)
#else
#define L(x, ...) (x)
#include <bits/stdc++.h>
#endif

using namespace std;
using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)

struct Flight {
  l day, from, to, price;
};

void solve(istream& cin, ostream& cout) {
  l n, m, k; cin >> n >> m >> k;
  vvll out_by_price(n);
  vll in_by_day, out_by_day;
  vector<Flight> flights(m);
  vector<bool> bad(m);
  F(i, 0, m) {
    auto& f = flights[i];
    cin >> f.day >> f.from >> f.to >> f.price;
    if (f.from == 0) {
      out_by_day.emplace_back(f.day, i);
      out_by_price[f.to - 1].emplace_back(f.price, i);
    } else {
      in_by_day.emplace_back(f.day, i);
    }
  }
  bool ok = true;
  l total_out_price = 0;
  sort(all(in_by_day));
  sort(all(out_by_day));
  // L("in_by_day", in_by_day);
  F(i, 0, n) {
    if (out_by_price[i].empty()) { ok = false; break; }
    sort(all(out_by_price[i]));
    total_out_price += out_by_price[i][0].first;
  }
  vl out_pos(n);
  vl price_in(n, -1);
  l answer = INF;
  l j = 0;
  l total_in_count = 0, total_in_price = 0;
  bool no_out = false;
  if (ok)
  for (auto p : in_by_day) {
    l t = p.first;
    while (j < out_by_day.size() and out_by_day[j].first <= t + k) {
      bad[out_by_day[j].second] = true;
      auto f = flights[out_by_day[j].second];
      l c = f.to - 1;
      while (out_pos[c] + 1 < out_by_price[c].size()
             and bad[out_by_price[c][out_pos[c]].second]) {
        total_out_price -= out_by_price[c][out_pos[c]].first;
        out_pos[c]++;
        total_out_price += out_by_price[c][out_pos[c]].first;
      }
      if (bad[out_by_price[c][out_pos[c]].second]) { no_out = true; break; }
      j++;
    }
    if (no_out) break;
    auto f = flights[p.second];
    l c = f.from - 1;
    if (price_in[c] == -1) {
      price_in[c] = f.price;
      total_in_count++;
      total_in_price += f.price;
    } else {
      if (price_in[c] > f.price) {
        total_in_price -= price_in[c];
        price_in[c] = f.price;
        total_in_price += price_in[c];
      }
    }
    if (total_in_count == n) answer = min(answer, total_in_price + total_out_price);
  }
  if (answer == INF) answer = -1;
  cout << answer << lf;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
