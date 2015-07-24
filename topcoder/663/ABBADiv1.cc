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
const int MAX = 51;

class ABBADiv1 {
public:
  string l, r;
  int DP[MAX][MAX][2];
  int dp(ll l_index, ll r_index, int reverse) {
    auto &_ = DP[l_index][r_index][reverse];
    if (_ == -1) {
      _ = 0;
      if (l_index > 0 && reverse == 0 && l[l_index - 1] == 'B') {
        _ = max(_, dp(l_index - 1, r_index, 1 - reverse));
      }
      if (r_index > 0 && reverse == 1 && r[r_index - 1] == 'B') {
        _ = max(_, dp(l_index, r_index - 1, 1 - reverse));
      }
      if (r_index > 0 && reverse == 0 && r[r_index - 1] == 'A') {
        _ = max(_, dp(l_index, r_index - 1, reverse));
      }
      if (l_index > 0 && reverse == 1 && l[l_index - 1] == 'A') {
        _ = max(_, dp(l_index - 1, r_index, reverse));
      }
    }
    return _;
  }
  string canObtain(string initial, string target) {
    // cerr << initial << " -> " << target << endl;
    int odd = 0;
    for (auto c : initial) if (c == 'B') odd--;
    for (auto c : target) if (c == 'B') odd++;
    bool ok = false;
    if (odd >= 0) {
      if (odd % 2 == 1) {
        reverse(initial.begin(), initial.end());
      }
      size_t i = 0;
      while (!ok) {
        i = target.find(initial, i);
        if (i == string::npos) break;
        l = target.substr(0, i);
        reverse(l.begin(), l.end());
        r = target.substr(i + initial.size());
        fill(&DP[0][0][0], &DP[MAX][0][0], -1);
        DP[0][0][odd % 2] = 1;
        DP[0][0][1 - odd % 2] = 0;
        ok = dp(l.size(), r.size(), 0) == 1;
        i++;
      }
    }
    if (ok) return "Possible";
    return "Impossible";
  }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "A"; string Arg1 = "BABA"; string Arg2 = "Possible"; verify_case(0, Arg2, canObtain(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "BAAAAABAA"; string Arg1 = "BAABAAAAAB"; string Arg2 = "Possible"; verify_case(1, Arg2, canObtain(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "A"; string Arg1 = "ABBA"; string Arg2 = "Impossible"; verify_case(2, Arg2, canObtain(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "AAABBAABB"; string Arg1 = "BAABAAABAABAABBBAAAAAABBAABBBBBBBABB"; string Arg2 = "Possible"; verify_case(3, Arg2, canObtain(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "AAABAAABB"; string Arg1 = "BAABAAABAABAABBBAAAAAABBAABBBBBBBABB"; string Arg2 = "Impossible"; verify_case(4, Arg2, canObtain(Arg0, Arg1)); }

// END CUT HERE
;
};

// BEGIN CUT HERE
int main() {
  ABBADiv1 ___test;
  ___test.run_test(-1);
}
// END CUT HERE
