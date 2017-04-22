#include <bits/stdc++.h>
// #define ONLINE_JUDGE
#if !defined ONLINE_JUDGE
#include "prettyprint.h"
#endif

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

default_random_engine source(chrono::system_clock::now().time_since_epoch().count());

// [a, b)
l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b - 1)(source);
}

bool random_bool() {
  return random_in_range(0, 2) == 1;
}

string random_string(int length) {
  string s = "";
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size())];
  }
  return s;
}

ll debufs_brute(l hd, l ad, l hk, l ak, l b, l d, l h, l target) {
  l c = 0;
  h = hd;
  bool f = true;
  while (target) {
    if (h <= ak - d) {
      if (not f) return make_pair(0, INF);
      h = hd;
      f = false;
    } else {
      ak = max(l(0), ak - d);
      target--;
      f = true;
    }
    c++;
    h -= ak;
  }
  return make_pair(h, c);
}

ll debufs(l hd, l ad, l hk, l ak, l b, l d, l h, l target) {
  LOG << 'd';
  l c = 0;
  h = hd;
  bool f = true;
  while (target and ak) {
    if (h <= ak - d) {
      if (not f) return make_pair(0, INF);
      h = hd - ak;
      c++;
      f = false;
    }
    l x = min(target, (h + ak - 1) / ak - 2);
    if (x > 0 and ak - d * x >= 0) {
      h -= (ak - d + ak - d * x) * x / 2;
      c += x;
      target -= x;
      ak -= d * x;
      f = true;
    }
    while (target and (h > ak - d)) {
      c++;
      ak = max(l(0), ak - d);
      target--;
      h -= ak;
      f = true;
    }
  }
  return make_pair(h, c);
}

ll buffs_brute(l hd, l ad, l hk, l ak, l b, l d, l h, l target) {
  l c = 0;
  bool f = true;
  while (target) {
    if (h > ak) {
      target--;
      f = true;
    } else {
      if (not f) return make_pair(0, INF);
      h = hd;
      f = false;
    }
    h -= ak;
    c++;
  }
  return make_pair(h, c);
}

ll buffs(l hd, l ad, l hk, l ak, l b, l d, l h, l target){
  LOG << 'b';
  if (ak == 0) return make_pair(h, target);
  l c = 0;
  l x = (h + ak - 1) / ak - 1; x = min(max(l(0),x), target);
  h -= ak * x;
  assert(h > 0 and (target == x or h <= ak));
  target -= x;
  c += x;
  if (target) {
    x = (hd + ak - 1) / ak - 2;
    if (x <= 0) return make_pair(0, INF);
    assert(x);
    l v = target / x;
    if (v) {
      target -= x * v;
      c += v * (x + 1);
      h = hd - ak * (x + 1);
      assert(h > 0 and h <= ak);
    }
    if (target) {
      c += target + 1;
      h = hd - ak * (target + 1);
      assert(h > 0);
    }
  }
  return make_pair(h, c);
}

l attacks_brute(l hd, l ad, l hk, l ak, l b, l d, l h, l target) {
  l c = 0;
  bool attacked = true;
  while (1) {
    if (hk <= ad) {
      c++;
      return c;
    }
    if (h > ak) {
      hk -= ad;
      attacked = true;
    } else {
      if (not attacked) return INF;
      h = hd;
      attacked = false;
    }
    h -= ak;
    c++;
  }
  return c;
}

l attacks(l hd, l ad, l hk, l ak, l b, l d, l h, l target) {
  LOG << 'a';
  assert(ad);
  l x = (hk + ad - 1) / ad;
  if (ak == 0) return x;
  l y = (h + ak - 1) / ak;
  if (x <= y) return x;
  auto e = buffs(hd, ak, hk, ak, b, d, h, (hk + ad - 1) / ad);
  l t = e.second;
  if (t == INF) return INF;
  if (e.first == hd - ak * 2) t--;
  return t;
}

l solve_brute(l hd, l ad, l hk, l ak, l b, l d, l h, l target) {
  l max_buffs = b == 0 ? 0 : max(0LL, ((hk - ad + b - 1) / b));
  l max_debufs = d == 0 ? 0 : max(0LL, ((ak + d - 1) / d));
  l best = INF;
  F(i, 0, max_debufs + 1) {
    // LOG << i << ' ';
    auto db = debufs_brute(hd, ak, hk, ak, b, d, hd, i);
    if (db.second == INF) continue;
    l ak_ = max(l(0), ak - i * d);
    F(j, 0, max_buffs + 1) {
      auto bf = buffs_brute(hd, ad, hk, ak_, b, d, db.first, j);
      if (bf.second == INF) continue;
      l r = attacks_brute(hd, ad + b * j, hk, ak_, b, d, bf.first, 0);
      best = min(best, r + bf.second + db.second);
    }
  }
  return best;
}

