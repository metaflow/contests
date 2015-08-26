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
using vvll = vector<vll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

class WalkOverATree {
  ll dp[51][51][101][2]; // (visited count, left)
  vvll adj;
    public:
    ll walk(ll node, ll child, ll left, int back) {
      auto& r = dp[node][child][left][back];
      if (r != -1) return r;
      r = 0;
      if (left == 0) return r;
      if (child >= adj[node].size()) return r;
      if (back == 1) {
        r = walk(node, child + 1, left, 1);
        for (int i = 2; i <= left; i++) {
          auto t = walk(adj[node][child], 0, i - 2, 1);
          auto w = walk(node, child + 1, left - i, 1);
          w += t + 1;
          r = max(r, w);
        }
        return r;
      }
      r = walk(node, child + 1, left, 0);
      for (int i = 1; i <= left; i++) {
        auto t = walk(adj[node][child], 0, i - 1, 0);
        t++;
        r = max(r, t);
        if (i > 1) {
          t = walk(adj[node][child], 0, i - 2, 1);
          auto w = walk(node, child + 1, left - i, 0);
          w += t + 1;
          r = max(r, w);

          t = walk(node, child + 1, left - i, 1);
          w = walk(adj[node][child], 0, i - 1, 0);
          w += t + 1;
          r = max(r, w);
        }
      }
      return r;
    }
    int maxNodesVisited(vector <int> parent, int L) {
      fill(&dp[0][0][0][0], &dp[51][0][0][0], -1);
      ll n = parent.size() + 1;
      adj.clear();
      adj.resize(n, vll(0));
      for (ll i = 0; i < n - 1; i++) {
        adj[parent[i]].emplace_back(i + 1);
      }
      return walk(0, 0, L, 0) + 1;
      // return 0;
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 2; verify_case(0, Arg2, maxNodesVisited(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 3; verify_case(1, Arg2, maxNodesVisited(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {0, 1, 2, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 3; verify_case(2, Arg2, maxNodesVisited(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {0,0,0,0,2,4,2,3,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 2; verify_case(3, Arg2, maxNodesVisited(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {0,0,1,2,3,2,3,1,3,0,1,8,6,8,0,5,15,0,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arg2 = 5; verify_case(4, Arg2, maxNodesVisited(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {0,0,0,1,1,3,5,1,4,5,2,2,10,5,10,10,11,13,8,3,18,15,20,20,23,8,11,26,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 26; int Arg2 = 17; verify_case(5, Arg2, maxNodesVisited(Arg0, Arg1)); }
	void test_case_6() { int Arr0[] = {0, 0, 2, 0}
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 100; int Arg2 = 5; verify_case(6, Arg2, maxNodesVisited(Arg0, Arg1)); }
	void test_case_7() { int Arr0[] = {0, 0, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arg2 = 4; verify_case(7, Arg2, maxNodesVisited(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
    WalkOverATree ___test;
    ___test.run_test(-1);
}
// END CUT HERE

