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
const double EPS = 1e-10;

struct quali {
  ll start, speed;
  double at(double t) {
    return start + speed * t;
  }
  quali(ll a, ll b): start(a), speed(b) {}
  bool operator < (const quali& rhs) const {
    if (speed != rhs.speed) return speed < rhs.speed;
    return start < rhs.start;
  }
};

// time, position
stack<pair<int, double>> get_hull(vector<quali>& q) {
  stack<pair<int, double>> s; // index, time
  for (size_t i = 0; i < q.size(); i++) {
    auto u = q[i];
    while (!s.empty()) {
      int j; double t;
      tie(j, t) = s.top();
      if (q[j].at(t) > u.at(t)) break;
      s.pop();
    }
    if (s.empty()) {
      s.emplace(i, 0);
    } else {
      auto v = q[s.top().first];
      if (v.speed == u.speed) continue; // same quali
      double t = double(u.start - v.start) / double(v.speed - u.speed);
      s.emplace(i, t);
    }
    // cout << "T " << s.top().first << " " << s.top().second << endl;
  }
  return s;
}

double intersect(stack<pair<int, double>> s, vector<quali>& q, quali me) {
  while (!s.empty()) {
    int j; double t;
    tie(j, t) = s.top();
    if (q[j].at(t) > me.at(t)) break;
    s.pop();
  }
  if (s.empty()) return 0;
  auto v = q[s.top().first];
  double t = double(me.start - v.start) / double(v.speed - me.speed);
  return t;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll Y, N;
    cin >> Y >> N;
    vector<quali> R, L;
    vll pp(N), ss(N);
    for (ll i = 0; i < N; i++) cin >> pp[i];
    for (ll i = 0; i < N; i++) cin >> ss[i];
    for (ll i = 0; i < N; i++) {
      if (pp[i] > 0) {
        R.emplace_back(pp[i], ss[i]);
      } else {
        L.emplace_back(-pp[i], ss[i]);
      }
    }
    sort(R.begin(), R.end());
    sort(L.begin(), L.end());
    auto hr = get_hull(R);
    auto hl = get_hull(L);
    quali me(0, Y);
    // R -> L
    double t = intersect(hr, R, me);
    me.start = -t * 2 * Y;
    double best = max(t, intersect(hl, L, me));
    // L -> R
    me.start = 0;
    t = intersect(hl, L, me);
    me.start = - t * 2 * Y;
    best = min(best, max(t, intersect(hr, R, me)));
    cout << "Case #" << tc << ": "
    << fixed << setprecision(7) << best << endl;
  }
}
