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

struct bigint {
  static const ll BUCKET = 1000;
  static const int BUCKET_DIGITS = 3;
  vll buckets;
  bigint() {}
  bigint(ll a) {
    buckets.emplace_back(a);
    normalize();
  }
  bigint(const bigint& n) {
    buckets = n.buckets;
  }
  bigint(bigint&& n) : bigint() {
    swap(*this, n);
  }
  friend void swap(bigint& first, bigint& second) {
    swap(first.buckets, second.buckets);
  }
  bigint& operator = (ll a) {
    buckets.clear();
    buckets.emplace_back(a);
    normalize();
    return *this;
  }
  bigint& operator = (const bigint rhs) {
    bigint t(rhs);
    swap(*this, t);
    return *this;
  }
  void normalize() {
    size_t i = 0;
    while (i < buckets.size()) {
      ll t = buckets[i] / BUCKET;
      if (t) {
        if (i + 1 == buckets.size()) buckets.resize(i + 2);
        buckets[i + 1] += t;
        buckets[i] %= BUCKET;
      }
      i++;
    }
  }
  bigint& operator += (const bigint& rhs) {
    size_t n = rhs.buckets.size();
    if (n > buckets.size()) buckets.resize(n);
    for (size_t i = 0; i < min(buckets.size(), n); i++) {
      buckets[i] += rhs.buckets[i];
    }
    normalize();
    return *this;
  }
  size_t size() {
    if (buckets.empty()) return 0;
    size_t r = BUCKET_DIGITS * (buckets.size() - 1) + 1;
    ll b = buckets.back();
    while (b >= 10) {
      r++;
      b /= 10;
    }
    return r;
  }
  friend bigint operator + (bigint lhs, bigint &rhs) {
    lhs += rhs;
    return lhs;
  }
  friend ostream& operator << (ostream& s, bigint& n) {
    for (auto i = n.buckets.rbegin(); i != n.buckets.rend(); i++) {
      s << *i << setw(BUCKET_DIGITS) << setfill('0');
    }
    s << setw(0);
    return s;
  }
};



int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  vector<bigint> v;
  v.emplace_back(1);
  v.emplace_back(1);
  vi at(5001, 0);
  size_t i = 2;
  at[0] = 1;
  bigint a(1);
  bigint b(1);
  while (at[5000] == 0) {
    i++;
    auto t = b;
    b += a;
    a = t;
    int n = b.size();
    assert(n <= 5000);
    if (at[n] == 0) at[n] = i;
  }
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int n; cin >> n;
    cout << at[n] << endl;
  }
}
