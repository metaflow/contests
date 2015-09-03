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
    long long construct(string note) {
      ll n = note.size();
      // 3 - any, 1 - produces, 2 - not produces, 0 - impossible
      vi carry(n, 3);
      carry[0] = 2;
      bool ok = true;
      switch (note[0]) {
        case '?': break;
        case '1':
          if (n == 1) { ok = false; break; }
          carry[1] &= 1;
          break;
        case '4':
          if (n == 1) { ok = false; break; }
          carry[1] &= 2;
          break;
        case '5':
          if (n == 1) { ok = false; break; }
          carry[1] &= 1;
          break;
        case '7':
          if (n == 1) { ok = false; break; }
          carry[1] &= 2;
          break;
        case '8': break;
        case '9':
          if (n == 1) { ok = false; break; }
          carry[1] &= 1;
          break;
        case default:
          ok = false;
          break;
      }
      for (ll i = 1; i < n; i++) {
        switch (note[i]) {
          case '1':
            carry[i] &= 1;
            if (i + 1 == n) continue;
            carry[i + 1] &= 2;
            break;
          case '2':
            if (i + 1 == n) {ok = false; break; }
            carry[i + 1] &= 1;
            carry[i] &= 1;
            break;
          case '4':
            if (i + 1 == n) continue;
            carry[i + 1] &= 2;
            break;
          case '5':
            if (i + 1 == n) { ok = false; break; }
            carry[i + 1] &= 1;
            break;
          case '7':
            if (i + 1 == n) { ok = false; break; }
            carry[i + 1] &= 2;
            break;
          case '8': break;
          case '9': break;
            if (i + 1 == n) { ok = false; break; }
            carry[i + 1] &= 1;
          case '?': break;
          default:
            ok = false;
            break;
        }
      }
      for (ll i = 0; i < n; i++) if (carry[i] == 0) ok = false;
      vi solution(n, 9);
      for (ll l = 1; l <= n; l++) {
        vi c = carry;
        vi candidate(n);
        bool g = true;
        if (note[0] == '?') {
          if (n == 1) {
            candidate[0] = 8;
          } else {
            if (l == n) {
              if (c[1] & 2) {
                candidate[0] = 8;
                c[1] = 2;
              } else {
                candidate[0] = 9;
              }
            } else {
              if (c[1] & 1) {
                candidate[0] = 1;
                c[1] = 1;
              } else {
                candidate[0] = 4;
              }
            }
          }
        } else {
          candidate[0] = note[0] - '0';
        }
        for (ll i = 1; i < n; i++) {
          bool b = (i >= n - l);
          switch (note[i]) {
            case '1':

          }
        }
      }
      return 0;
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
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
