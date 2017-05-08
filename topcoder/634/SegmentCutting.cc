#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

class SegmentCutting {
public:
  void add(vl& v, l t) {
    v[0]++;
    v[1] += t;
    v[2] += t * t;
  }

  void remove(vl& v, l t) {
    v[0]--;
    v[1] -= t;
    v[2] -= t * t;
  }
  l value(vvl& v) {
    return v[0][2] * v[1][0] - 2 * v[0][1] * v[1][1] + v[0][0] * v[1][2];
  }
  long long maxValue(vector <int> x, vector <int> y) {
    l answer = 0;
    l n = x.size();
    F(o, 0, n) {
      vector<tuple<double, l>> p;
      F(i, 0, n) if (i != o) {
        p.emplace_back(make_tuple(atan2(y[i] - y[o], x[i] - x[o]), i));
        p.emplace_back(make_tuple(atan2(y[i] - y[o], x[i] - x[o]) + 2 * PI, i));
      }
      sort(all(p));
      vvl xx(2, vl(3));
      auto yy = xx;
      l j = 0;
      while (get<0>(p[j]) - get<0>(p[0]) < PI) {
        add(xx[0], x[get<1>(p[j])]);
        add(yy[0], y[get<1>(p[j])]);
        j++;
      }
      F(i, j, n - 1) {
        add(xx[1], x[get<1>(p[i])]);
        add(yy[1], y[get<1>(p[i])]);
      }
      add(xx[1], x[o]);
      add(yy[1], y[o]);
      assert(xx[0][0] + xx[1][0] == n);
      F(i, 0, n) {
        l t = value(xx) + value(yy);
        if (answer < t) {
          // LOG << answer << ' '
              // << o << ' '  << get<1>(p[i]) << ' ' << get<1>(p[j]) << endl;
        }
        answer = max(answer, value(xx) + value(yy));
        add(xx[1], x[get<1>(p[i])]);
        add(yy[1], y[get<1>(p[i])]);
        remove(xx[0], x[get<1>(p[i])]);
        remove(yy[0], y[get<1>(p[i])]);
        while (j < 2 * (n - 1) and get<0>(p[j]) - get<0>(p[i + 1]) < PI) {
          add(xx[0], x[get<1>(p[j])]);
          add(yy[0], y[get<1>(p[j])]);
          remove(xx[1], x[get<1>(p[j])]);
          remove(yy[1], y[get<1>(p[j])]);
          j++;
        }
      }
    }
    return answer;
  }
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 25LL; verify_case(0, Arg2, maxValue(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {0,0,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,1,0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 6LL; verify_case(1, Arg2, maxValue(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {-6, 3, -4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 0, 5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 159LL; verify_case(2, Arg2, maxValue(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {0, 2,-2, 4,-4, 2,-2, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 2, 4, 4, 6, 6, 5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 430LL; verify_case(3, Arg2, maxValue(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 4, 9, 16, 25, 36, 49, 64, 81, 100}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 94640LL; verify_case(4, Arg2, maxValue(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {-24,11,-235,49,13,-247,-575,80,35,29,1,-9,-1,-1,-27,-3,-20,13,-33,111,
-36,30,-303,-645,-23,-5,393,227,89,145,6,515,234,271,-901,239,-368,-642,
-3,125,-63,2,221,-113,1,6,3,-31,-6,-49,-785,314,363,-2,34,15,465,11,32,
-72,394,20,-8,-448,429,-7,-88,-11,-42,-8,2,-707,-231,-143,76,-10,-152,
-66,24,-73,778,-29,807,-63,722,-804,413,-21,-2,-131,26,3,-23,101,-551,
-58,21,180,-15,-88,410,604,74,956,62,275,-352,-93,291,184,70,564,-594,
-101,-391,18,115,-329,8,-4,-218,77,218,-145,27,-34,598,-87,-243,-323,34,
211,7,-145,-49,528,-13,10,-778,184,-65,101,-232,503,-6,69,553,-14,25,26,
854,955,-10,-490,-674,-4,9,-373,42,-121,-528,67,-32,23,74,81,-752,-7,
-122,-464,-174,-722,46,961,57,-105,269,48,64,-585,-107,641,9,27,297,5,
-44,107,-600,113,468,-24,-104,277,10,5,75,106,-591,38}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1,-2,62,-8,-1,28,-47,241,-10,-3,3,-41,1,95,111,-4,-114,503,1,19,3,
-26,615,762,7,-52,399,-174,-987,30,-49,165,67,551,-214,-36,-108,-242,
-967,69,698,-120,-298,20,-43,32,-171,2,-9,8,50,948,-2,-30,-3,53,-411,
410,141,-8,292,41,71,-523,-329,-284,8,84,34,559,-160,2,73,12,276,-16,
-33,-63,119,869,127,47,963,-7,-995,146,-161,775,17,-5,-167,-315,59,
-345,10,766,-10,-6,850,12,-5,-17,295,-89,14,71,-11,-305,13,-524,181,
-279,-11,15,437,349,20,10,-749,82,25,336,-6,-794,-944,895,-52,72,198,
194,-988,641,-59,-434,-524,-381,368,6,-14,125,-55,319,-666,-610,-274,
359,-39,206,28,-719,-150,51,-366,-341,89,13,-635,-287,56,35,665,103,-81,
156,-4,888,-48,96,-48,340,61,396,272,-16,335,219,-388,15,324,24,-194,9,
-310,7,-25,5,39,-342,118,-92,425,-336,796,950,-419,-812,-488,428,-32,-9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 5887914054LL; verify_case(5, Arg2, maxValue(Arg0, Arg1)); }

// END CUT HERE
;
};

// BEGIN CUT HERE
int main() {
  SegmentCutting ___test;
  ___test.run_test(-1);
}
// END CUT HERE
