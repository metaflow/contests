#if defined(LOCAL)
#define PROBLEM_NAME "CHEFCOUN"
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

void solve(istream& cin, ostream& cout) {
  l tcc; cin >> tcc;
  while (tcc--) {
    l n; cin >> n;
    l mod = ((l)1 << 32);
    l a = (mod - 1) / n;
    l x = a;
    while (x * 2 + a * (n - 2) + 1 < mod) x++;
    cout << 1 << ' ' << x;
    F(i, 0, n - 2) cout << ' ' << a;
    cout << lf;
  }
}

int wrongSolver(std::vector <unsigned int> a) {
	int n = a.size();
	std::vector<unsigned int> prefSum(n), sufSum(n);
	prefSum[0] = a[0];
	for (int i = 1; i < n; i++) {
		prefSum[i] = prefSum[i - 1] + a[i];
	}
	sufSum[n - 1] = a[n - 1];
	for (int i = n - 2; i >= 0; i--) {
		sufSum[i] = sufSum[i + 1] + a[i];
	}
	unsigned int mn = prefSum[0] + sufSum[0];
	int where = 1;
	for (int i = 1; i < n; i++) {
		unsigned int val = prefSum[i] + sufSum[i];
		if (val < mn) {
			mn = val;
			where = i + 1;
		}
	}
	return where;
}

bool solution_checker(istream& input, istream& /* expected */,
                      istream& actual, ostream& /* out */) {
  l tcc; input >> tcc;
  while (tcc--) {
    l n; input >> n;
    vector<unsigned int> v(n);
    l answer = 0;
    F(i, 0, n) {
      l a; actual >> a;
      C(a > 0, a);
      C(a < e5, a);
      v[i] = a;
      if (v[i] < v[answer]) answer = i;
    }
    l wrong = wrongSolver(v) - 1;
    L(answer, wrong);
    C(answer != wrong, answer, wrong);
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
 _custom_solution_checker = solution_checker;
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
