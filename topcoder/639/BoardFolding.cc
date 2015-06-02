#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 260;

class BoardFolding {
  int paper[MAX][MAX];
  int row_count, column_count;
  int tonumber(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    if (c >= 'A' && c <= 'Z') return c - 'A' + 36;
    if (c == '#') return 62;
    return 63;
  }

  vector<vector<int>> dict;

  int get_index(vector<int> &v) {
    for (int i = 0; i < dict.size(); i++) {
      if (dict[i] == v) return i;
    }
    int t = dict.size();
    dict.emplace_back(v);
    return t;
  }

  vector<int> get_rows() {
    vector<int> indexes(row_count);
    for (int row = 0; row < row_count; row++) {
      vector<int> v(column_count);
      for (int column = 0; column < column_count; column++) {
        v[column] = paper[row][column];
      }
      indexes[row] = get_index(v);
    }
    return indexes;
  }

  vector<int> get_columns() {
    vector<int> indexes(column_count);
    for (int column = 0; column < column_count; column++) {
      vector<int> v(row_count);
      for (int row = 0; row < row_count; row++) {
        v[row] = paper[row][column];
      }
      indexes[column] = get_index(v);
    }
    return indexes;
  }
public:
  int howMany(int N, int M, vector <string> compressedPaper) {
    row_count = N;
    column_count = M;
    fill(&paper[0][0], &paper[MAX][0], 0);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        paper[i][j] = (tonumber(compressedPaper[i][j / 6]) >> (j % 6)) % 2;
      }
    }
    // cerr << endl;
    auto rows = get_rows();
    auto columns = get_columns();
    return fold_left(rows, 0, rows.size())
           * fold_left(columns, 0, columns.size());
  }

  int fold_left(vector<int> &row, int begin, int end) {
    int t = 0;
    int l = end - begin;
    for (int i = 2; i <= l; i += 2) {
      if (!symmetrical(row, begin, begin + i)) continue;
      t = fold_left(row, begin + i/2, end);
      break;
    }
    return t + fold_right(row, begin, end);
  }

  int fold_right(vector<int> &row, int begin, int end) {
    int t = 0;
    int l = end - begin;
    for (int i = 2; i <= l; i += 2) {
      if (!symmetrical(row, end - i, end)) continue;
      t = fold_right(row, begin, end - i / 2);
      break;
    }
    return t + 1;
  }

  bool symmetrical(vector<int> &row, int begin, int end) {
    int k = (end - begin) / 2;
    for (int i = 0; i < k; i++) {
      if (row[begin + i] != row[end - i - 1]) return false;
    }
    return true;
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
};

// BEGIN CUT HERE
int main() {
  BoardFolding ___test;
  ___test.run_test(-1);
  ___test.howMany(250, 250, {"000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000", "000000000000000000000000000000000000000000"});
}
// END CUT HERE

// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor