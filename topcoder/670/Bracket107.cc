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

class Bracket107 {
    public:
    bool balanced(string& s) {
      l t = 0;
      for (auto c : s) {
        if (c == '(') t++;
        if (c == ')') {
          t--;
          if (t < 0) return false;
        }
      }
      return t == 0;
    }
    int yetanother(string s) {
      // cerr << s << endl;
      unordered_set<string> q;
      q.insert(s);
      l n = s.size();
      for (l i = 0; i < n; i++) {
        for (l j = 0; j < n; j++) {
          string t = s;
          t.insert(t.begin() + j, s[i]);
          if (i < j) {
            t.erase(i, 1);
          } else {
            t.erase(i + 1, 1);
          }
          // cerr << t << endl;
          if (balanced(t)) q.insert(t);
        }
      }
      return q.size() - 1;
     }
};

// BEGIN CUT HERE
int main() {
  Bracket107 t;
  cout << t.yetanother("(())") << endl;
  cout << t.yetanother("()()()") << endl;
  cout << t.yetanother("(((())))") << endl;
  cout << t.yetanother("((())())") << endl;
}
// END CUT HERE
