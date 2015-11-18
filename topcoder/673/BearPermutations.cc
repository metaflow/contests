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

const l MAX = 101;
l C[MAX][MAX]; // (k from n)
l D[MAX][MAX][MAX];
l mod;

l add(l a, l b) { return (a + b) % mod; }
l get(l pos, l n, l s) {
  if (n == 0) { cerr << "!"; return 0; }
  if (n == 1) return 1;
  assert(pos >= 0 && pos < MAX);
  assert(s >= 0 && s < MAX);
  assert(n >= 0 && n < MAX);
  assert(pos < n);
  l& r = D[pos][n][s];
  if (r != -1) return r;
  r = 0;
  // one child
  if (pos == 0 || pos == n - 1) {
    for (l a = 0; a < n - 1; a++) {
      r = add(r, get(a, n - 1, s));
    }
  } else { // two childs
    // 0..a..pos..b..n-1
    for (l a = 0; a < pos; a++) {
      for (l b = pos + 1; b < n; b++) {
        l rest = s - (b - a);
        // if (rest < 0) continue;
        for (l sa = 0; sa <= rest; sa++) {
          r = add(r,
                  (get(a, pos, sa) *
                  get(b - pos - 1, n - pos - 1, rest - sa)) % mod);
        }
      }
    }
    // cerr << pos << " " << n << " " << C[pos][n] << endl;
    // cerr << r << endl;
    r = (r * C[pos][n]) % mod;
  }
  return r;
}

class BearPermutations {
    public:

    int countPermutations(int N, int S, int MOD) {
      mod = MOD;
      fill(&C[0][0], &C[MAX][0], 0);
      for (l i = 0; i < MAX; i++) { C[i][i] = 1; C[0][i] = 1; }
      for (l i = 1; i < MAX; i++) {
        for (l j = i + 1; j < MAX; j++) {
          C[i][j] = add(C[i - 1][j - 1], C[i][ - 1]);
        }
      }
      fill(&D[0][0][0], &D[MAX][0][0], -1);
      l answer = 0;
      for (l i = 0; i < N; i++) {
        answer = add(answer, get(i, N, S));
      }
      return answer;
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

};

// BEGIN CUT HERE
int main() {
    for (int i = 0; i < 6; i++) {
      BearPermutations ___test; ___test.run_test(i);
    }
}
// END CUT HERE
