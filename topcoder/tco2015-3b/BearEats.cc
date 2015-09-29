#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using l = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vl = vector<l>;
using ll = pair<l, l>;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l MOD = 1000000007;

class BearEats {
    public:
    vll generate(l N, l R, l C, l D, l A_MAX, l B_MAX) {
      vll g(N);
      for (l i = 0; i < N; i++) {
        R = (C * R + D) % MOD;
        g[i].first = R % A_MAX;
        R = (C * R + D) % MOD;
        g[i].second = R % B_MAX;
      }
      return g;
    }
    long long getDifference(int N, int R, int C, int D, int A_MAX, int B_MAX) {
        vll v = generate(N, R, C, D, A_MAX, B_MAX);
        sort(v.begin(), v.end(), [] (const ll &a, const ll &b) {
          if (a.second == b.second) return a.first > b.first;
          return a.second > b.second;
        });
        priority_queue<l, vl, greater<l>> q;
        l balance = 0;
        for (l i = 0; i < N; i++) {
          l keep = i / 2 + 1;
          l j = v[i].first + v[i].second;
          q.push(j);
          balance += v[i].first;
          while (q.size() > keep) {
            balance -= q.top();
            q.pop();
          }
        }
        return balance;
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 4; int Arg2 = 4; int Arg3 = 1; int Arg4 = 11; int Arg5 = 15; long long Arg6 = -3LL; verify_case(0, Arg6, getDifference(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_1() { int Arg0 = 5; int Arg1 = 2; int Arg2 = 3; int Arg3 = 0; int Arg4 = 14; int Arg5 = 40; long long Arg6 = 4LL; verify_case(1, Arg6, getDifference(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 938593858; int Arg2 = 538591850; int Arg3 = 384025833; int Arg4 = 885912358; int Arg5 = 3405; long long Arg6 = 1452754016LL; verify_case(2, Arg6, getDifference(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_3() { int Arg0 = 200000; int Arg1 = 999998741; int Arg2 = 999997411; int Arg3 = 64592149; int Arg4 = 57; int Arg5 = 75; long long Arg6 = 462494LL; verify_case(3, Arg6, getDifference(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
    BearEats ___test;
    ___test.run_test(-1);
}
// END CUT HERE
