#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

struct dot {
  int x, y;
  int q;
  int index;
  int sum;
  bool real;
};

class TrianglesContainOrigin {
public:
  long long count(vector <int> x, vector <int> y) {
    vector<dot> dd;
    for (int i = 0; i < x.size(); i++) {
      dot d;
      d.real = true;
      d.x = x[i];
      d.y = y[i];
      d.sum = 0;
      d.index = i;
      d.q = 1;
      if (d.y < 0) {
        d.q +=2;
      }
      if (d.x * d.y < 0) {
        swap(d.x, d.y);
        d.q++;
      }
      d.x = abs(d.x);
      d.y = abs(d.y);
      dd.emplace_back(d);
      d.q += 2;
      d.real = false;
      dd.emplace_back(d);
    }

    sort(dd.begin(), dd.end(), [] (const dot &a, const dot &b) {
      if (a.q == b.q) return b.x * a.y < b.y * a.x;
      return a.q < b.q;
    });

    vector<int> back(x.size());

    int sum = 0;

    for (int i = 0; i < dd.size(); i++) {
      // printf("%d (%d, %d) %c\n",
        //dd[i].q, dd[i].x, dd[i].y, (dd[i].real ? '.' : 'o'));
      if (dd[i].real) {
        sum++;
      } else {
        back[dd[i].index] = i;
      }
      dd[i].sum = sum;
    }

    ll r = 0;
    for (int i = 0; i < dd.size(); i++) {
      if (!dd[i].real) continue;
      for (int j = i + 1; j < dd.size(); j++) {
        if (dd[j].index == dd[i].index) break;
        if (!dd[j].real) continue;
        // cerr << '+' << back[dd[i].index] << ".." << back[dd[j].index] <<
        //  " " << dd[back[dd[j].index]].sum - dd[back[dd[i].index]].sum << endl;
        r += dd[back[dd[j].index]].sum - dd[back[dd[i].index]].sum;
      }
    }

    // printf("------------\n");
    return r;
  }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {-1,-1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,-1,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 1LL; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {-1,-1,1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,-1,2,-1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 2LL; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {-1,-2,3,3,2,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-2,-1,1,2,3,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 8LL; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {1,5,10,5,-5,7,-9,-6,-3,0,8,8,1,-4,7,-3,10,9,-6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5,-6,-3,4,-2,-8,-7,2,7,4,2,0,-4,-8,7,5,-5,-2,-9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 256LL; verify_case(3, Arg2, count(Arg0, Arg1)); }

// END CUT HERE
;
};

// BEGIN CUT HERE
int main() {
  TrianglesContainOrigin ___test;
  ___test.run_test(-1);
}
// END CUT HERE
