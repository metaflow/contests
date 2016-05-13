#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

const l BOUND = e9 * e6;
const ll ZERO = {0, 0};

ll to_ll(l a) {
  return make_pair(0, a);
}

ll add(ll a, ll b) {
  l x = a.second + b.second;
  l y = a.first + b.first + x / BOUND;
  return make_pair(y, x % BOUND);
}

l shr(ll& a) {
  l result = a.second % 10;
  a.second = (a.second / 10 + (a.first % 10) * (BOUND / 10));
  a.first /= 10;
  return result;
}

l shl(ll& a) {
  a.first *= 10;
  a.second *= 10;
  l result = a.first / BOUND;
  a.first = (a.first % BOUND) + a.second / BOUND;
  a.second = a.second % BOUND;
  return result;
}

ll reverse(ll a) {
  ll result = {0, 0};
  while (a != ZERO) {
    shl(result);
    result.second += shr(a);
  }
  return result;
}

void output(ostream& os, ll a) {
  if (a.first) {
    os << a.first << setw(15) << setfill('0') << a.second;
  } else {
    os << a.second;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    vector<ll> to(n + 1);
    for (l i = n; i >= 1; i--) {
      auto a = to_ll(i);
      for (l j = 0; j < 60; j++) {
        auto b = reverse(a);
        if (a == b) {
          to[i] = a;
          break;
        }
        a = add(a, b);
        if (a.first == 0 && a.second <= n) {
          to[i] = to[a.second];
        }
      }
    }
    map<ll, l> counts;
    ll best = ZERO;
    l best_count = 0;
    for (l i = 1; i <= n; i++) {
      if (to[i] != ZERO) {
        counts[to[i]]++;
        if (counts[to[i]] > best_count) {
          best_count = counts[to[i]];
          best = to[i];
        }
      }
    }
    output(cout, best);
    cout << " " << best_count << endl;
  }
}
