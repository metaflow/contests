#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

class Coversta {
  vvi v;
  vvi sum;
  int n, m, k;

  bool out(int a, int b) {
    return a < 0 || a >= n || b < 0 || b >= m;
  }

  void update_sum(int a, int b, int s, vi& x, vi& y) {
    for (int j = 0; j < k; j++) {
      int c = a + x[j]; int d = b + y[j];
      if (out(c, d)) continue;
      int q = v[c][d];
      for (int g = 0; g < k; g++) {
        int e = c - x[g]; int f = d - y[g];
        if (out(e, f)) continue;
        sum[e][f] += q * s;
      }
    }
  }
public:
  int place(vector <string> field, vector <int> x, vector <int> y) {
    n = field.size(); m = field[0].size(); k = x.size();
    v.clear(); sum.clear(); v.resize(n); sum.resize(n);
    for (int i = 0; i < n; i++) {
      v[i].resize(m);
      for (int j = 0; j < m; j++) {
        v[i][j] = field[i][j] - '0';
      }
    }

    vector<ii> coords;
    for (int i = 0; i < n; i++) {
      sum[i].resize(m, 0);
      for (int j = 0; j < m; j++) {
        coords.emplace_back(i, j);
        for (int d = 0; d < k; d++) {
          int a = i + x[d]; int b = j + y[d];
          if (out(a, b)) continue;
          sum[i][j] += v[a][b];
        }
      }
    }
    sort(coords.begin(), coords.end(), [&] (const ii& l, const ii& r) {
      return sum[l.first][l.second] > sum[r.first][r.second];
    });
    int best = 0;
    for (int i = 0; i < coords.size() - 1; i++) {
      int a = coords[i].first; int b = coords[i].second;
      int candidate = sum[a][b];
      if (candidate + sum[coords[i + 1].first][coords[i + 1].second] < best) {
        break;
      }
      update_sum(a, b, -1, x, y);
      int best_left = 0;
      for (int l = i + 1; l < coords.size() && l < i + 110; l++) {
        best_left = max(best_left, sum[coords[l].first][coords[l].second]);
      }
      best = max(best, candidate + best_left);
      update_sum(a, b, +1, x, y);
    }
    return best;
  }

// BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"11",
 "11"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 4; verify_case(0, Arg3, place(Arg0, Arg1, Arg2)); }
 void test_case_1() { string Arr0[] = {"11",
 "11"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; verify_case(1, Arg3, place(Arg0, Arg1, Arg2)); }
 void test_case_2() { string Arr0[] = {"15",
 "61"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 11; verify_case(2, Arg3, place(Arg0, Arg1, Arg2)); }
 void test_case_3() { string Arr0[] = {"151",
 "655",
 "661"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,-1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0,1,0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 33; verify_case(3, Arg3, place(Arg0, Arg1, Arg2)); }
 void test_case_4() { string Arr0[] = {"303",
 "333",
 "000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1,-1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {-1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 12; verify_case(4, Arg3, place(Arg0, Arg1, Arg2)); }
 void test_case_5() { string Arr0[] = {"0000000",
 "1010101"}
 ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1,-1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {-1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 0; verify_case(5, Arg3, place(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  Coversta ___test;
  ___test.run_test(-1);
}
// END CUT HERE

