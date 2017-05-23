#include <bits/stdc++.h>
#if defined(LOCAL)
#include "prettyprint.h"
#endif

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
const bool enable_log = true;
#else
const bool enable_log = false;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

struct node;
using pnode = shared_ptr<node>;
using graph = vector<pnode>;

struct node {
  l id;
  vector<pnode> adjusted;
  l to0, to1;
  bool visited;
};

class DistanceZeroAndOne {
public:
  vector <string> construct(vector <int> dist0, vector <int> dist1) {
    l n = dist0.size();
    vb assigned(n);
    vector<string> answer;
    if (dist0[0] or dist1[1]) return answer;
    if (dist1[0] != dist0[1]) return answer;
    vector<pnode> g(n);
    F(i, 0, n) {
      g[i] = make_shared<node>();
      g[i]->id = i;
      g[i]->to0 = dist0[i];
      g[i]->to1 = dist1[i];
    }
    for (auto u : g) for (auto v : g) {
      if (u == v) continue;
      if (abs(u->to0 - v->to0) > 1 or abs(u->to1 - v->to1) > 1) continue;
      if ((u->to0 > 0 and v->to0 == u->to0 - 1) or
          (u->to1 > 0 and v->to1 == u->to1 - 1)) {
        u->adjusted.emplace_back(v);
        v->adjusted.emplace_back(u);
      }
    }
    vvl dd(n, vl(n, INF));
    for (auto u : g) {
      for (auto v : u->adjusted) dd[u->id][v->id] = 1;
      dd[u->id][u->id] = 0;
    }
    F(k, 0, n) F(i, 0, n) F(j, 0, n) dd[i][j] = min(dd[i][j], dd[i][k] + dd[k][j]);
    F(i, 0, n) if (dist0[i] != dd[0][i]) return answer;
    F(i, 0, n) if (dist1[i] != dd[1][i]) return answer;
    answer.resize(n);
    for (auto& s : answer) s.resize(n, 'N');
    for (auto& u : g) {
      for (auto& v : u->adjusted) {
        answer[u->id][v->id] = 'Y';
      }
    }
    return answer;
  }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = {0,2,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"NNY", "NNY", "YYN" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, construct(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {0,2,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,0,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = { }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, construct(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {3,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,0,1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = { }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, construct(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {0,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,0,1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"NYYY", "YNYY", "YYNN", "YYNN" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, construct(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {0,3,1,2,2,3,4,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3,0,2,1,2,3,4,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"NNYNNNNN", "NNNYNNNN", "YNNYYNNN", "NYYNYNNN", "NNYYNYNN", "NNNNYNYY", "NNNNNYNN", "NNNNNYNN" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, construct(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {0,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"NY", "YN" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(5, Arg2, construct(Arg0, Arg1)); }

// END CUT HERE
;
};

// BEGIN CUT HERE
int main() {
  DistanceZeroAndOne ___test;
  ___test.run_test(-1);
}
// END CUT HERE
