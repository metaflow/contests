#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

class SubdividedSlimes {

  // (base^power) % mod, safe for l near max
  l pp(l base, l power) {
    l r = 1;
    while (power) {
      if (power % 2) r = (r * base);
      base = (base * base);
      power /= 2;
    }
    return r;
  }

public:
  int needCut(int S, int M) {
    for (l i = 1; i < S; i++) {
      l p = (S) / (i + 1);
      l r = S - p * i;
      l m = r * p * i + p * p * i * (i - 1) / 2;
      if (m >= M) return i;
      p = (S + i) / (i + 1);
      r = S - p * i;
      m = r * p * i + p * p * i * (i - 1) / 2;
      if (m >= M) return i;
    }
    return -1;
  }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 1; verify_case(0, Arg2, needCut(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 2; verify_case(1, Arg2, needCut(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 9; int Arg2 = 3; verify_case(2, Arg2, needCut(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 765; int Arg1 = 271828; int Arg2 = 14; verify_case(3, Arg2, needCut(Arg0, Arg1)); }

// END CUT HERE
;
};

// BEGIN CUT HERE
int main() {
  SubdividedSlimes ___test;
  ___test.run_test(-1);
}
// END CUT HERE
