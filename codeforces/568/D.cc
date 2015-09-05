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
const double EPS = 1e-10;

struct point {
  ii x, y;
  friend ostream& operator << (ostream& o, point p) {
    return o << "( " << p.x.first << "/" << p.x.second << ", "
             << p.y.first << "/" << p.y.second << " )";
  }
};

struct road {
  ll id, A, B, C;
  // whether rational point (x, y) is at road
  bool contains(const point q) const {
    return A * q.x.first * q.y.second +
           B * q.y.first * q.x.second +
           C * q.x.second * q.y.second == 0;
  }

  bool intersects(const road& rhs) {
    return (A * rhs.B != rhs.A * B);
  }
  bool operator < (const road& rhs) {
    return (A * rhs.B < rhs.A * B);
  }
};

point cross(const road& L, const road& R) {
    if (R.B == 0) return cross(R, L);
    point q;
    if (L.B == 0) {
      q.x.first = -L.C;
      q.x.second = L.A;
    } else {
      q.x.first = L.B * R.C - L.C * R.B;
      q.x.second = L.A * R.B - L.B * R.A;
    }
    q.y.first = -R.A * q.x.first - R.C * q.x.second;
    q.y.second = R.B * q.x.second;
    return q;
  }

default_random_engine source(random_device{}());

ll random_in_range(ll a, ll b) {
  return uniform_int_distribution<ll>(a, b)(source);
}

bool random_bool() {
  return random_in_range(0, 1) == 1;
}

string random_string(int length) {
  string s = "";
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size() - 1)];
  }
  return s;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n, m;
  while (cin >> n >> m) {
    // cerr << "------" << endl;
    vector<road> v(n);
    for (ll i = 0; i < n; i++) {
      cin >> v[i].A >> v[i].B >> v[i].C;
      v[i].id = i + 1;
    }
    sort(v.begin(), v.end());
    vii answer;
    for (ll trial = 0; trial < 250; trial++) {
      // assert(answer.empty());
      ll e = n;
      ll k = m;
      while (k > 0 && e > 0) {
        if (k >= e) {
          for (ll i = 0; i < e; i++) {
            answer.emplace_back(v[i].id, -1);
          }
          e = 0;
          break;
        }
        bool found = false;
        point q;
        for (ll i = 0; i < e; i++) {
          auto &a = v[random_in_range(0, e - 1)];
          auto bi = upper_bound(v.begin(), v.begin() + e, a);
          ll bf = bi - v.begin();
          if (bf >= e) continue;
          swap(v[0], v[random_in_range(0, e - 1)]);
          swap(v[1], v[random_in_range(1, e - 1)]);
          if (!v[0].intersects(v[1])) continue;
          q = cross(v[0], v[1]);
          answer.emplace_back(v[0].id, v[1].id);
          found = true;
          break;
        }
        if (!found) break;
        ll i = 0;
        while (i < e) {
          if (v[i].contains(q)) {
            swap(v[i], v[e - 1]);
            e--;
          } else {
            i++;
          }
        }
        k--;
      }
      if (e == 0) break;
      answer.clear();
    }
    if (answer.empty()) {
      cout << "NO" << endl;
    } else {
      cout << "YES" << endl;
      cout << answer.size() << endl;
      for (auto a : answer) {
        cout << a.first << " " << a.second << endl;
      }
    }
  }
}
