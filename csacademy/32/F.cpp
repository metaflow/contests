#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "F"
const double _max_double_error = 1e-9;
#include "testutils.h"
#endif
#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
bool local = true;
#define L(x...) debug(x)
#else
bool local = false;
#define L(x, ...) (x)
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(local) ? (void) 0 : VoidStream() & cerr

struct BIT {
  vi tree;
  l max_p;
  BIT(size_t n) {
    max_p = n;
    tree.resize(n + 1);
  };
  void reset(size_t n) {
    max_p = n;
    tree.clear();
    tree.resize(n + 1);
 }
  // sum of [1, p], O(log(max))
  l get(l p) {
    l sum = 0;
    while (p) {
      sum += tree[p];
      p -= (p & -p);
    }
    return sum;
  }
  l at(l p) {
    return get(p) - get(p - 1);
  }
  // O(log(max))
  void add(l p, l value) {
    while (p <= max_p) {
      tree[p] += value;
      p += (p & -p);
    }
  }
  // find lowest index with given sum, -1 if not found O(log(max))
  l find(l sum) {
    l mask = max_p;
    while (true) {
      l lower = (mask & -mask);
      if (lower == mask) break;
      mask -= lower;
    }
    l p = 0;
    l top = -1;
    while (mask != 0) {
      l m = p + mask;
      if (m <= max_p) {
        if (sum == tree[m]) top = m;
        if (sum > tree[m]) {
          p = m;
          sum -= tree[m];
        }
      }
      mask >>= 1;
    }
    if (sum != 0) return top;
    return p;
  }
};


struct RandGen {
  int x, y, z;

  int nextInt() {
    int t = x ^ (x << 11);
    x = y;
    y = z;
    z ^= (z >> 19) ^ t ^ (t >> 8);
    return z;
  }

  int random(int N) {
    return nextInt() % N;
  }
};

const l MAX = 50 * e6;
bitset<MAX> bits;
const l B = e6;
BIT bt(B);

void init(int N, int M) {
  bits.reset();
  M++; N++;
}

int addr(int p) {
  return p / 50 + 1;
}

void flipPosition(int p) {
  bool v = bits[p];
  bt.add(addr(p), v ? -1 : +1);
  bits[p] = not v;
}

int getCount(int st, int fn) {
  int r = 0;
  l ps = addr(st), pf = addr(fn);
  l a = ps;
  l b = pf - 1;
  if (b > a) {
    r += bt.get(b) - bt.get(a);
    l i = st;
    while (addr(i) == ps) {
      if (bits[i]) r++;
      i++;
    }
    i = fn;
    while (addr(i) == pf) {
      if (bits[i]) r++;
      i--;
    }
  } else {
    F(i, st, fn + 1) if (bits[i]) r++;
  }
  return r;
}

void solve(istream& cin, ostream& cout) {
  int N, M;
  RandGen rng;
  cin >> N >> M >> rng.x >> rng.y >> rng.z;

  init(N, M);

  long long hashSol = 0;

  for (long long i = 0; i < M; i++) {
    if (rng.random(2) == 0) {
      const int poz = rng.random(N);
      flipPosition(poz);
    }
    else {
      int st = rng.random(N), fn = rng.random(N);
      if (st > fn) {
        swap(st, fn);
      }

      hashSol ^= i * getCount(st, fn);
    }
  }

  cout << hashSol << "\n";
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
