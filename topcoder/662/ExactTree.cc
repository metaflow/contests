#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
int dp[51][2000][101];

class ExactTree {
    public:
    int M;
    int f(int n, int k, int r) {
      int &q = dp[n][k][r];
      if (q == -2) {
        // cerr << "n, k, r " << n << " " << k << " " << r << endl;
        q = -1;
        if (n == 1) {
          if (r == 0) q = 0;
          return q;
        }
        for (int a = 1; a < n; a++) {
          int b = n - a;
          for (int ra = 0; ra < M; ra++) {
            // ra + rb + (a | b) * k  + a * b = r | M
            // 1:
            int rb;
            rb = r - a * b - a * k - ra;
            while (rb < 0) rb += M;
            rb %= M;
            int fa = f(a, b + k, ra);
            int fb = f(b, a + k, rb);
            if (fa != -1 && fb != -1) {
              int t = fa + fb + a * k + a * b;
              if (q == -1 || q > t) q = t;
            }

            rb = r - a * b - b * k - ra;
            while (rb < 0) rb += M;
            rb %= M;
            fb = f(b, a + k, rb);
            if (fa != -1 && fb != -1) {
              int t = fa + fb + b * k + a * b;
              if (q == -1 || q > t) q = t;
            }
          }
        }
      }
      return q;
    }

    int getTree(int n, int m, int r) {
      M = m;
      fill(&dp[0][0][0], &dp[51][0][0], -2);
      return f(n, 0, r);
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 4; int Arg1 = 100; int Arg2 = 9; int Arg3 = 9; verify_case(0, Arg3, getTree(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 100; int Arg2 = 10; int Arg3 = 10; verify_case(1, Arg3, getTree(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 100; int Arg2 = 0; int Arg3 = -1; verify_case(2, Arg3, getTree(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 6; int Arg1 = 2; int Arg2 = 0; int Arg3 = 28; verify_case(3, Arg3, getTree(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 6; int Arg1 = 2; int Arg2 = 1; int Arg3 = 25; verify_case(4, Arg3, getTree(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arg0 = 25; int Arg1 = 100; int Arg2 = 0; int Arg3 = 700; verify_case(5, Arg3, getTree(Arg0, Arg1, Arg2)); }
	void test_case_6() { int Arg0 = 50; int Arg1 = 97; int Arg2 = 89; int Arg3 = 2708; verify_case(6, Arg3, getTree(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
    ExactTree ___test;
    ___test.run_test(-1);
}
// END CUT HERE
