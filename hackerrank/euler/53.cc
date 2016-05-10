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

l gcd(l a, l b) {
  while (b) {
    l t = b;
    b = a % b;
    a = t;
  }
  return a;
}

l lcm(l a, l b) {
  return a * b / gcd(a, b);
}

// -> a * m / d
l mult_div(l a, l m, l d) {
  l a_ = a, m_ = m, d_ = d;
  l t = gcd(a, d);
  d /= t;
  a /= t;
  t = gcd(m, d);
  m /= t;
  if (a > std::numeric_limits<l>::max() / m) return 0;
  return m * a;
}

l count_for(l N, l K) {
  l from = 0;
  l v = 1; // (n 0)
  while (from < N) {
    l t = v;
    v = mult_div(v, N - from, from + 1);
    if (v > K || v < t) break;
    from++;
  }
  v = 1; // (n n)
  l to = N;
  while (to > 0) {
    l t = v;
    v = mult_div(v, to, N - to + 1);
    if (v > K || v < t) break;
    to--;
  }
  return max(0ll, to - from - 1);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l N, K;
  while (cin >> N >> K) {
    l answer = 0;
    for (l i = 1; i <= N; i++) answer += count_for(i, K);
    cout << answer << endl;
  }
}
