#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 1000001;

ll gcd(ll a, ll b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

ll lcm(ll a, ll b) {
  return a * b / gcd(a, b);
}

pair<ll, ll> get_time(ll x, ll h, ll y, ll m, ll a) {
  bitset<MAX> b;
  b.reset();
  ll t = 0;
  pair<ll, ll> r;
  r.first = 0;
  while (true) {
    h = (x * h + y) % m;
    t++;
    if (h == a && r.first == 0) {
      r.first = t;
    }
    if (b[h]) {
      if (r.first == 0) return r;
      if (h == a) {
        r.second = t - r.first;
        return r;
      }
    }
    b.set(h);
  }
}

ll X, Y, D;

void euclid(ll a, ll b) {
  if (b == 0) { X = 1; Y = 0; D = a; return; }
  euclid(b, a % b);
  ll t = Y;
  Y = X - (a / b) * Y;
  X = t;
}

ll solve(ll u1, ll p1, ll u2, ll p2) {
  ll a = p1;
  ll b = -p2;
  ll c = u2 - u1;
  D = gcd(a, b);
  if (c % D != 0) return -1;
  euclid(a, b);
  X *= c / D; Y *= c / D;
  ll from = -X * D / b;
  ll to = Y * D / a;
  if (from > to) swap(from, to);
  from--; to++;
  ll best = -1;
  for (int n = from; n <= to; n++) {
    ll x = X + b / D * n;
    ll y = Y - a / D * n;
    if (x < 0 || y < 0) continue;
    ll v = u1 + p1 * x;
    if (best == -1 || best > v) best = v;
  }
  return best;
}

int main() {
  ll m;
  while (cin >> m) {
    ll h, a, x ,y;
    cin >> h >> a >> x >> y;
    auto t1 = get_time(x, h, y, m, a);
    cin >> h >> a >> x >> y;
    auto t2 = get_time(x, h, y, m, a);
    if (t1.first == 0 || t2.first == 0) {
      cout << -1 << endl;
    } else {
      cout << solve(t1.first, t1.second, t2.first, t2.second) << endl;
    }
  }
}
