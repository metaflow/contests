#if defined(LOCAL)
#define PROBLEM_NAME "#PROBLEM_NAME"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
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
#define max(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x>__y?__x:__y;})
#define min(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__x:__y;})

class GraphAndPairs {
public:
  vector <int> construct(int d, int k) {
    l nodes = 0;
    vll edges;
    if (d == 2) {
      while (k) {
        l a = 1;
        while (a * (a + 1) / 2 <= k) a++;
        l r = nodes;
        F(i, 0, a) edges.emplace_back(r, nodes + i + 1);
        nodes += a + 1;
        assert(a > 1);
        k -= a * (a - 1) / 2;
      }
  } else {
    while (k) {
      l a = 1;
      while ((a + 1) * (a + 1) <= k) a++;
      // construct middle
      l left = nodes, right = nodes + d - 2;
      F(i, left, right) edges.emplace_back(i, i + 1);
      nodes += d - 1;
      F(i, 0, a) edges.emplace_back(left, nodes + i);
      nodes += a;
      F(i, 0, a) edges.emplace_back(right, nodes + i);
      nodes += a;
      k -= a * a;
    }
  }
  vector<int> result;
  result.emplace_back(nodes);
  for (auto e : edges) {
    result.emplace_back(e.first);
    result.emplace_back(e.second);
  }
  return result;
}

// BEGIN CUT HERE
public:
void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
void test_case_0() { int Arg0 = 2; int Arg1 = 1; int Arr2[] = {4, 0, 1, 1, 3, 3, 2, 2, 0, 1, 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, construct(Arg0, Arg1)); }
void test_case_1() { int Arg0 = 2; int Arg1 = 2; int Arr2[] = {8, 0, 1, 1, 3, 3, 2, 2, 0, 1, 2, 4, 5, 5, 7, 7, 6, 6, 4, 5, 6 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, construct(Arg0, Arg1)); }
void test_case_2() { int Arg0 = 4; int Arg1 = 4; int Arr2[] = {8, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 0 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, construct(Arg0, Arg1)); }
void test_case_3() { int Arg0 = 5; int Arg1 = 2; int Arr2[] = {10, 0, 1, 1, 2, 2, 3, 3, 4, 5, 6, 6, 7, 7, 8, 8, 9, 0, 5, 1, 6, 2, 7, 3, 8, 4, 9 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, construct(Arg0, Arg1)); }

// END CUT HERE
;
};

// BEGIN CUT HERE
void solve(istream&, ostream&) {}
int main() {
  GraphAndPairs ___test;
  ___test.run_test(-1);
}
// END CUT HERE
