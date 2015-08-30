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
using vvll = vector<vll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-6;

struct line {
  double x, s;
  ll id, pos;
};

struct event {
  ll a, b, query_no, query_pos;
  double t;
  ll type; // 0 - crossing, 1 - query
};

bool equal_double(double x, double y) {
  if (abs(x - y) < EPS) return true;
  // Is x or y too close to zero?
  if (abs(x) < EPS || abs(y) < EPS) return false;
  // Check relative precision.
  return (abs((x - y) / x) < EPS) && (abs((x - y) / y) < EPS);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll n; cin >> n;
    vector<line> v(n);
    for (ll i = 0; i < n; i++) {
      cin >> v[i].s >> v[i].x;
      v[i].id = i + 1;
    }
    sort(v.begin(), v.end(),
      [](const line& a, const line& b) {
        return a.x > b.x;
      });
    vi order(n);
    for (ll i = 0; i < n; i++) {
      v[i].pos = i;
    }
    sort(v.begin(), v.end(),
      [](const line& a, const line& b) {
        return a.s > b.s;
      });
    vector<event> events;
    for (ll i = 0; i < n; i++) order[v[i].pos] = i;
    for (ll i = 0; i < n; i++) {
      for (ll j = i + 1; j < n; j++) {
        auto &a = v[i];
        auto &b = v[j];
        if (equal_double(a.s, b.s)) continue;
        event e;
        e.type = 0;
        e.t = (a.x - b.x) / (b.s - a.s);
        e.a = i;
        e.b = j;
        events.emplace_back(e);
      }
    }
    ll m; cin >> m;
    vll answers(m);
    for (ll i = 0; i < m; i++) {
      event e;
      e.type = 1;
      e.query_no = i;
      cin >> e.t >> e.query_pos;
      e.query_pos--;
      events.emplace_back(e);
    }
    sort(events.begin(), events.end(),
      [&v] (const event& a, const event& b) {
        if (!equal_double(a.t, b.t)) return a.t < b.t;
        if (a.type != b.type) return a.type < b.type;
        if (a.type == 1) return a.query_no < b.query_no;
        if (!equal_double(v[a.a].s, v[b.a].s)) return v[a.a].s > v[b.a].s;
        return v[a.b].s > v[b.b].s;
      });
    for (auto e : events) {
      switch (e.type) {
        case 0:
          if (abs(v[e.a].pos - v[e.b].pos) != 1) continue;
          // assert();
          swap(order[v[e.a].pos], order[v[e.b].pos]);
          swap(v[e.a].pos, v[e.b].pos);
          // cerr << "X " << e.t << " " << v[e.a].id << " " << v[e.b].id << " ";
          // cerr << v[e.a].pos << endl;
          break;
        case 1:
          ll k = e.query_pos;
          double y = v[order[k]].s * e.t + v[order[k]].x;
          while (k > 0 &&
            equal_double(y, v[order[k - 1]].s * e.t + v[order[k - 1]].x)) k--;
          vll eq_range;
          ll start = k;
          while (k < n &&
            equal_double(v[order[k]].s * e.t + v[order[k]].x, y)) {
            eq_range.emplace_back(v[order[k]].id);
            k++;
          }
          sort(eq_range.begin(), eq_range.end());
          // for (auto i : eq_range) cerr << i << " ";
          // cerr << endl;
          answers[e.query_no] = eq_range[e.query_pos - start];
          // cerr << "? " << e.t << " " << e.query_no << endl;
          break;
      }
    }
    for (auto a : answers) cout << a << endl;
  }
}
