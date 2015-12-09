#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

class BearPermutations {
public:
  int countPermutations(int N, int S, int MOD) {

  }
  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 71876209; int Arg3 = 4; verify_case(0, Arg3, countPermutations(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 0; int Arg2 = 1000003; int Arg3 = 8; verify_case(1, Arg3, countPermutations(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 1; int Arg2 = 483128897; int Arg3 = 8; verify_case(2, Arg3, countPermutations(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 5; int Arg1 = 3; int Arg2 = 907283243; int Arg3 = 82; verify_case(3, Arg3, countPermutations(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 5; int Arg1 = 100; int Arg2 = 101; int Arg3 = 19; verify_case(4, Arg3, countPermutations(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arg0 = 20; int Arg1 = 30; int Arg2 = 3; int Arg3 = 2; verify_case(5, Arg3, countPermutations(Arg0, Arg1, Arg2)); }

// END CUT HERE
;
};

// BEGIN CUT HERE
int main() {
  BearPermutations ___test;
  ___test.run_test(-1);
}
// END CUT HERE
