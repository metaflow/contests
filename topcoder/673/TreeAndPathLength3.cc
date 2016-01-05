#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

class TreeAndPathLength3 {
public:
  l a, b, c, d;
  vl primes;
  // s = a * b + c * d + a + b + c + 2, nodes = a + b + c + d + 5
  bool split(l s) {
    // l a, b, c, d;
    for (a = 0; a < 250; a++)
    for (b = a; b < 250; b++) {
      l k = s - a * b - a - b - 1;
      if (k <= 0) continue;
      if (k == 1) {
        c = 0;
        d = 0;
        return true;
      }
      for (c = 1; c * c <= k; c++) {
        if (k % c == 0) {
          d = k / c - 1;
          if (a + b + c - 1 + d + 5 <= 500) {
            c -= 1;
            return true;
          }
        }
      }
    }
    return false;
  }
  vector <int> construct(int s) {
    vector<ll> edges;
    edges.emplace_back(0, 1);
    edges.emplace_back(1, 2);
    edges.emplace_back(2, 3);
    if (s != 1) {
      edges.emplace_back(3, 4);
      split(s);
      l k = 5;
      for (l i = 0; i < a; i++) edges.emplace_back(k++, 0);
      for (l i = 0; i < b; i++) edges.emplace_back(k++, 1);
      for (l i = 0; i < c; i++) edges.emplace_back(k++, 3);
      for (l i = 0; i < d; i++) edges.emplace_back(k++, 4);
    }
    vector<int> result(edges.size() * 2);
    for (l i = 0; i < edges.size(); i++) {
      result[i] = edges[i].first;
      result[2 * i + 1] = edges[i].second;
    }
    return result;
  }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 1; int Arr1[] = {0, 1, 1, 2, 2, 3 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, construct(Arg0)); }
	void test_case_1() { int Arg0 = 2; int Arr1[] = {0, 1, 1, 2, 2, 3, 3, 4 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, construct(Arg0)); }
	void test_case_2() { int Arg0 = 6; int Arr1[] = {0, 1, 1, 2, 0, 3, 3, 4, 0, 5, 5, 6 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, construct(Arg0)); }
	void test_case_3() { int Arg0 = 8; int Arr1[] = {0, 1, 1, 2, 1, 3, 3, 4, 3, 5, 5, 6, 5, 7 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, construct(Arg0)); }

// END CUT HERE
;
};

// BEGIN CUT HERE
int main() {
  TreeAndPathLength3 ___test;
  ___test.run_test(-1);
  // for (l s = 1; s < 10001; s++) ___test.construct(s);
}
// END CUT HERE