l divup(l a, l b) { assert(b); return (a + b - 1) / b; }
l divd(l a, l b) { assert(b); return a / b; }

ll ternary_search_min(l from, l to, function<l(l)> f) {
  l L = from, R = to;
  l rl = f(L), rr = f(R);
  while (1) {
    if (R - L < 2) {
      if (rl < rr) return make_pair(L, rl);
      return make_pair(R, rr);
    }
    if (R - L == 2) {
      l t = f(L + 1);
      if (t < rl) {
        if (t < rr) return make_pair(L + 1, t);
        return make_pair(R, rr);
      } else {
        if (rl < rr) return make_pair(L, rl);
        return make_pair(R, rr);
      }
    }
    l m1 = L + (R - L) / 3;
    l m2 = L + 2 * (R - L) / 3;
    vl v = {rl, f(m1), f(m2), rr};
    l x = 0;
    F(i, 1, 4) if (v[i] < v[x]) x = i;
    if (x < 2) { R = m2; rr = v[2]; }
    else { L = m1; rl = v[1]; }
  }
  assert(false);
  return make_pair(0, 0);
}

l solve_debuffed(l hd, l ad, l hk, l ak, l b, l d, l h, l target) {
  auto db = debufs(hd, ad, hk, ak, b, d, hd, target);
  if (db.second == INF) return INF;
  h = db.first;
  ak = max(0LL, ak - target * d);
  l max_buffs = (b == 0) ? 0 : max(0LL, divup(hk - ad, b));
  l best = INF;
  l r = INF;
  F(j, 0, min(max_buffs + 1, 4LL)) {
    auto bf = buffs(hd, ad, hk, ak, b, d, h, j);
    if (bf.second == INF) continue;
    r = attacks(hd, ad + b * j, hk, ak, b, d, bf.first, 0);
    best = min(best, r + bf.second + db.second);
  }
  if (r != INF and max_buffs > 3) {
    auto f = [&](l j) {
      auto bf = buffs(hd, ad, hk, ak, b, d, h, j);
      assert(bf.second != INF);
      return bf.second + attacks(hd, ad + b * j, hk, ak, b, d, bf.first, 0);
    };
    auto tt = ternary_search_min(4, max_buffs, f);
    best = min(best, db.second + tt.second);
  }
  return best;
}

l solve(l hd, l ad, l hk, l ak, l b, l d, l h, l target) {
  l best = INF;
  if (d) {
    l min_cycle = divup(hd, ak);
    l max_cycle = divup(hd, ak - (divup(ak, d) - 1) * d);
    l r = INF;
    F(i, 0, 4) {
      r = solve_debuffed(hd, ad, hk, ak, b, d, hd, i);
      best = min(best, r);
    }
    if (r != INF) {
      while (divup((ak - divup(hd, min_cycle)), d) < 4
             and min_cycle <= max_cycle) min_cycle++;
      if (min_cycle <= max_cycle) {
        auto f = [&](l c) {
          l i = divup((ak - divup(hd, c)), d);
          l x = solve_debuffed(hd, ad, hk, ak, b, d, hd, i);
          if (x == INF) {
            LOG << endl;
            LOG << i << endl;
            LOG << min_cycle << ".." << max_cycle << endl;
            LOG << "hd " << hd << " ad " << ad << " hk " << hk << " ak " << ak << " d " << d << " b " << b << " target " << target << endl;
            assert(x != INF);
          }
          return x;
        };
        auto tt = ternary_search_min(min_cycle, max_cycle, f);
        best = min(best, tt.second);
      }
    }
    best = min(best, solve_debuffed(hd, ad, hk, ak, b, d, hd, divup(ak, d)));
  } else {
    return solve_debuffed(hd, ad, hk, ak, b, d, hd, 0);
  }
  return best;
}

ll actions_brute(l hd, l ad, l hk, l ak, l b, l d, l h, l target) {
  bool acted = true;
  l turns = 0;
  while (target) {
    if (h > ak) {
      acted = true;
      target--;
    } else {
      if (not acted) return make_pair(0, INF);
      acted = false;
      h = hd;
    }
    h -= ak;
    turns++;
  }
  return make_pair(h, turns);
}

