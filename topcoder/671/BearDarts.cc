#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using lu = unsigned long long; using ll = pair<l, l>;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

class BearDarts {
    public:
    long long count(vector <int> w) {
      l n = w.size();
      unordered_map<l, set<ll>> M;
      for (l i = 0; i < n; i++) {
        for (l j = i + 2; j < n; j++) {
          l s = w[i];
          s *= w[j];
          M[s].insert(make_pair(min(w[i], w[j]), max(w[i], w[j])));
        }
      }
      unordered_map<l, l> RI;
      for (l a : w) {
        if (RI.count(a)) continue;
        RI[a] = RI.size() - 1;
      }
      vvl A(RI.size(), vl(n + 1));
      for (l i = 0; i < n; i++) A[RI[w[i]]][i + 1]++;
      for (l i = 0; i < A.size(); i++) {
        for (l j = 1; j < n; j++) {
          A[i][j] += A[i][j - 1];
        }
      }
      l answer = 0;
      for (l i = 0; i < n; i++) {
        for (l j = i + 2; j < n; j++) {
          l s = w[i];
          s *= w[j];
          for (auto k : M[s]) {
            l x = RI[k.first], y = RI[k.second];
            answer += (A[x][i] * (A[y][j] - A[y][i + 1]));
            if (x != y) {
              answer += (A[y][i] * (A[x][j] - A[x][i + 1]));
            }
          }
        }
      }
      return answer;
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {6,8,4,3,6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 2LL; verify_case(0, Arg1, count(Arg0)); }
	void test_case_1() { int Arr0[] = {3,4,12,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 0LL; verify_case(1, Arg1, count(Arg0)); }
	void test_case_2() { int Arr0[] = {42,1000000,1000000,42,1000000,1000000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 3LL; verify_case(2, Arg1, count(Arg0)); }
	void test_case_3() { int Arr0[] = {1,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 5LL; verify_case(3, Arg1, count(Arg0)); }
	void test_case_4() { int Arr0[] = {1,2,3,4,5,6,5,4,3,2,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 22LL; verify_case(4, Arg1, count(Arg0)); }
	void test_case_5() { int Arr0[] = {33554432, 33554432, 67108864, 134217728}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 0LL; verify_case(5, Arg1, count(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
    BearDarts ___test;
    ___test.run_test(-1);
}
// END CUT HERE
