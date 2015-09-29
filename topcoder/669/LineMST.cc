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

const l MOD = 1000000007;

// return gcd(a, b) and set x, y: a * x + b * y = gcd(a, b)
l extended_euclid(l a, l b, l& x, l& y) {
  if (b == 0) { x = 1; y = 0; return a; }
  l d = extended_euclid(b, a % b, x, y);
  l t = y;
  y = x - (a / b) * y;
  x = t;
  return d;
}

// return b: a * b = 1 (mod n)
l inverse_mod(l a, l n) {
  l x, y;
  l d = extended_euclid(a, n, x, y);
  if (d != 1) return 0;
  return (x + (abs(x) / n + 1) * n) % n;
}

class LineMST {
public:
  int count(int N, int L) {
    l g = 1; // for N = 1
    //[k][n] ways to get line MST with max edge exactly k of length n
    vvl c(L + 1, vl(N + 1));
    vvl p(L + 1, vl(N + 1)); // [i, j] mod power of i ^ j
    for (l i = 1; i <= L; i++) {
      p[i][0] = 1;
      for (l j = 1; j <= N; j++) {
        p[i][j] = (p[i][j - 1] * i) % MOD;
      }
    }
    for (l i = 1; i <= L; i++) c[i][1] = 1;
    for (l i = 1; i < N; i++) c[1][i] = 1;
    for (l k = 2; k <= L; k++) {
      for (l j = 2; j < N; j++) {
        l &t = c[k][j] = 0;
        // ends with edge (< k)
        for (int e = 1; e < k; e++) t += p[k - e + 1][j];
        t %= MOD;
        t = (t * c[k][j - 1]) % MOD;
        // ends with edge (k)
        for (int i = 1; i <= k; i++) t += c[i][j - 1];
        t %= MOD;
      }
    }
    l r = 0;
    for (l i = 1; i <= L; i++) r += c[i][N - 1];
    r %= MOD;
    for (l i = 2; i <= N; i++) r = (r * i) % MOD; // n! ways to mark vertices
    r = (r * inverse_mod(2, MOD)) % MOD;
    return r;
  }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 15; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 10; int Arg2 = 10; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 3; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 8; int Arg1 = 41; int Arg2 = 655468587; verify_case(3, Arg2, count(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 200; int Arg1 = 200; int Arg2 = 152699064; verify_case(4, Arg2, count(Arg0, Arg1)); }

// END CUT HERE
;
};

// BEGIN CUT HERE
int main() {
  LineMST ___test;
  ___test.run_test(-1);
}
// END CUT HERE
