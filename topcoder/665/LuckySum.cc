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

class LuckySum {
    public:
    bool check(vi& v, string s, int pos) {
      if (s[pos] == '?') return v[pos] > 0;
      return v[pos] == (s[pos] - '0');
    }

    vi f(vi v, string s, int fa, int fb, int pos) {
      if (pos < s.size()) {
        vi va;
        if (pos >= fa) {
          va.emplace_back(4);
          va.emplace_back(7);
        } else {
          va.emplace_back(0);
        }
        vi vb;
        if (pos >= fb) {
          vb.emplace_back(4);
          vb.emplace_back(7);
        } else {
          vb.emplace_back(0);
        }
        for (auto a : va) {
          for (auto b : vb) {
            vi c = v;
            c[pos] += a + b;
            c[pos - 1] += c[pos] / 10;
            c[pos] %= 10;
            if (check(c, s, pos - 1)) {
              c = f(c, s, fa, fb, pos + 1);
              if (c[0] == 0) return c;
            }
          }
        }
      } else {
        if (check(v, s, pos - 1)) return v;
      }
      v[0] = 1;
      return v;
    }

    ll lucky(string s) {
      ll n = s.size();
      vi carry(n, 3);
      carry[0] = 2;
      bool ok = true;
      for (ll i = 0; i < n; i++) {
        bool last = (i == n - 1);
        switch (s[i]) {
          case '?': break;
          case '1': if (last || i != 0) carry[i] &= 1; break;
          case '2': if (last) { ok = false; }
                    else { carry[i + 1] &= 1; carry[i] &= 1; } break;
          case '4': if (last) { carry[i] &= 1; } else { carry[i + 1] &= 2; } break;
          case '5': if (last) { ok = false; } else { carry[i + 1] &= 1; } break;
          case '7': if (last) { ok = false; } else { carry[i + 1] &= 2; carry[i] &= 2; } break;
          case '8': carry[i] &= 2; break;
          case '9': if (last) { ok = false; } else { carry[i + 1] &= 1; carry[i] &= 2; } break;
          default: ok = false; break;
        }
      }
      for (auto i : carry) ok = ok && (i != 0);
      ll best = - 1;
      if (ok) {
        s = "0" + s;
        for (ll i = 1; i <= 2; i++) {
          for (ll j = i; j <= n; j++) {
            vi v(n + 1, 0);
            v = f(v, s, i, j, 1);
            if (v[0] != 1) {
              ll a = 0;
              for (auto k : v) {
                a = a * 10 + k;
              }
              if (a < best || best == -1) best = a;
            }
          }
        }
      }
      return best;
    }

    long long construct(string note) {
      return lucky(note);
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "1FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "?"; long long Arg1 = 8LL; verify_case(0, Arg1, construct(Arg0)); }
	void test_case_1() { string Arg0 = "?1"; long long Arg1 = 11LL; verify_case(1, Arg1, construct(Arg0)); }
	void test_case_2() { string Arg0 = "4?8"; long long Arg1 = 448LL; verify_case(2, Arg1, construct(Arg0)); }
	void test_case_3() { string Arg0 = "2??"; long long Arg1 = -1LL; verify_case(3, Arg1, construct(Arg0)); }
	void test_case_4() { string Arg0 = "??????????????"; long long Arg1 = 11888888888888LL; verify_case(4, Arg1, construct(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
    LuckySum ___test;
    ___test.run_test(-1);
}
// END CUT HERE

