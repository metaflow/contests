#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const ll MOD = 1000000007;
const int MAX = 4001;


ll dp[MAX][3];
ll C[MAX][MAX];
ll M;


class SumOverPermutations {
    public:
    ll brute(ll n) {
      vll p;
      for (ll i = 0; i < n; i++) p.emplace_back(i);
      // next_permutation(p.begin(), p.end());
      ll s = 0;
      while (true) {
        vb b(n);
        ll r = 1;
        for (auto i : p) {
          ll m = 0;
          if (i > 0 && b[i - 1]) m++;
          if (i < n - 1 && b[i + 1]) m++;
          r *= (n - m);
          b[i] = true;
        }
        s += r;
        if (!next_permutation(p.begin(), p.end())) break;
      }
      return s;
    }


    ll f(ll n, ll sides) {
      ll &r = dp[n][sides];
      if (r != -1) return r;
      if (n == 0) return 1;
      r = 0;
      for (ll i = 0; i < n; i++) {
        ll t = M;
        if (i == 0 && sides > 0) t--;
        if (i == n - 1 && sides == 2) t--;
        t = (t * f(i, min(2LL, sides + 1))) % MOD;
        t = (t * f(n - 1 - i, max(1LL, sides))) % MOD;
        t = (t * C[n - 1][i]) % MOD;
        r = (r + t) % MOD;
      }
      return r;
    }

    int findSum(int n) {
      // cerr << 'c' << endl;
      fill(&C[0][0], &C[MAX][0], 0);
      for (ll i = 0; i < MAX; i++) {
        C[i][0] = 1;
        for (ll j = 1; j <= i; j++) {
          C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
        }
      }
      M = n;
      fill(&dp[0][0], &dp[MAX][0], -1);
      // cerr << "dp" << endl;
      return f(n, 0);
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 4; verify_case(0, Arg1, findSum(Arg0)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 66; verify_case(1, Arg1, findSum(Arg0)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 58310114; verify_case(2, Arg1, findSum(Arg0)); }
	void test_case_3() { int Arg0 = 3900; int Arg1 = 940560814; verify_case(3, Arg1, findSum(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
    SumOverPermutations ___test;
    // for (ll i = 1; i <= 7; i++) {
    //   cout << i << " " << ___test.brute(i) << endl;
    // }
    // cout << ___test.findSum(3) << endl;
    ___test.run_test(-1);
}
// END CUT HERE
