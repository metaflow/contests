#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

// intervals are inclusive [a, b]
// e.g. [1, 2] + [2, 3] -> [1, 3]
// and find([4, 7]) -> ([1, 4], [5, 6], [7, 11])
class interval_tree {
private:
  struct intervals_key {
    bool operator() (const ii& a, const ii& b) {
      return a.second < b.first;
   };
  };
  map<ii, int, intervals_key> m;
  friend ostream& operator << (ostream& s, const interval_tree& v) {
    for (auto ii = v.m.cbegin(); ii != v.m.cend(); ii++) {
      s << "[" << ii->first.first << ", " << ii->first.second << "] ";
    }
    return s;
  }
public:
  void add(int a, int b) {
    vii r;
    auto p = m.equal_range(make_pair(a, b));
    for (auto ii = p.first; ii != p.second; ii++) r.emplace_back(ii->first);
    m.erase(p.first, p.second);
    for (auto ii : r) {
      a = min(a, ii.first);
      b = max(b, ii.second);
    }
    m.emplace(make_pair(a, b), 0);
  }

  void remove(int a, int b) {
    auto p = m.equal_range(make_pair(a, b));
    vii r;
    for (auto ii = p.first; ii != p.second; ii++) r.emplace_back(ii->first);
    m.erase(p.first, p.second);
    for (auto ii : r) {
      if (ii.first < a) {
        m.emplace(make_pair(ii.first, min(a, ii.second)), 0);
      }
      if (ii.second > b) {
        m.emplace(make_pair(max(b, ii.first), ii.second), 0);
      }
    }
  }

  vii find(int a, int b) {
    vii r;
    auto p = m.equal_range(make_pair(a, b));
    for (auto i = p.first; i != p.second; i++) r.emplace_back(i->first);
    return r;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n, m, w;
  int tc = 1;
  while (cin >> m >> n >> w, n) {
    // <x, type (1 (+) , 0 (-) range of y's), y1, y2>
    priority_queue<tuple<int, int, int, int>> events;
    ll unexplored_area = n * m;
    for (int ii = 0; ii < w; ii++) {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      events.emplace(x1, 1, y1, y1 + 1);
      events.emplace(x2 + 1, 0, y1, y1 + 1);
      unexplored_area -= ll(x2 + 1 - x1);
    }
    events.emplace(0, 0, 0, 0);
    events.emplace(n, 1, 0, 0);
    interval_tree r;
    r.add(0, m);
    vii wave;
    wave.emplace_back(m - 1, m);
    int x_last = n;
    while (!events.empty()) {
      int x = get<0>(events.top());
      // add traveled area
      for (auto ww : wave) {
        unexplored_area -= ll(ww.second - ww.first) * ll(x_last - x);
      }
      // update field profile
      // cerr << "x = " << x << endl;
      while (!events.empty() && get<0>(events.top()) == x) {
        auto e = events.top(); events.pop();
        int y1 = get<2>(e);
        int y2 = get<3>(e);
        int t = get<1>(e);
        switch (t) {
          case 0:
            r.remove(y1, y2);
            // cerr << "- [" << y1 << ", " << y2 << "]" << endl;
            break;
          case 1:
            r.add(y1, y2);
            // cerr << "+ [" << y1 << ", " << y2 << "]" << endl;
            break;
        }
      }
      // cerr << "= " << r << endl;
      // update wave
      vii new_wave; // top-down ordered
      int bottom = m;
      for (auto ww : wave) {
        auto match = r.find(ww.first, ww.second);
        reverse(match.begin(), match.end());
        for (auto mm : match) {
          if (mm.first >= ww.second || mm.second <= ww.first) continue;
          int a = mm.first;
          if (a >= bottom) continue;
          bottom = a;
          int b = min(mm.second, ww.second);
          new_wave.emplace_back(a, b);
        }
      }
      swap(wave, new_wave);
      // cerr << "wave = ";
      // for (auto ww : wave) cerr << "[" << ww.first << ", " << ww.second << "] ";
      // cerr << endl;
      x_last = x;
    }
    cout << "Case " << tc << ": " << unexplored_area << endl;
    tc++;
  }
}
