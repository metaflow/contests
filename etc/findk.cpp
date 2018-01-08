#if defined(LOCAL)
#define PROBLEM_NAME "findk"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
#define C(x...) CHECK(x)
#else
#define L(x, ...) (x)
#define C(x, ...) ;
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
#define MAX(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__y:__x;})
#define MIN(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__x:__y;})

int find_k(auto a, auto b, int k) {
  auto pivot = L(*(a + (b - a) / 2), "pivot");
  auto lower = partition(a, b, [pivot](auto const& x) {
      return x < pivot; });
  auto upper = partition(lower, b, [pivot](auto const& x) {
      return pivot == x; });
  L("partitioned", vector<int>(a, b));
  if (L(lower - a) > k)
    return find_k(a, lower, L(k, "left"));
  if (L(upper - a) <= k)
    return find_k(upper, b, L(k - (upper - a), "right"));
  return pivot;
}
/*
int find_k(auto a, auto b, int k) {
  auto pivot = *(a + (b - a) / 2);
  auto lower = partition(a, b, [pivot](auto const& x) {
      return x < pivot; });
  auto upper = partition(lower, b, [pivot](auto const& x) {
      return !(pivot < x); });
  if (L(lower - a) > k) return find_k(a, lower, k);
  if (L(upper - a) <= k) return find_k(upper, b, k - (upper - a));
  return pivot;
}


int find_k(auto a, auto b, int k) {
  auto pivot = *(a + (b - a) / 2);
  cerr << "pivot " << pivot << endl;
  auto lower = partition(a, b, [pivot](auto const& x) {
      return x < pivot; });
  auto upper = partition(lower, b, [pivot](auto const& x) {
      return !(pivot < x); });
  cerr << "partitioned: ";
  auto i = a;
  while (i != b) cerr << *(i++) << ", ";
  cerr << endl;
  cerr << "size < : " << (lower - a) << endl;
  if ((lower - a) > k) {
    cerr << "< pivot" << endl;
    return find_k(a, lower, k);
  }
  cerr << "size <= : " << (upper - a) << endl;
  if ((upper - a) <= k) {
    auto new_k = k - (upper - a);
    cerr << "> pivot, new_k =" << new_k << endl;
    return find_k(upper, b, new_k);
  }
  return pivot;
}
*/
default_random_engine source(chrono::system_clock::now().time_since_epoch().count());

// [a, b)
l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b - 1)(source);
}

double random_double() {
  return uniform_real_distribution<double>(0, 1)(source);
}

bool random_bool() {
  return random_in_range(0, 2) == 1;
}

string random_string(int length) {
  string s = "";
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size())];
  }
  return s;
}

// return false to stop
bool generate_random(l tc, ostream& cout) {
  l max_cases = 10000;
  if (tc % (max_cases / 100) == 0) cerr << (tc * 100 / max_cases) << "%\r";
  l n = tc / 10 + 1;
  vl v(n);
  cout << n << ' ' << random_in_range(0, n) + 1 << endl;
  F(i, 0, n) cout << random_in_range(0, n) << ' ';
  return tc < max_cases;
}

void solve_brute(istream& cin, ostream& cout) {
  int n, k;
  cin >> n >> k;
  vector<int> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  sort(all(v));
  cout << v[k - 1] << endl;
}

void solve(istream& cin, ostream& cout) {
  int n, k;
  cin >> n >> k;
  vector<int> v(n);
  while (n--) cin >> v[n];
  cout << find_k(v.begin(), v.end(), k - 1) << endl;
}

int main() {
  int a, b;
  cin >> a >> b;
  if (L(a + b, a, b) == 42) {
    cout << "well done!" << endl;
  }
}
/*
int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  _generate_random_test = generate_random;
  _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
*/
