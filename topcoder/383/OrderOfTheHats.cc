#if defined(LOCAL)
#define PROBLEM_NAME "OrderOfTheHats"
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

#if defined(LOCAL)
#define L(x...) debug(x)
#else
#define L(x, ...) (x)
#endif

class OrderOfTheHats {
public:

  vl v;
  l N;
  int minChanged(vector <string> spellChart) {
    N = spellChart.size();
    v.clear();
    v.resize(N);
    F(i, 0, N) F(j, 0, N) if (spellChart[i][j] == 'Y') v[j] |= l(1) << i;
    vl dp(1 << N, INF);
    dp[0] = 0;
    F(i, 0, 1 << N) {
      F(j, 0, N) {
        if (i & (1 << j)) continue;
        l next = i | (1 << j);
        dp[next] = min(dp[next], dp[i] + __builtin_popcount(v[j] & next));
      }
    }
    return dp[(1 << N) - 1];
  }
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"Y"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, minChanged(Arg0)); }
	void test_case_1() { string Arr0[] = {"NYN",
 "NNY",
 "NNN"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, minChanged(Arg0)); }
	void test_case_2() { string Arr0[] = {"NYN",
 "NNY",
 "YNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, minChanged(Arg0)); }
	void test_case_3() { string Arr0[] = {"NYYYYYY",
 "YNYYYYY",
 "YYNYYYY",
 "YYYNYYY",
 "YYYYNYY",
 "YYYYYNY",
 "YYYYYYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 21; verify_case(3, Arg1, minChanged(Arg0)); }
	void test_case_4() { string Arr0[] = {"NNNY",
 "YNYN",
 "YNNN",
 "YYYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(4, Arg1, minChanged(Arg0)); }
	void test_case_5() { string Arr0[] = {"YYYYYNNYYYNYNNNNYNNY",
 "NYNNNYYNNYNYYYNYYYYY",
 "NNYNNNYYNNNNNNYYYYNY",
 "YYNYNYYNNYYYNYNNNYYY",
 "NYYNNYNYNYNNNNYYYNYN",
 "NNNNNYYNYNNYYYYNYYYN",
 "YNYNYYNNNYNNNNNYNNYY",
 "NYYYYNYNYNNYNNYNNNNY",
 "YYYYNYYNNYYYNNYNNYNY",
 "YYYYYYNYNYNYNNNNNNYN",
 "NNYYYYYNNNYNNNYNNNNY",
 "YYNNNYNYYNYYNYYNYNYN",
 "NNYNYYNYYNYYNYNYNYYN",
 "YNYNYYNYNNNYNYNYYNYY",
 "NNYNNNYYYYYYYYYYYNYY",
 "YYYYYNYYNYYYYYNNYNNN",
 "NYYYYYYYYNNNNNYYNNYN",
 "YNNYNNNYYNYYYNYNYYYY",
 "YYNNYNYYYNYYNNNYYNNY",
 "NNYNYNYYYNYYNYNNYNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 79; verify_case(5, Arg1, minChanged(Arg0)); }
	void test_case_6() { string Arr0[] = {"YYNYNN",
 "YNYNNY",
 "YYYYNN",
 "NNNYNN",
 "NNNYNN",
 "YNYNYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(6, Arg1, minChanged(Arg0)); }
	void test_case_7() { string Arr0[] = {"NNNNNNNNNN",
 "NNNNNNNNNN",
 "NNNYNNYNNN",
 "NNNYNNYNNN",
 "NNNYNNYNNN",
 "NNNNNNNNNN",
 "NNYYYYYYNN",
 "NNYNNNNYNN",
 "NNNYYYYNNN",
 "NNNNNNNNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(7, Arg1, minChanged(Arg0)); }

// END CUT HERE
;
};

// BEGIN CUT HERE
void solve(istream&, ostream&) {}
int main() {
  OrderOfTheHats ___test;
  ___test.run_test(-1);
}
// END CUT HERE
