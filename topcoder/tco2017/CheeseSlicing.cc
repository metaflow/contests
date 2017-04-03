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

const l MAX = 101;
l DP[MAX][MAX][MAX];
class CheeseSlicing {
public:
  l s;

  l score(vl& v) {
    if (v[0] < s) return 0;
    return v[1] * v[2];
  }

  l f(vl& v) {
    if (v[0] < s) return 0;
    l& r = DP[v[0]][v[1]][v[2]];
    if (r == -1) {
      r = score(v);
      F(j, 0, 3) {
        if (v[j] < s) continue;
        vl t1 = v;
        vl t2 = v;
        t1[j] = s;
        t2[j] = v[j] - s;
        sort(ALL(t1)); sort(ALL(t2));
        r = max(r, score(t1) + f(t2));
      }
    }
    return r;
  }
  int totalArea(int A, int B, int C, int S) {
    s = S;
    fill(&DP[0][0][0], &DP[MAX][0][0], -1);
    vl v = {A, B, C};
    sort(ALL(v));
    return f(v);
  }
  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 3; int Arg2 = 3; int Arg3 = 2; int Arg4 = 0; verify_case(0, Arg4, totalArea(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 5; int Arg1 = 3; int Arg2 = 5; int Arg3 = 3; int Arg4 = 25; verify_case(1, Arg4, totalArea(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 5; int Arg2 = 5; int Arg3 = 2; int Arg4 = 58; verify_case(2, Arg4, totalArea(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 100; int Arg1 = 100; int Arg2 = 100; int Arg3 = 1; int Arg4 = 1000000; verify_case(3, Arg4, totalArea(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
;
};

// BEGIN CUT HERE
int main() {
  CheeseSlicing ___test;
  ___test.run_test(-1);
}
// END CUT HERE
