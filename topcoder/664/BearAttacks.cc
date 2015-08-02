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

struct node {
  ll id, parent;
  vll adjusted;
};

const ll BILLION = 1000000000;

class BearAttacks {
    public:
    int expectedValue(ll N, ll R0, ll A, ll B, ll M, ll LOW, ll HIGH) {
      vector<node> g(N);
      ll R = R0;
      for (ll i = 0; i < N; i++) {
        g[i].id = i; g[i].parent = -1;
        R = (A * R + B) % M;
        ll MIN = ((i-1) * LOW) / BILLION;
        ll MAX = ((i-1) * HIGH) / BILLION;
        if (i == 0) {
          MIN = ((i-1) * LOW);
          if ((-MIN) % BILLION != 0) MIN -= BILLION;
          MIN /= BILLION;
          MAX = ((i-1) * HIGH);
          if ((-MAX) % BILLION != 0) MAX -= BILLION;
          MAX /= BILLION;
        }
        cerr << MIN << " " << MAX << endl;
        ll u = MIN + (R % (MAX - MIN + 1));
        cout << i << " - " << u << endl;
        g[i].adjusted.emplace_back(u);
        g[u].adjusted.emplace_back(i);
      }
      return 0;
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 0; int Arg2 = 2; int Arg3 = 3; int Arg4 = 100; int Arg5 = 938593850; int Arg6 = 1000000000; int Arg7 = 21; verify_case(0, Arg7, expectedValue(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 0; int Arg2 = 0; int Arg3 = 0; int Arg4 = 1; int Arg5 = 0; int Arg6 = 0; int Arg7 = 23; verify_case(1, Arg7, expectedValue(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_2() { int Arg0 = 6; int Arg1 = 303840291; int Arg2 = 848660283; int Arg3 = 395739574; int Arg4 = 950123456; int Arg5 = 0; int Arg6 = 1000000000; int Arg7 = 3856; verify_case(2, Arg7, expectedValue(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_3() { int Arg0 = 1; int Arg1 = 0; int Arg2 = 0; int Arg3 = 0; int Arg4 = 1; int Arg5 = 0; int Arg6 = 0; int Arg7 = 1; verify_case(3, Arg7, expectedValue(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_4() { int Arg0 = 19; int Arg1 = 384038999; int Arg2 = 938592393; int Arg3 = 692854433; int Arg4 = 1000000000; int Arg5 = 300000000; int Arg6 = 600000000; int Arg7 = 473263988; verify_case(4, Arg7, expectedValue(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
    BearAttacks ___test;
    ___test.run_test(-1);
}
// END CUT HERE
