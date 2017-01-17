#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

#define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc;
  cin >> tcc;
  for (l tc = 1; tc <= tcc; tc++) {
    l dogs, cats, legs;
    cin >> cats >> dogs >> legs;
    bool ok = legs % 4 == 0;
    legs /= 4;
    ok = ok and (legs <= dogs + cats) and (legs >= (dogs + max((l)0, cats - dogs * 2)));
    cout << (ok ? "yes" : "no") << endl;
  }
}
