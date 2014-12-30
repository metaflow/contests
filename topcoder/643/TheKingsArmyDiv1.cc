#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max() / 2;
const int MAX = 210;

class TheKingsArmyDiv1 {
  int sum[2][MAX];
  int memo[MAX][MAX];
  int b[2][MAX];
  vector<int> bars;

  int s(int from, int to, int row) {
    return sum[row][to] - sum[row][from];
  }

  int s(int from, int to) {
    return s(from, to, 0) + s(from, to, 1);
  }

  int f(int from, int to) {
    int &r = memo[from][to];
    if (r == INF) {
      // check for obvious cases
      if (s(from, to) == 0) return r = -1;
      if (s(from, to) == 2 * (to - from)) return r = 0;
      // case when we just flip bars
      int c = 0;
      for (int i = from; i < to; i++) {
        if (b[0][i] == 1 && b[1][i] == 1) c++;
      }
      if (c != 0) r = (to - from - c);
      // or select one of sides fill and flip
      int a = max(s(from, to, 0), s(from, to, 0));
      r = min(r, 1 + (to - from - a));
      // or split interval
      for (int i = from + 1; i < to; i++) {
        int k = f(from, i);
        int m = f(i, to);
        if (k == -1 || m == -1) continue;
        r = min(r, m + k);
      }
    }
    return r;
  }

  public:
    int getNumber(vector <string> state) {
      fill(&sum[0][0], &sum[MAX][0], 0);
      fill(&memo[0][0], &memo[MAX][0], INF);
      int n = state[0].size();
      for (int row = 0; row < 2; row++) {
        for (int col = 0; col < n; col++) {
          b[row][col] = state[row][col] == 'H' ? 1 : 0;
          sum[row][col + 1] = sum[row][col] + b[row][col];
        }
      }
      for (int i = 0; i < n; i++) {
        if (b[0][i] == 1 && b[1][i] == 1) bars.emplace_back(i);
      }
      if (f(0, n) == INF) return -1;
      return f(0, n);
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"HSH",
 "SHS"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, getNumber(Arg0)); }
	void test_case_1() { string Arr0[] = {"HH",
 "HH"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, getNumber(Arg0)); }
	void test_case_2() { string Arr0[] = {"HHHHH",
 "HSHSH"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, getNumber(Arg0)); }
	void test_case_3() { string Arr0[] = {"S",
 "S"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(3, Arg1, getNumber(Arg0)); }
	void test_case_4() { string Arr0[] = {"HSHHSHSHSHHHSHSHSH",
 "SSSSHSSHSHSHHSSSSH"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(4, Arg1, getNumber(Arg0)); }
	void test_case_5() { string Arr0[] = {"HS",
 "HS"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(5, Arg1, getNumber(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
    TheKingsArmyDiv1 ___test;
    ___test.run_test(-1);
}
// END CUT HERE
