#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 251;

struct rect {
  int x1, y1, x2, y2;
};

class BoardFolding {
  int paper[MAX][MAX];
  int tonumber(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    if (c >= 'A' && c <= 'Z') return c - 'A' + 36;
    if (c == '#') return 62;
    return 63;
  }

public:
  int howMany(int N, int M, vector <string> compressedPaper) {
    fill(&paper[0][0], &paper[MAX][0], 0);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        paper[i][j] = (tonumber(compressedPaper[i][j / 6]) >> (j % 6)) % 2;
      }
    }
    rect r;
    r.x1 = 0;
    r.x2 = N;
    r.y1 = 0;
    r.y2 = M;
    return fold1(r);
  }

  bool v_sym(rect a) {
    int k = a.x2 - a.x1;
    for (int i = 0; i < a.x2 - a.x1; i++) {
      for (int j = a.y1; j < a.y2; j++) {
        if (paper[a.x1 + i][j] != paper[a.x2 + k - i - 1][j]) return false;
      }
    }
    return true;
  }

  int fold1(rect r) {
    int t = 0;
    int l = r.x2 - r.x1;
    for (int i = 1; i < (l + 1) / 2; i++) {
      if (v_sym({r.x1, r.y1, r.x1 + i, r.y2})) {
        t += fold1({r.x1 + i + 1, r.y1, r.x2, r.y2});
      }
    }
    if (l % 2 == 0) {
      l = l / 2;
      if (v_sym({r.x1, r.y1, r.x1 + l, r.y2})) {
        t += 2 * fold1({r.x1 + l, r.y1, r.x2, r.y2});
      }
    }
    return t + fold2(r);
  }

  int fold2(rect r) {
    return 1;
  }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; string Arr2[] = {"1", "3"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; verify_case(0, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 7; string Arr2[] = {"@@", "@@"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 84; verify_case(1, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 4; string Arr2[] = {"6", "9", "9", "6"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 9; verify_case(2, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 6; int Arg1 = 1; string Arr2[] = {"0", "2", "6", "@", "4", "A"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 6; verify_case(3, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 3; int Arg1 = 3; string Arr2[] = {"0", "2", "0"}
; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; verify_case(4, Arg3, howMany(Arg0, Arg1, Arg2)); }

// END CUT HERE
;
};

// BEGIN CUT HERE
int main() {
  BoardFolding ___test;
  ___test.run_test(-1);
}
// END CUT HERE
