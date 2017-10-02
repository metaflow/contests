#if defined(LOCAL)
#define PROBLEM_NAME "#PROBLEM_NAME"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
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
#define max(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x>__y?__x:__y;})
#define min(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__x:__y;})

class RememberWords {
public:
  ll f(l d, l w) {
    l from = max((w - d * (d - 1) / 2 + d - 1) / d, 0);
    l t = (d - 1) * d / 2;
    l to;
    if (t <= w) {
      to = (w - d * (d - 1) / 2) / d + d - 1;
    } else {
      l k = sqrt(2 * w) - 1;
      while (k * (k + 1) / 2 <= w) k++;
      to = max(k - 1, 0);
    }
    return make_pair(from, to);
  }
  string isPossible(int d1, int d2, int w1, int w2) {
    auto p1 = f(d1, w1);
    auto p2 = f(d2, w2);
    // L(p1, p2);
    if (p1.second >= p2.first - 1 and p1.first <= p2.second + 1) return "Possible";
    return "Impossible";
  }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 26662; int Arg1 = 46; int Arg2 = 173072; int Arg3 = 9; string Arg4 = "Possible"; verify_case(0, Arg4, isPossible(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 3; int Arg3 = 5; string Arg4 = "Impossible"; verify_case(1, Arg4, isPossible(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 5; int Arg2 = 300; int Arg3 = 500; string Arg4 = "Possible"; verify_case(2, Arg4, isPossible(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 100; int Arg1 = 1; int Arg2 = 0; int Arg3 = 2; string Arg4 = "Impossible"; verify_case(3, Arg4, isPossible(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 1000000000; int Arg1 = 1000000000; int Arg2 = 1000000000; int Arg3 = 1000000000; string Arg4 = "Possible"; verify_case(4, Arg4, isPossible(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
;
};

// BEGIN CUT HERE
void solve(istream&, ostream&) {}
int main() {
  RememberWords ___test;
  ___test.run_test(-1);
}
// END CUT HERE
