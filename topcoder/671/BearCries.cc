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
const l MAX = 201;
const l MOD = 1000000007;
l D[MAX][MAX][MAX];

class BearCries {
    public:
    string s;
    l N;
    //    ';'     ';_+'
    l f(l opened, l mid, l pos) {
      //cerr << opened << " " << mid << ' ' << pos;
      if (pos == N) {
        if (opened == 0) return 1;
        return 0;
      }
      l &r = D[opened][mid][pos];
      if (r != -1) return r;
      r = 0;
      if (s[pos] == ';') {
        // either close one of the ';_'
        if (mid > 0) {
          r = (r + mid * f(opened - 1, mid - 1, pos + 1)) % MOD;
        }
        // or start new
        r = (r + f(opened + 1, mid, pos + 1)) % MOD;
      } else { // '_'
        // start new
        if (opened > mid) {
          r = (r + (opened - mid) * f(opened, mid + 1, pos + 1)) % MOD;
        }
        // or join one of the existing
        if (mid > 0) {
          r = (r + mid * f(opened, mid, pos + 1)) % MOD;
        }
      }
      return r;
    }
    int count(string message) {
      N = message.size();
      s = message;
      fill(&D[0][0][0], &D[MAX][0][0], -1);
      return f(0, 0, 0);
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = ";_;;_____;"; int Arg1 = 2; verify_case(0, Arg1, count(Arg0)); }
	void test_case_1() { string Arg0 = ";;;___;;;"; int Arg1 = 36; verify_case(1, Arg1, count(Arg0)); }
	void test_case_2() { string Arg0 = "_;__;"; int Arg1 = 0; verify_case(2, Arg1, count(Arg0)); }
	void test_case_3() { string Arg0 = ";_____________________________________;"; int Arg1 = 1; verify_case(3, Arg1, count(Arg0)); }
	void test_case_4() { string Arg0 = ";__;____;"; int Arg1 = 0; verify_case(4, Arg1, count(Arg0)); }
	void test_case_5() { string Arg0 = ";_;;__;_;;"; int Arg1 = 52; verify_case(5, Arg1, count(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
    BearCries ___test;
    ___test.run_test(-1);
}
// END CUT HERE
