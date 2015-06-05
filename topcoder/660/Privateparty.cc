#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 51;
double DP[MAX][MAX][MAX][MAX];
class Privateparty {
  public:

  int cycle[MAX];

  double p(int x, int k, int n, int c, vi &a) {
    double &_ = DP[x][k][n][c];
    if (_ < 0) {
      _ = 1;
      if (cycle[x] > c && n > 1) {
        for (int i = 0; i < k; i++) {
          _ -= p(a[x], i, n - 1, c + 1, a);
        }
      }
      _ /= n;
    }
    return _;
  }

  double f(int x, vi& a, int n) {
    double _ = 0;
    for (int i = 0; i < n; i++) {
      _ += p(x, i, n, 0, a);
    }
    return _;
  }

  double getexp(vector <int> a) {
    double r = 0;
    int n = a.size();
    fill(&DP[0][0][0][0], &DP[MAX][0][0][0], -1);
    for (int i = 0; i < n; i++) {
      int at = a[i];
      for (cycle[i] = 0; cycle[i] < MAX && at != i; cycle[i]++) {
        at = a[at];
      }
    }
    for (int i = 0; i < n; i++) {
      r += f(i, a, n);
    }
    return r;
  }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 2.0; verify_case(0, Arg1, getexp(Arg0)); }
	void test_case_1() { int Arr0[] = {0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1.5; verify_case(1, Arg1, getexp(Arg0)); }
	void test_case_2() { int Arr0[] = {0,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 2.5; verify_case(2, Arg1, getexp(Arg0)); }
	void test_case_3() { int Arr0[] = {0,1,1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 3.166666666666667; verify_case(3, Arg1, getexp(Arg0)); }
	void test_case_4() { int Arr0[] = {3,2,1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 2.0; verify_case(4, Arg1, getexp(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
    Privateparty ___test;
    ___test.run_test(-1);
    // cerr << ___test.getexp({1, 0}) << endl;
    // cerr << ___test.getexp({1, 2, 0}) << endl;
    // cerr << ___test.getexp({1, 2, 3, 0}) << endl;
}
// END CUT HERE
