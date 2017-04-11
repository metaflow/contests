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
#define ALL(x) begin(x), end(x)
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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ifstream fin("C.in"); cin.rdbuf(fin.rdbuf());
  ofstream fout("C.in.o"); cout.rdbuf(fout.rdbuf());
  l friendCount, basicCount, compositeCount, purchases;
  l tt = 0;
  tt ++;
  cout << tt << endl;
  while (cin >> friendCount >> basicCount >> compositeCount >> purchases) {
    map<string, l> names;
    F(i, 0, basicCount) {
      string s; cin >> s;
      // LOG << s << endl;
      l j = names.size();
      names[s] = j;
    }
    // for (auto n : names) LOG << n.first << ' ' << n.second << endl;
    string s;
    getline(cin, s);
    vvl composite(101, vl(basicCount));
    F(i, 0, compositeCount) {
      getline(cin, s);
      // LOG << s << endl;
      stringstream ss(s);
      ss >> s;
      s.pop_back();
      l c = names.size();
      names[s] = c;
      while (ss >> s) {
        l j = names[s];
        string no; ss >> no;
        if (no.back() == ',') no.pop_back();
        composite[c][j] += stol(no);
      }
    }
    vvl arts(friendCount, vl(names.size()));
    F(i, 0, purchases) {
      l f; cin >> f >> s; f--;
      l a = names[s];
      arts[f][a]++;
      F(k, basicCount, basicCount + compositeCount) {
        bool ok = true;
        F(m, 0, basicCount) ok = ok and (composite[k][m] <= arts[f][m]);
        if (ok) {
          arts[f][k]++;
          F(m, 0, basicCount) arts[f][m] -= composite[k][m];
          break;
        }
      }
    }
    F(i, 0, friendCount) {
      l n = 0;
      F(j, 0, names.size()) if (arts[i][j]) n++;
      cout << n << '\n';
      for (auto item : names) {
        if (arts[i][item.second]) cout << item.first << ' ' << arts[i][item.second] << '\n';
      }
    }
  }
}
