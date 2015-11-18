#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;
const l MOD = 1000000007;

class BearCavalry {
    void add(l& a, l b) {
      a = (a + b) % MOD;
    }
    public:
    int countAssignments(vector <int> warriors, vector <int> horses) {
        sort(horses.begin(), horses.end());
        l n = warriors.size();
        sort(warriors.begin() + 1, warriors.end());
        reverse(warriors.begin() + 1, warriors.end());
        l answer = 0;
        for (l i = 0; i < n; i++) {
          l cap = warriors[0] * horses[i];
          vector<bool> mask(n);
          mask[i] = true;
          l m = 1;
          for (l j = 1; j < n; j++) {
            l k = n - 1;
            while (k >= 0 &&
                  (mask[k] ||
                  (horses[k] * warriors[j] >= cap))) k--;
            l t = 0; for (l q = 0; q <= k; q++) if (!mask[q]) t++;
            m = (m * t) % MOD;
            if (m == 0) break;
            mask[k] = true;
            // cerr << t << endl;
          }
          // cerr << m << endl;
          add(answer, m);
        }
        // cerr << "---" << endl;
        return answer;
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {5,8,4,8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {19,40,25,20}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(0, Arg2, countAssignments(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(1, Arg2, countAssignments(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {10,2,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {100,150,200}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(2, Arg2, countAssignments(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {10,20}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(3, Arg2, countAssignments(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {20,20,25,23,24,24,21}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {20,25,25,20,25,23,20}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(4, Arg2, countAssignments(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {970,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,
800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
1000,1000,1000,1000,1000,1000,1000,1000,1000,1000}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 318608048; verify_case(5, Arg2, countAssignments(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
    BearCavalry ___test;
    ___test.run_test(-1);
}
// END CUT HERE
