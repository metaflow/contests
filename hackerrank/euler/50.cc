#include<bits/stdc++.h>
#include <chrono>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

const l MAX_PRIME = 6000000;
vl sieve_primes() {
  bitset<MAX_PRIME + 1> b;
  vl primes;
  primes.emplace_back(2);
  for (l i = 3; i <= MAX_PRIME; i += 2) {
    if (b[i]) continue;
    primes.emplace_back(i);
    for (l j = i * i; j <= MAX_PRIME; j += i) b.set(j);
  }
  return primes;
}

bool is_prime(vl& primes, l n) {
  auto p = primes.begin();
  while (p != primes.end() && (*p) * (*p) <= n) {
    if (n % *p == 0) return (n == *p);
    p++;
  }
  return true;
}

ll solve(l n, vl& primes, vl& sum) {
  vl seq;
  l best = 0;
  l best_x = 0;
  l right = 0;
  l size = sum.size();
  for (l left = 0; left < size; left++) {
    while (sum[right] - sum[left] < n) right++;
    if (right - left <= best) break;
    while (sum[right] - sum[left] > n || (right > 1 && (sum[right] - sum[left]) % 2 == 0)) right--;
    while (true) {
      assert(right > left);
      if (right - left <= best) break;
      if (is_prime(primes, sum[right] - sum[left])) {
        if (right - left > best) {
          best = right - left;
          best_x = sum[right] - sum[left];
        }
        break;
      }
      if (right > 2) { right -= 2; } else { right--; }
    }
  }
  return make_pair(best_x, best);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  vl primes = sieve_primes();
  vl sum(primes.size() + 1);
  for (size_t i = 1; i < sum.size(); i++) sum[i] = sum[i - 1] + primes[i - 1];
  l T; cin >> T;
  while (T--) {
    l n; cin >> n;
    auto s = solve(n, primes, sum);
    cout << s.first << " " << s.second << endl;
  }
}
