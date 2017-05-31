#include <bits/stdc++.h>
#if defined(LOCAL)
#include "prettyprint.h"
#endif

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
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
const bool enable_log = true;
#else
const bool enable_log = false;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

struct trie;
using ptrie = shared_ptr<trie>;
struct trie {
  l id = -1;
  vector<ptrie> next;
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  // solution
  l n, m;
  while (cin >> n >> m) {
    ptrie t = make_shared<trie>();
    t->next.resize(26);
    vector<tuple<l,l,l>> words; // size * parent * id
    vector<pair<l, string>> v;
    F(i, 0, n) {
      string s; cin >> s;
      v.emplace_back(make_pair(s.size(), s));
    }
    sort(all(v));
    F(i, 0, n) {
      auto p = t;
      l parent = -1;
      string& s = v[i].second;
      F(j, 0, s.size()) {
        if (p->id != -1) parent = p->id;
        l x = s[j] - 'a';
        if (not p->next[x]) {
          p->next[x] = make_shared<trie>();
          p->next[x]->next.resize(26);
        }
        p = p->next[x];
      }
      words.emplace_back(make_tuple(s.size(), parent, i));
      p->id = i;
    }
    vb used(n);
    l p = 0;
    l k = v.back().first;
    l total = 0;
    l answer = -1;
    F(i, 1, k + 1) {
      while (p < n and get<0>(words[p]) <= i) {
        total++;
        used[p] = true;
        l u = get<1>(words[p]);
        if (u != -1 and used[u]) {
          used[u] = false;
          total--;
        }
        p++;
      }
      if (total >= m) {
        answer = i;
        break;
      }
    }
    cout << answer << lf;
  }
}
