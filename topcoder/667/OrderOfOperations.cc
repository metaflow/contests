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
const ll MAX = (1 << 20) + 1;

ll dp[MAX];

ll count_bits(ll a) {
  ll r = 0;
  while (a) {
    if (a % 2) r++;
    a /= 2;
  }
  return r;
}

class OrderOfOperations {
    public:
    int minTime(vector<string> s) {
      ll target = 0;
      vll v;
      for (auto k : s) {
        ll a = 0;
        for (auto c : k) {
          a *= 2;
          if (c == '1') a++;
        }
        v.emplace_back(a);
        target = target | a;
      }
      fill(&dp[0], &dp[MAX], INF);
      dp[0] = 0;
      for (ll i = 0; i < target; i++) {
        if (dp[i] == INF) continue;
        for (auto a : v) {
          ll t = count_bits(a - (a & i));
          dp[i | a] = min(dp[i | a], dp[i] + t * t);
        }
      }
      return dp[target];
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {
 "111",
 "001",
 "010"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, minTime(Arg0)); }
	void test_case_1() { string Arr0[] = {
 "11101",
 "00111",
 "10101",
 "00000",
 "11000"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(1, Arg1, minTime(Arg0)); }
	void test_case_2() { string Arr0[] = {
  "11111111111111111111"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 400; verify_case(2, Arg1, minTime(Arg0)); }
	void test_case_3() { string Arr0[] = {
  "1000",
  "1100",
  "1110"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(3, Arg1, minTime(Arg0)); }
	void test_case_4() { string Arr0[] = {
  "111",
  "111",
  "110",
  "100"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(4, Arg1, minTime(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE

int minTimeGreedy(vector <string> s) {
  int answer = 0;
  ll n = s.size();
  ll m = s[0].size();
  vb on(m, false);
  vb used(n, false);
  for (ll i = 0; i < n; i++) {
    ll best = INF, best_id = -1;
    for (ll j = 0; j < n; j++) {
      if (used[j]) continue;
      ll t = 0;
      for (ll k = 0; k < m; k++) {
        if (!on[k] && s[j][k] == '1') t++;
      }
      if (t < best) {
        best = t;
        best_id = j;
      }
    }
    answer += best * best;
    for (ll k = 0; k < m; k++) {
      if (s[best_id][k] == '1') on[k] = true;
    }
    used[best_id] = true;
  }
  return answer;
}

string to_binary(int i, int k) {
  string r;
  while (k--) {
    if (i % 2) {
      r += "1";
    } else {
      r += "0";
    }
    i /= 2;
  }
  reverse(r.begin(), r.end());
  return r;
}

int main() {
  OrderOfOperations correct;
  ll t = (1 << 6);
  for (int i = 0; i < t; i++) {
    auto si = to_binary(i, 6);
    for (int j = i + 1; j < t; j++) {
      if (count_bits(i) == count_bits(j)) continue;
      auto sj = to_binary(j, 6);
      for (int k = j + 1; k < t; k++) {
        if (count_bits(i) == count_bits(k)) continue;
        if (count_bits(j) == count_bits(k)) continue;
        auto sk = to_binary(k, 6);
        vector<string> s = {si, sj, sk};
        if (correct.minTime(s) != minTimeGreedy(s)) {
          cout << si << endl;
          cout << sj << endl;
          cout << sk << endl;
          return 0;
        }
      }
    }
  }
}
// END CUT HERE
