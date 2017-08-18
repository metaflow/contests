#if defined(LOCAL)
#define PROBLEM_NAME "c"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) debug(x)
#else
#define L(x, ...) (x)
#include <bits/stdc++.h>
#endif

using namespace std;
using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)

#if defined(LOCAL)
#define L(x...) debug(x)
#else
#define L(x, ...) (x)
#endif
struct node;
using pnode = shared_ptr<node>;
struct node {
  l value;
  l from, to; // [from, to) // TODO: remove
  pnode left, right;
  pnode min_node;
};

pnode inf;

void update_node_min(pnode p) {
  if (not p->left) return;
  if (p->left->min_node->value < p->right->min_node->value) {
    p->min_node = p->left->min_node;
  } else {
    p->min_node = p->right->min_node;
  }
}

pnode build_tree(l from, l to, vector<pnode>& v, l mod2) {
  if (to - from == 1) {
    if (from % 2 == mod2) {
      return v[from];
    } else {
      return inf;
    }
  }
  pnode p = make_shared<node>();
  l m = (from + to) / 2;
  p->left = build_tree(from, m, v, mod2);
  p->right = build_tree(m, to, v, mod2);
  update_node_min(p);
  return p;
}

pnode query_min(pnode p, l pfrom, l pto, l x) {
  if (x < pfrom or x >= pto) return inf;
  if (x == pfrom) return p->min_node;
  l m = (pfrom + pto) / 2;
  auto a = query_min(p->left, pfrom, m, x);
  auto b = query_min(p->right, m, pto, x);
  if (a->value < b->value) return a;
  return b;
}

pnode remove(pnode p, l from, l to, l at) {
  if (to - from == 1) return inf;
  l m = (from + to) / 2;
  if (at < m) {
    p->left = remove(p->left, from, m, at);
  } else {
    p->right = remove(p->right, m, to, at);
  }
  update_node_min(p);
  return p;
}

void swap_oddity(l from, l to, pnode odd, pnode even, l p) {
  if (to - from == 1 or p >= to) return;
  l m = (from + to) / 2;
  if (p < m) {
    swap(odd->right, even->right);
    swap_oddity(from, m, odd->left, even->left, p);
  } else {
    swap_oddity(m, to, odd->right, even->right, p);
  }
  update_node_min(odd);
  update_node_min(even);
}

vvl rmq_preprocess(vl& A) {
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

// range minimum query [from, to)
l rmq(l from, l to, vl& A, vvl& P) {
  l q = P.size() - 1;
  l k = (l)1 << q;
  while (k > (to - from)) { k = k >> 1; q--; }
  l i = P[q][from];
  l j = P[q][to - k];
  return (A[i] < A[j]) ? i : j;
}

// true if pick a
bool cmp(vl& a, l pa, vl&b, l pb) {
  if (pb >= b.size()) return true;
  if (pa >= a.size()) return false;
  return a[pa] < b[pb];
}

struct state {
  l from, to; bool inverse;
  l x, y; l value_x;
};

struct compare_state {
  bool operator() (const state& a, const state& b) {
    return a.value_x > b.value_x;
  }
};

state build(vl& odd, vvl& po, vl& even, vvl& pe, l from, l to, bool inverse) {
  state s;
  s.from = from;
  s.to = to;
  s.inverse = inverse;
  if (inverse) {
    s.x = rmq(from, to, odd, po);
    s.value_x = odd[s.x];
    s.y = rmq(s.x, to, even, pe);
  } else {
    s.x = rmq(from, to, even, pe);
    s.value_x = even[s.x];
    s.y = rmq(s.x, to, odd, po);
  }
  return s;
}

void solve(istream& cin, ostream& cout) {
  l n;
  while (cin >> n) {
    vl even(n, INF), odd(n, INF);
    vl v(n);
    F(i, 0, n) {
      cin >> v[i];
      if (i % 2) {
        odd[i] = v[i];
      } else {
        even[i] = v[i];
      }
    }
    auto pe = rmq_preprocess(even);
    auto po = rmq_preprocess(odd);
    priority_queue<state, vector<state>, compare_state> q;
    state root = build(odd, po, even, pe, 0, n, false);
    q.emplace(root);
    vl answer;
    while(not q.empty()) {
      state a = q.top(); q.pop();
      answer.emplace_back(v[a.x]);
      answer.emplace_back(v[a.y]);
      if (a.x - a.from > 1) {
        q.emplace(build(odd, po, even, pe, a.from, a.x, a.inverse));
      }
      if (a.y - a.x > 1) {
        q.emplace(build(odd, po, even, pe, a.x + 1, a.y, not a.inverse));
      }
      if (a.to - a.y > 1) {
        q.emplace(build(odd, po, even, pe, a.y + 1, a.to, a.inverse));
      }
    }
    F(i, 0, n) {
      if (i) cout << ' ';
      cout << answer[i];
    }
    cout << lf;
  }
}

    int main() {
      ios_base::sync_with_stdio(false); cin.tie(0);
      cout << fixed << setprecision(15);
#if defined(LOCAL)
      // _generate_random_test = generate_random;
      // _solve_brute = solve_brute;
      // _player_b = player_b;
      // _custom_solution_checker = solution_checker;
      maybe_run_tests(cin, cout);
#else
      solve(cin, cout);
#endif
    }
