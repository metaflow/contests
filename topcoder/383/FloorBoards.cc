#if defined(LOCAL)
#define PROBLEM_NAME "FloorBoards"
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

class FloorBoards {
public:

  l N, M;
  vector<vector<vector<vector<l>>>> memo;
  vvb v;
  l dfs(l row, l col, l started, l mask) {
    if (col == M) return dfs(row + 1, 0, 0, mask);
    if (row == N) return 0;
    l& r = memo[row][col][started][mask];
    if (r == -1) {
      r = INF;
      l nocol = mask & (((1 << M) - 1) ^ (1 << col));
      if (v[row][col]) {
        if (started) {
          r = min(r, dfs(row, col + 1, started, nocol));
        } else {
          r = min(r, 1 + dfs(row, col + 1, 1, nocol));
        }
        if (mask & (1 << col)) {
          r = min(r, dfs(row, col + 1, 0, mask));
        } else {
          r = min(r, 1 + dfs(row, col + 1, 0, mask | (1 << col)));
        }
      } else {
        r = dfs(row, col + 1, 0, nocol);
      }
    }
    return r;
  }

  int layout(vector <string> room) {
    N = room.size();
    M = room[0].size();
    v.clear();
    v.resize(N, vb(M));
    memo.clear();
    memo.resize(N, vector<vvl>(M, vvl(2, vl(1 << M, -1))));
    F(i, 0, N) F(j, 0, M) v[i][j] = (room[i][j] == '.');
    L(room);
    L(v);
    return dfs(0, 0, 0, 0);
  }
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"....."
,"....."
,"....."
,"....."
,"....."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(0, Arg1, layout(Arg0)); }
	void test_case_1() { string Arr0[] = {"......."
,".#..##."
,".#....."
,".#####."
,".##..#."
,"....###"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(1, Arg1, layout(Arg0)); }
	void test_case_2() { string Arr0[] = {"####"
,"####"
,"####"
,"####"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, layout(Arg0)); }
	void test_case_3() { string Arr0[] = {"...#.."
,"##...."
,"#.#..."
,".#...."
,"..#..."
,"..#..#"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(3, Arg1, layout(Arg0)); }
	void test_case_4() { string Arr0[] = {".#...."
,"..#..."
,".....#"
,"..##.."
,"......"
,".#..#."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(4, Arg1, layout(Arg0)); }

// END CUT HERE
;
};

// BEGIN CUT HERE
void solve(istream&, ostream&) {}
int main() {
  FloorBoards ___test;
  ___test.run_test(-1);
}
// END CUT HERE