ll actions(l hd, l ad, l hk, l ak, l b, l d, l h, l target) {
  // LOG << "a hd " << hd << " ad " << ad << " hk " << hk << " ak " << ak << " d " << d << " b " << b << " h " << h << " target " << target << endl;
  l turns = 0;
  if (ak == 0 or target == 0) return make_pair(h, target);
  // consume initial health
  l s = divup(h, ak) - 1;
  l i = max(0LL, min(target, s));
  target -= i;
  turns += i;
  h -= i * ak;
  // consume from lowest health
  if (target) {
    s = divup(hd, ak) - 2;
    if (s <= 0) return make_pair(0, INF);
    l j = target / s;
    if (j) {
      turns += j * (s + 1);
      target -= s * j;
      h = hd - ak * (s + 1);
    }
    if (target) {
      turns += target + 1;
      h = hd - ak * (target + 1);
    }
  }
  return make_pair(h, turns);
}

l solve2(l hd, l ad, l hk, l ak, l b, l d, l h, l target) {
  // LOG << "------------------------" << endl;
  l turns_to_kill = divup(hk, ad);
  if (b) {
    turns_to_kill = ternary_search_min(0, max(0LL, divup(hk - ad, b)),
                                       [&] (l x) {
                                         return x + divup(hk, ad + x * b);
                                       }).second;
  }
  // LOG << "ttk = " << turns_to_kill << endl;
  l best = INF;
  l debuffs_applied = 0;
  l turns = 0;
  h = hd;
  l ak_ = ak;
  while (1) {
    LOG << "ak_ " << ak_ << ' ' << h << endl;
    l s = (ak_ == 0) ? INF : divup(h, ak_);
    if (s >= turns_to_kill) {
      best = min(best, turns_to_kill + turns);
    } else {
      ll e = actions(hd, ad, hk, ak_, b, d, h, turns_to_kill);
      best = min(best, e.second + turns);
    }
    if (ak_ == 0 or d == 0) break;
    l x = divd((ak - divup(hd, s)), d) - debuffs_applied; // max to keep same s
    if (x < 0) x = 0;
    ll next = actions(hd, ad, hk, ak_, b, d, h, x);
    if (next.second == INF) { break; }
    h = next.first;
    turns += next.second;
    // LOG << debuffs_applied;
    debuffs_applied += x + 1;
    // LOG << ' ' << debuffs_applied << endl;
    ak_ = max(0LL, ak - debuffs_applied * d);
    LOG << "2: ak_ " << ak_ << ' ' << h << endl;
    if (h > ak_) {
      h -= ak_;
      turns++;
    } else {
      auto e = actions(hd, ad, hk, ak_ + d, b, d, h, 1);
      if (e.second == INF) break;
      turns += e.second;
      h = e.first;
    }
  }
  return best;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  if (1) {
    F(tc, 0, 10000)
      F(i, 2, 100) {
      l hd = random_in_range(1, i);
      l ad = random_in_range(1, i);
      l hk = random_in_range(1, i);
      l d = random_in_range(0, i);
      l b = random_in_range(0, i);
      l ak = random_in_range(1, i);
      l h = random_in_range(1, hd + 1);
      l target = random_in_range(0, i);
      // hd = 8; d = 4; ak = 3; h = 6; target = 8;
      auto d1 = solve_brute(hd, ad, hk, ak, b, d, h, target);
      auto d2 = solve2(hd, ad, hk, ak, b, d, h, target);
      if (d1 == d2) continue;
      LOG << "hd " << hd << " ad " << ad << " hk " << hk << " ak " << ak << " d " << d << " b " << b << " target " << target << endl;
      LOG << d1 << endl << d2 << endl;
      return 1;
    }
    LOG << "PASSED" << endl;
    return 0;
  }
  l tcc;
  cin >> tcc;
  F(tc, 1, tcc + 1) {
    LOG << tc << endl;
    l hd, ad, hk, ak, b, d; cin >> hd >> ad >> hk >> ak >> b >> d;
    l s = solve(hd, ad, hk, ak, b, d, hd, 0);
    cout << "Case #" << tc << ": ";
    if (s == INF) {
      cout << "IMPOSSIBLE";
    } else {
      cout << s;
    }
    cout << lf;
  }
}
