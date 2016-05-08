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
    if (abs(speed) != abs(rhs.speed)) return abs(speed) > abs(rhs.speed);
    return abs(start) > abs(rhs.start);
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
ll Y;
double best;

void backtrack(double x, double t, size_t at_l, size_t at_r,
  vb& l_cached, vb &r_cached) {
  bool stop = true;
  for (size_t i = at_l; i < L.size(); i++) {
    if (l_cached[i]) continue;
    vb lc = l_cached;
    stop = false;
    auto &q = L[i];
    double dt = q.meet(x, t, Y);
    lc[i] = true;
    for (size_t j = 0; j < L.size(); j++) {
      if (lc[j]) continue;
      if (L[j].meet(x, t, Y) <= dt) lc[j] = true;
    }
    backtrack(q.at(t + dt), t + dt, i + 1, at_r, lc, r_cached);
    break;
  }

  for (size_t i = at_r; i < R.size(); i++) {
    if (r_cached[i]) continue;
    vb rc = r_cached;
    stop = false;
    auto &q = R[i];
    double dt = q.meet(x, t, Y);
    rc[i] = true;
    for (size_t j = 0; j < R.size(); j++) {
      if (rc[j]) continue;
      if (R[j].meet(x, t, Y) <= dt) rc[j] = true;
    }
    backtrack(q.at(t + dt), t + dt, at_l, i + 1, l_cached, rc);
    break;
  }

  if (stop) best = min(best, t);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    cerr << tc << endl;
    ll N;
    cin >> Y >> N;
    vll pp(N), ss(N);
    R.clear();
    L.clear();
    for (ll i = 0; i < N; i++) cin >> pp[i];
    for (ll i = 0; i < N; i++) cin >> ss[i];
    for (ll i = 0; i < N; i++) {
      if (pp[i] > 0) {
        R.emplace_back(pp[i], ss[i]);
      } else {
        L.emplace_back(pp[i], -ss[i]);
      }
    }
    sort(R.begin(), R.end());
    sort(L.begin(), L.end());
    // TODO there are at most 250^4 ~= 4e9 possible different states at most
    // so it's feasible to cover some of them + prunning ~0.1%
    best = DINF;
    vb r_cached(R.size()), l_cached(L.size());
    backtrack(0, 0, 0, 0, l_cached, r_cached);
    cout << "Case #" << tc << ": "
    << fixed << setprecision(7) << best << endl;
  }
}
