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

struct bigint {
  static const l BUCKET = 1000;
  static const int BUCKET_DIGITS = 3;
  vl buckets;
  // constructors
  bigint() {}
  bigint(l a) {
    buckets.emplace_back(a);
    normalize();
  }
  bigint(const bigint& n) { buckets = n.buckets; }
  bigint(bigint&& n) : bigint() { swap(*this, n); }
  friend void swap(bigint& first, bigint& second) {
    swap(first.buckets, second.buckets);
  }
  // assignment
  bigint& operator = (l a) {
    buckets.clear();
    buckets.emplace_back(a);
    normalize();
    return *this;
  }
  bigint& operator = (bigint rhs) {
    swap(*this, rhs);
    return *this;
  }
  // utility
  void normalize() {
    size_t i = 0;
    while (i < buckets.size()) {
      l t = buckets[i] / BUCKET;
      if (t) {
        if (i + 1 == buckets.size()) buckets.resize(i + 2);
        buckets[i + 1] += t;
        buckets[i] %= BUCKET;
      }
      i++;
    }
  }
  size_t size() {
    if (buckets.empty()) return 0;
    size_t r = BUCKET_DIGITS * (buckets.size() - 1) + 1;
    l b = buckets.back();
    while (b >= 10) {
      r++;
      b /= 10;
    }
    return r;
  }
  friend ostream& operator << (ostream& s, bigint& n) {
    for (auto i = n.buckets.rbegin(); i != n.buckets.rend(); i++) {
      s << *i << setw(BUCKET_DIGITS) << setfill('0');
    }
    s << setw(0);
    return s;
  }
  // +
  friend bigint operator + (bigint lhs, const bigint &rhs) {
    lhs += rhs;
    return lhs;
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
  bigint& operator += (const l n) {
    buckets[0] += n;
    normalize();
    return *this;
  }
  friend bigint operator + (bigint lhs, const l &rhs) {
    lhs += rhs;
    return lhs;
  }
  // *
  bigint& operator *= (const l n) {
    for (size_t i = 0; i < buckets.size(); i++) {
      buckets[i] *= n;
    }
    normalize();
    return *this;
  }
  friend bigint operator * (bigint lhs, const l &rhs) {
    lhs *= rhs;
    return lhs;
  }
  bigint& operator *= (const bigint& b) {
    bigint a;
    bigint m(*this);
    for (int i = 0; i < b.buckets.size(); i++) {
      a += (m * b.buckets[i]);
      a.normalize();
      m.buckets.insert(m.buckets.begin(), 0); // * 10
    }
    swap(a, *this);
    return *this;
  }
  size_t digits() {
    size_t result = (buckets.size() - 1) * BUCKET_DIGITS;
    l t = buckets.back();
    while (t) {
      result++;
      t /= 10;
    }
    return result;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  bigint nominator(1);
  bigint denominator(2);
  vl v;
  for (l i = 1; i <= 10000; i++) {
    nominator += denominator;
    if (nominator.digits() != denominator.digits()) v.emplace_back(i);
    nominator += denominator;
    swap(nominator, denominator);
  }
  l n;
  while (cin >> n) {
    for (auto i : v) {
      if (i > n) break;
      cout << i << endl;
    }
  }
}
