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

ll gcd(ll a, ll b) {
  while (b) {
    ll t = b;
    b = a % b;
    a = t;
  }
  return a;
}

ll lcm(ll a, ll b) {
  return a * b / gcd(a, b);
}

const int n = 13;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  double d = 0;
  for (int j = 1; j < n; j++) {
    vi v;
    for (int i = 0; i < j; i++) {
      v.emplace_back(i);
    }
    ll count = 0;
    ll up = 0;
    while (true) {
      bitset<n> b;
      for (auto i : v) {
        if (i == 0) {
          b.set(0);
          continue;
        }
        if (b[i - 1]) continue;
        b.set(i);
      }
      up += b.count();
      count++;
      if (!next_permutation(v.begin(), v.end())) break;
    }
    int g = gcd(count, up);
    count /= g; up /= g;
    cout << up << " / " << count << endl;
    double t = up; t /= count;
    printf("%.12f\n", (t - d - 0.5));
    d = t;
  }
  // looks like the lim of (t - d - 0.5) = 0.5-1/e => t - d ->1 - 1/e
}
