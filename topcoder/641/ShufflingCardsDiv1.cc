#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max() / 2;
const int MAX = 2000;

class ShufflingCardsDiv1 {
private:
  int n, odds;
  bitset<MAX> visited;
  int memo[MAX];

  void dfs(int a) {
    int &best = memo[a];
    visited.set(a);
    int low = max(a - (n - odds), 0) + max(n - a - odds, 0);
    int up = min(a, odds) + min(n - a, n - odds);
    for (int i = low; i <= up; i++) {
      if (!visited[i]) dfs(i);
      if (memo[i])
      best = min(best, memo[i] + 1);
    }
  }
public:
  int shuffle(vector <int> permutation) {

    n = permutation.size() / 2;
    odds = n / 2 + n % 2;

    bool sorted = true;
    for (int i = 1; i < permutation.size(); i++) {
      if (permutation[i] < permutation[i - 1]) sorted = false;
    }
    if (sorted) return 0;
    int a = 0;
    fill(&memo[0], &memo[MAX], INF);
    memo[0] = 1;
    visited.reset();
    for (int i = 0; i < n; i++) {
      if (permutation[i * 2] > n) a++;
    }
    dfs(a);
    return memo[a];
  }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,2,3,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(0, Arg1, shuffle(Arg0)); }
	void test_case_1() { int Arr0[] = {1,4,3,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, shuffle(Arg0)); }
	void test_case_2() { int Arr0[] = {6,3,5,2,4,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(2, Arg1, shuffle(Arg0)); }
	void test_case_3() { int Arr0[] = {8,5,4,9,1,7,6,10,3,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(3, Arg1, shuffle(Arg0)); }
	void test_case_4() { int Arr0[] = {9,1,7,2,10,3,6,4,8,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(4, Arg1, shuffle(Arg0)); }

// END CUT HERE
;
};

// BEGIN CUT HERE
int main() {
  ShufflingCardsDiv1 ___test;
  ___test.run_test(-1);
}
// END CUT HERE
