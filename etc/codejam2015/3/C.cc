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
    assert(r >= 0);
    return r;
  }
};

vector<quali> R, L;
vb Rv, Lv;
ll Y;

// IDA* TSP with bitmask up to 64 vertices
struct ida_state {
  double x, t;
};

double ida_updated_bound;
double estimate(ida_state &s) {
  double a = 0, b = 0;
  for (size_t i = 0; i < R.size(); i++) {
    if (Rv[i]) continue;
    a = max(a, R[i].meet(s.x, s.t, Y));
  }
  for (size_t i = 0; i < L.size(); i++) {
    if (Lv[i]) continue;
    b = max(b, L[i].meet(s.x, s.t, Y));
  }
  return a + b;
}

bool ida_dfs(ida_state& s, double bound) {
  double e = estimate(s);
  // cerr << "e " << e << endl;
  if (e + s.t > bound) {
    ida_updated_bound = min(ida_updated_bound, e + s.t);
    return false;
  }
  if (e == 0) return true;
  int min_index = -1;
  double m = DINF;
  for (size_t i = 0; i < R.size(); i++) {
    if (Rv[i]) continue;
    double w = R[i].meet(s.x, s.t, Y);
    if (w < m) {
      m = w;
      min_index = i;
    }
  }
  if (min_index != -1) {
    Rv[min_index] = true;
    s.t += m;
    s.x += m * Y;
    if (ida_dfs(s, bound)) return true;
    s.t -= m;
    s.x -= m * Y;
    Rv[min_index] = false;
  }

  min_index = -1;
  m = DINF;
  for (size_t i = 0; i < L.size(); i++) {
    if (Lv[i]) continue;
    double w = L[i].meet(s.x, s.t, Y);
    if (w < m) {
      m = w;
      min_index = i;
    }
  }
  if (min_index != -1) {
    Lv[min_index] = true;
    s.t += m;
    s.x -= m * Y;
    if (ida_dfs(s, bound)) return true;
    s.t -= m;
    s.x += m * Y;
    Lv[min_index] = false;
  }
  return false;
}

double tsp(ida_state& s) {
  double bound = 0;
  while (bound < DINF) {
    // cerr << "T " << bound << endl;
    ida_updated_bound = DINF;
    if (ida_dfs(s, bound)) break;
    bound = ida_updated_bound;
  }
  return bound;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    cerr << tc << endl;
    ll N;
    cin >> Y >> N;
    vll pp(N), ss(N);
    for (ll i = 0; i < N; i++) cin >> pp[i];
    for (ll i = 0; i < N; i++) cin >> ss[i];
    R.clear();
    L.clear();
    for (ll i = 0; i < N; i++) {
      if (pp[i] > 0) {
        R.emplace_back(pp[i], ss[i]);
      } else {
        L.emplace_back(pp[i], -ss[i]);
      }
    }
    Rv.clear(); Rv.resize(R.size());
    Lv.clear(); Lv.resize(L.size());
    ida_state s;
    s.x = 0;
    s.t = 0;
    cout << "Case #" << tc << ": "
    << fixed << setprecision(7) << tsp(s) << endl;
  }
}
