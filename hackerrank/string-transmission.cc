#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

const l MOD = 1000000007;
const l MAX = 1001;
const l MAX_PRIME = 1000000;
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

vvl C(MAX, vl(MAX));

vl factorize_to_primes(vl& primes, l n) {
  vl factors;
  auto p = primes.begin();
  while (p != primes.end() && (*p) * (*p) <= n) {
    if (n % *p == 0) factors.emplace_back(*p);
    while (n % *p == 0) n /= *p;
    p++;
  }
  if (n != 1) factors.emplace_back(n);
  return factors;
}

l add(l a, l b) { return (a + b) % MOD; }
l sub(l a, l b) { return (a + MOD - b) % MOD; }

l solve(l n, l k, string s, vl& primes) {
  vl r(n);
  for (l i = 0; i < n; i++) r[i] = s[i] - '0';
  l sum = accumulate(r.begin(), r.end(), 0);
  l total = 0;
  // ways to apply k bit change
  for (l i = 0; i <= k; i++) total = add(total, C[i][n]);
  for (l p = 2; p <= n; p++) {
    if (n % p) continue;
    auto factors = factorize_to_primes(primes, p);
    l t = 1; for (auto f : factors) t *= f;
    if (t != p) continue;
    l a = n / p; // length of part
    l q = p; // number of parts
    vl v(a);
    for (l i = 0; i < n; i++) v[i % a] += r[i];
    // number of ways to get symmetric with exatly k changes
    vvl d(a + 1, vl(k + 1));
    d[0][0] = 1;
    for (l i = 1; i <= a; i++) { // lenght
      for (l j = 0; j <= k; j++) { // bits changed
        if (v[i - 1] == 0 || v[i - 1] == q) {
          // leave as is
          d[i][j] = add(d[i][j], d[i - 1][j]);
          // change completely
          if (j >= q) d[i][j] = add(d[i][j], d[i - 1][j - q]);
        } else {
          // change -> 0
          if (j - v[i - 1] >= 0)
            d[i][j] = add(d[i][j], d[i - 1][j - v[i - 1]]);
          // change -> 1
          if (j - q + v[i - 1] >= 0)
            d[i][j] = add(d[i][j],d[i - 1][j - q + v[i - 1]]);
        }
      }
    }
    l dd = 0;
    for (l i = 0; i <= k; i++) dd = add(dd, d[a][i]);
    if (factors.size() % 2) {
      total = sub(total, dd);
    } else {
      total = add(total, dd);
    }
  }
  return total;
}

l solve_brute(l n, l k, string s) {
  set<string> ss;
  ss.insert(s);
  for (l i = 0; i < k; i++) {
    set<string> ns;
    for (auto a : ss) {
      ns.insert(a);
      for (l j = 0; j < n; j++) {
        auto b = a;
        b[j] = (a[j] == '0' ? '1' : '0');
        ns.insert(b);
      }
    }
    swap(ns, ss);
  }
  l answer = 0;
  for (auto a : ss) {
    bool symmetric = false;
    for (l p = 1; p < n; p++) {
      if (n % p) continue;
      bool d = false;
      for (l i = p; i < n; i++) d = d || (a[i] != a[i - p]);
      if (!d) {
        symmetric = true;
        break;
      }
    }
    if (!symmetric) answer++;
  }
  return answer;
}

default_random_engine source(random_device{}());

l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b)(source);
}

bool random_bool() {
  return random_in_range(0, 1) == 1;
}

string random_string(int length) {
  string s = "";
  string an = "01";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size() - 1)];
  }
  return s;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  auto primes = sieve_primes();
  for (l i = 0; i < MAX; i++) {
    C[i][i] = 1;
    C[0][i] = 1;
  }
  for (l i = 1; i < MAX; i++) {
    for (l j = i + 1; j < MAX; j++) {
      C[i][j] = add(C[i - 1][j - 1], C[i][j - 1]);
    }
  }
  /*
  for (l i = 0; i < 100000; i++) {
    string s = random_string(12);
    l n = s.size();
    l k = random_in_range(0, n);
    l a = solve_brute(n, k, s);
    l b = solve(n, k, s, primes);
    if (a != b) {
      cerr << a << " != " << b << endl;
      cout << n << " " << k << endl;
      cout << s << endl;
      return 0;
    }
  }
  return 0;
*/
  l tcc; cin >> tcc;
  for (l tc = 0; tc < tcc; tc++) {
    l n, k; cin >> n >> k;
    string s; cin >> s;
    cout << solve(n, k, s, primes) << endl;
  }
}

