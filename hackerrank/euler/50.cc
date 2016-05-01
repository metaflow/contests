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

chrono::high_resolution_clock::duration prime_time;

l get_seq_at(vl& seq, size_t at, l n, vl& primes) {
  auto t1 = chrono::high_resolution_clock::now();
  while (seq.size() <= at) {
    l x = seq.empty() ? n : seq.back() - 1;
    if (x % 2 == 0 && x != 2) x--;
    while (!is_prime(primes, x)) x -= 2;
    assert(x > 1);
    seq.push_back(x);
  }
  prime_time += chrono::high_resolution_clock::now() - t1;
  return seq[at];
}

ll solve(l n, vl& primes, vl& sum) {
  vl seq;
  l best = 0;
  l best_x = 0;
  l right = 0;
  l size = sum.size();
  size_t best_i = 0;
  for (l left = 0; left < size; left++) {
    // cerr << left << endl;
    size_t i = 0;
    l x = get_seq_at(seq, i, n, primes);
    while (sum[right] - sum[left] < x) right++;
    if (right - left <= best) break;
    while (true) {
      while (sum[right] - sum[left] > x) right--;
      assert(right > left);
      if (right - left <= best) break;
      if (sum[right] - sum[left] == x) {
        if (right - left > best) {
          best = right - left;
          best_x = x;
          best_i = i;
        }
        break;
      }
      i++;
      x = get_seq_at(seq, i, n, primes);
    }
  }
  cout << "best i " << best_i << endl;
  // cout << seq.size() << endl;
  return make_pair(best_x, best);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  vl primes = sieve_primes();
  vl sum(primes.size() + 1);
  for (size_t i = 1; i < sum.size(); i++) sum[i] = sum[i - 1] + primes[i - 1];
  l T; cin >> T;
  while (T--) {
    cout << "---" << endl;
    prime_time = chrono::high_resolution_clock::duration::zero();
    l n; cin >> n;
    auto t1 = chrono::high_resolution_clock::now();
    auto s = solve(n, primes, sum);
    auto t2 = chrono::high_resolution_clock::now();
    cout << "total " << chrono::duration_cast<chrono::microseconds>(t2 - t1).count() << endl;
    cout << "prime " << chrono::duration_cast<chrono::microseconds>(prime_time).count() << endl;
    cout << s.first << " " << s.second << endl;
    cout << (n - s.first) << endl;
  }
}
