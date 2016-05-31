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


// v max flow
struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  int age;
  vector<pedge> adjusted;
  vector<pedge> back;
};

struct edge {
  pnode from, to;
  l flow;
  pedge opposite;
};

int adjust(pedge e, l d) {
  if (!e) return d;
  l sum = 0;
  if (e->from->back.empty()) sum = d;
  for (auto o : e->from->back) {
    if (o->flow == 0) continue;
    sum += adjust(o, min(o->flow, d - sum));
    if (sum == d) break;
  }
  e->flow -= sum;
  e->opposite->flow += sum;
  return sum;
}

void connect(pnode &a, pnode &b, int w) {
  pedge ea = make_shared<edge>();
  pedge eb = make_shared<edge>();
  ea->from = a; ea->to = b; ea->flow = w; ea->opposite = eb;
  eb->from = b; eb->to = a; eb->flow = 0; eb->opposite = ea;
  a->adjusted.emplace_back(ea);
  b->adjusted.emplace_back(eb);
}

int max_flow(vector<pnode> &g, pnode &source, pnode &sink) {
  int result = 0;
  while (true) {
    for (auto u : g) {
      u->age = 0;
      u->back.clear();
    }
    queue<pnode> q;
    q.push(source); source->age = 1;
    while (!q.empty()) {
      auto u = q.front(); q.pop();
      if (u == sink) break;
      for (auto e : u->adjusted) {
        if (e->flow == 0) continue;
        auto v = e->to;
        if (v->age == 0) {
          v->age = u->age + 1;
          q.push(v);
          v->back.emplace_back(e);
        } else if (v->age == u->age + 1) {
          v->back.emplace_back(e);
        }
      }
    }
    if (sink->age == 0) break;
    for (auto o : sink->back) {
      // if (o->from->age != sink->age - 1 || o->flow == 0) continue;
      result += adjust(o, o->flow);
    }
  }
  return result;
}
// ^ max flow

l index_of(l x, map<l, l>& indexes) {
  if (!indexes.count(x)) {
    l v = indexes.size();
    indexes[x] = v;
  }
  return indexes[x];
}

l solve(vl& left, vl& right) {
  pnode source = make_shared<node>();
  pnode sink = make_shared<node>();
  auto primes = sieve_primes();
  vector<pnode> factors, g;
  map<l, l> prime_indexes;
  for (auto x : left) {
    g.emplace_back(make_shared<node>());
    connect(source, g.back(), 1);
    auto fs = factorize_to_primes(primes, x);
    for (auto k : fs) {
      l j = index_of(k, prime_indexes);
      while (factors.size() <= j) factors.emplace_back(make_shared<node>());
      connect(g.back(), factors[j], 1);
    }
  }
  for (auto x : right) {
    g.emplace_back(make_shared<node>());
    connect(g.back(), sink, 1);
    auto fs = factorize_to_primes(primes, x);
    for (auto k : fs) {
      l j = index_of(k, prime_indexes);
      while (factors.size() <= j) factors.emplace_back(make_shared<node>());
      connect(factors[j], g.back(), 1);
    }
  }
  g.insert(g.end(), factors.begin(), factors.end());
  g.emplace_back(source);
  g.emplace_back(sink);
  return max_flow(g, source, sink);
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
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size() - 1)];
  }
  return s;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  // l n = 10000;
  // vl a(n), b(n);
  // for (l i = 0; i < n; i++) a[i] = random_in_range(2, e9);
  // for (l i = 0; i < n; i++) b[i] = random_in_range(2, e9);
  l n; cin >> n;
  vl a; for (l i = 0; i < n; i++) { l x; cin >> x; a.emplace_back(x); }
  vl b; for (l i = 0; i < n; i++) { l x; cin >> x; b.emplace_back(x); }
  cout << solve(a, b) << endl;
}
