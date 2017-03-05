#include <bits/stdc++.h>

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

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

vvl rmq_preprocess(vl A) {
  l n = A.size();
  vvl R(1, vl(n));
  for (l i = 0; i < n; i++) R[0][i] = i;
  for (l k = 1; 2 * k <= n; k = k << 1) {
    vl V;
    for (l i = 0; i + 2 * k <= n; i++) {
      if (A[R.back()[i]] < A[R.back()[i + k]]) {
        V.emplace_back(R.back()[i]);
      } else {
        V.emplace_back(R.back()[i + k]);
      }
    }
    R.emplace_back(V);
  }
  return R;
}

l rmq(l from, l to, vl& A, vvl& P) {
  l q = P.size() - 1;
  l k = (l)1 << q;
  while (k > (to - from)) { k = k >> 1; q--; }
  l i = P[q][from];
  l j = P[q][to - k];
  return (A[i] < A[j]) ? i : j;
}

struct RMQ {
  vl L, R, P, V;
  // Euler tour, heights of nodes in tour, where node with index appeared
  vl E, H, Q;
  l root, block_size, v_size, e_size;
  vl B, BI, T;
  vvl BP;
  unordered_map<l,l> M;
  RMQ(vl& A) {
    V = A;
    v_size = V.size();
    build_tree();
    Q.resize(V.size());
    tour(root, 0);
    e_size = E.size();
    blocks();
  }
  void build_tree() {
    L.resize(v_size, -1); R.resize(v_size, -1); P.resize(v_size, -1);
    stack<l> S;
    for (l i = 0; i < v_size; i++) {
      l j = -1;
      while ((not S.empty()) and (V[i] < V[S.top()])) {
        j = S.top(); S.pop();
      }
      if (j > -1) {
        L[i] = j;
        P[j] = i;
      }
      if (not S.empty()) {
        R[S.top()] = i;
        P[i] = S.top();
      }
      if (S.empty()) root = i;
      S.emplace(i);
    }
  }
  void tour(l i, l h) {
    Q[i] = E.size();
    E.emplace_back(i);
    H.emplace_back(h);
    if (L[i] != -1) { tour(L[i], h + 1); E.emplace_back(i); H.emplace_back(h); }
    if (R[i] != -1) { tour(R[i], h + 1); E.emplace_back(i); H.emplace_back(h); }
  }
  l hash(l from, l to, l type) { // [from, to]
    return from + block_size * (to + block_size * type);
  }
  void blocks() {
    block_size = 0;
    while (((l)1 << block_size) < e_size) block_size++;
    block_size >>= 1; if (block_size == 0) block_size = 1;
    // LOG << "block_size " << block_size << '\n';
    while (H.size() % block_size) H.emplace_back(H.back() + 1);
    l t = 0;
    while (t < e_size) {
      l type = 0;
      for (l i = t + 1; i < t + block_size; i++) {
        type <<= 1;
        if (H[i] < H[i - 1]) type++;
      }
      for (l i = t; i < t + block_size; i++) {
        l best = i;
        for (l j = i; j < t + block_size; j++) {
          if (H[j] < H[best]) best = j;
          M[hash(i - t, j - t, type)] = best - t;
        }
        if (i == t) {
          B.emplace_back(H[best]);
          BI.emplace_back(best);
          T.emplace_back(type);
        }
      }
      t += block_size;
    }
    BP = rmq_preprocess(B);
  }
  l query(l from, l to) { // [from, to)
    from = Q[from];
    to = Q[to - 1];
    if (from > to) swap(from, to);
    l fp = from / block_size;
    l tp = to / block_size;
    l b_from = fp;
    if (from % block_size) b_from++;
    l b_to = tp;
    if ((to + 1) % block_size == 0) b_to++;
    l best = -1;
    if (b_from < b_to) best = BI[rmq(b_from, b_to, B, BP)];
    if (from % block_size) {
      l type = T[fp];
      l i = from % block_size;
      l j = (fp == tp) ? (to % block_size) : (block_size - 1);
      l k = M[hash(i, j, type)] + fp * block_size;
      if ((best == -1) or (H[k] < H[best])) best = k;
    }
    if ((to + 1) % block_size) {
      l type = T[to / block_size];
      l i = (fp == tp) ? (from % block_size) : 0;
      l j = to % block_size;
      l k = M[hash(i, j, type)] + tp * block_size;
      if ((best == -1) or (H[k] < H[best])) best = k;
    }
    return E[best];
  }
};
l solve(l a, l b, vl& V, RMQ& R) {
  if (a >= b) return 0;
  l k = R.query(a, b);
  return - V[k] * (k - a + 1) * (b - k)
    + solve(a, k, V, R)
    + solve(k + 1, b, V, R);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, q;
  while (cin >> n >> q) {
    vl V;
    l x; cin >> x;
    for (l i = 0; i < n - 1; i++) {
      l y; cin >> y;
      V.emplace_back(-abs(x - y));
      x = y;
    }
    RMQ R(V);
    while (q--) {
      l a, b; cin >> a >> b; a--; b--;
      cout << solve(a, b, V, R) << '\n';
    }
  }
}
