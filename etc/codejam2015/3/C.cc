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
using dd = pair<double, double>;
const int INF = numeric_limits<int>::max();
const double DINF = 1e20;
const double EPS = 1e-10;

struct quali {
  ll start, speed;
  double at(double t) {
    return start + speed * t;
  }
  quali() {}
  quali(ll a, ll b): start(a), speed(b) {}
  bool operator < (const quali& rhs) const {
    if (speed != rhs.speed) return speed < rhs.speed;
    return start < rhs.start;
  }
  double meet(double x, double t, ll Y) {
    double v = start + speed * t;
    double r;
    if (speed > 0) {
      r = (v - x) / (Y - speed);
    } else {
      r = (x - v) / (Y + speed);
    }
    if (r < 0) {
      cerr << "r " << r << " " << v << " -> " << x << t << endl;
      assert(r >= 0);
    }
    return r;
  }
};

vector<quali> Q;
vb Rv, Lv;
ll Y;

struct as_state {
  vb catched;
  int cc;
  int quali;
  size_t h;
  double t, e;
  const bool operator < (const as_state& rhs) const {
    if (quali != rhs.quali) return quali < rhs.quali;
    if (cc != rhs.cc) return cc < rhs.cc;
    return catched < rhs.catched;
  }
  const bool operator == (const as_state& rhs) const {
    return (quali == rhs.quali) && (cc == rhs.cc) && (catched == rhs.catched);
  }
  void hash() {
    h = quali * cc;
    for (int i = 0; i < catched.size(); i++) {
      if (!catched[i]) continue;
      h = h ^ (1 << ((i * quali) % 60));
    }
  }
  void estimate() {
    double x = Q[quali].at(t);
    double l = 0, r = 0;
    for (size_t i = 1; i < Q.size(); i++) {
      if (catched[i]) continue;
      double d = Q[i].meet(x, t, Y);
      if (Q[i].start < 0) {
        l = max(l, d);
      } else {
        r = max(r, d);
      }
    }
    e = r + l;
    hash();
    // cerr << "e = " << e << endl;
  }
};

// adj[u][?] = (v, x) - edge from u to v of weight x
double shortest_paths(as_state from) {
  double best = DINF;

  auto hh = [] (const as_state& a) { return a.h; };
  unordered_map<as_state, double, decltype(hh)> actual_time(100, hh);
  auto by_time = [] (const as_state& lhs, const as_state& rhs) {
    return lhs.e > rhs.e;
  };
  priority_queue<as_state, vector<as_state>, decltype(by_time)> pq(by_time);
  actual_time[from] = from.e;
  pq.emplace(from);

  while (!pq.empty()) {
    auto u = pq.top(); pq.pop();
    if (actual_time[u] < u.e) continue;
    // cerr << " " << u.e << endl;
    if (u.e >= best) break;
    double t = u.t;
    double x = Q[u.quali].at(t);
    ll leftmost = 0, rightmost = 0;
    double l = DINF, r = DINF;
    for (size_t i = 1; i < Q.size(); i++) {
      if (u.catched[i]) continue;
      double d = Q[i].meet(x, t, Y);
      if (Q[i].start < 0) {
        if (l <= d) continue;
        l = d;
        leftmost = i;
      } else {
        if (r <= d) continue;
        r = d;
        rightmost = i;
      }
    }

    u.cc++;
    if (leftmost != 0) {
      u.t += l;
      u.quali = leftmost;
      u.catched[leftmost] = true;
      u.estimate();
      if (u.e < best) {
        auto &d = actual_time[u];
        if (d == 0 || d > u.e) {
          d = u.e;
          pq.emplace(u);
          // cerr << "enqueue" << endl;
        }
      }
      u.t -= l;
      u.catched[leftmost] = false;
    }

    if (rightmost != 0) {
      //auto v = u;
      u.t += r;
      u.quali = rightmost;
      u.catched[rightmost] = true;
      u.estimate();
      if (u.e < best) {
        auto &d = actual_time[u];
        if (d == 0 || d > u.e) {
          d = u.e;
          pq.emplace(u);
          // cerr << "enqueue" << endl;
        }
      }
    }
    if (rightmost == 0 && leftmost == 0) {
      best = min(best, t);
    }
    // cerr << "T " << actual_time.size() << endl;
  }
  return best;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
/*
  auto by_time = [] (const as_state& lhs, const as_state& rhs) {
    return lhs.t < rhs.t;
  };
  priority_queue<as_state, vector<as_state>, decltype(by_time)> pq(by_time);
  */

  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    cerr << tc << endl;
    ll N;
    Q.clear();
    quali me(0, 0);
    Q.emplace_back(me);
    cin >> Y >> N;
    vll pp(N), ss(N);
    for (ll i = 0; i < N; i++) cin >> pp[i];
    for (ll i = 0; i < N; i++) cin >> ss[i];
    for (ll i = 0; i < N; i++) {
      if (pp[i] > 0) {
        Q.emplace_back(pp[i], ss[i]);
      } else {
        Q.emplace_back(pp[i], -ss[i]);
      }
    }
    // TODO there are at most 250^4 ~= 4e9 possible different states at most
    // so it's feasible to cover some of them + prunning ~0.1%
//    uniq_states.clear();
    as_state start;
    start.catched.resize(Q.size(), false);
    start.catched[0] = true;
    start.quali = 0;
    start.cc = 1;
    start.t = 0;
    start.estimate();
    cout << "Case #" << tc << ": "
    << fixed << setprecision(7) << shortest_paths(start) << endl;
  }
}
