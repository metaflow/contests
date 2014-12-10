#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 260;

struct rect {
  int x1, y1, x2, y2;
};

class BoardFolding {
  int paper[MAX][MAX];
  int sum[MAX][MAX];
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
    fill(&sum[0][0], &sum[MAX][0], 0);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        paper[i][j] = (tonumber(compressedPaper[i][j / 6]) >> (j % 6)) % 2;
        cerr << paper[i][j];
        sum[i+1][j+1] = sum[i][j+1] + sum[i+1][j] + paper[i][j] - sum[i][j];
      }
      cerr << endl;
    }
    cerr << endl;
    // full rows
    int a = 0, b;
    bool full = true;
    for (int i = 1; i <= N; i++) {
      b = sum[i][M];
      if ((b - a) == 0 || b - a == M) {
        a = b;
        continue;
      }
      full = false;
      break;
    }
    if (full) {
      //cerr << "full rows" << endl;
      return fold1({0, 0, N, 1}) * M * (M + 1) / 2;
    }

    // full columns
    a = 0;
    full = true;
    for (int i = 1; i <= M; i++) {
      b = sum[N][i];
      if ((b - a) == 0 || (b - a) == N) {
        a = b;
        continue;
      }
      full = false;
      break;
    }

    if (full) {
      //cerr << "full columns" << endl;
      return fold1({0, 0, 1, M}) * N * (N + 1) / 2;
    }

    return fold1({0, 0, N, M});
  }

  int rect_sum(rect a) {
    return sum[a.x1][a.y1] + sum[a.x2][a.y2]
         - sum[a.x1][a.y2] - sum[a.x2][a.y1];
  }

  bool vertical(rect a) {
    //if (rect_sum(a) == 0) return true;
    int k = (a.x2 - a.x1) / 2;
    for (int i = 0; i < k; i++) {
      for (int j = a.y1; j < a.y2; j++) {
        if (paper[a.x1 + i][j] != paper[a.x2 - i - 1][j]) return false;
      }
    }
    return true;
  }

  bool horizontal(rect a) {
    //if (rect_sum(a) == 0) return true;
    int k = (a.y2 - a.y1) / 2;
    for (int i = 0; i < k; i++) {
      for (int j = a.x1; j < a.x2; j++) {
        if (paper[j][a.y1 + i] != paper[j][a.y2 - i - 1]) return false;
      }
    }
    return true;
  }

  int fold1(rect r) {
    int t = 0;
    int l = r.x2 - r.x1;
    for (int i = 2; i <= l; i += 2) {
      if (!vertical({r.x1, r.y1, r.x1 + i, r.y2})) continue;
      t = fold1({r.x1 + i/2, r.y1, r.x2, r.y2});
      break;
    }
    return t + fold2(r);
  }

  int fold2(rect r) {
    int t = 0;
    int l = r.x2 - r.x1;
    for (int i = 2; i <= l; i += 2) {
      if (!vertical({r.x2 - i, r.y1, r.x2, r.y2})) continue;
      t = fold2({r.x1, r.y1, r.x2 - i/2, r.y2});
      break;
    }
    return t + fold3(r);
  }

  int fold3(rect r) {
    int t = 0;
    int l = r.y2 - r.y1;
    for (int i = 2; i <= l; i += 2) {
      if (!horizontal({r.x1, r.y1, r.x2, r.y1 + i})) continue;
      t = fold3({r.x1, r.y1 + i/2, r.x2, r.y2});
      break;
    }
    return t + fold4(r);
  }

  int fold4(rect r) {
    int t = 0;
    int l = r.y2 - r.y1;
    for (int i = 2; i <= l; i += 2) {
      if (!horizontal({r.x1, r.y2 - i, r.x2, r.y2})) continue;
      t = fold4({r.x1, r.y1, r.x2, r.y2 - i/2});
      break;
    }
    return t + 1;
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
  cerr << ___test.howMany(250, 250, {"mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "FpFBFppqFpFBFBCBFpFBFppqFppqmqpqFpFBFppqF9", "mCmqmCCBmCmqmqpqmCmqmCCBmCCBFBCBmCmqmCCBm6"});


}
// END CUT HERE
