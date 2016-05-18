#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>; using vvvl = vector<vvl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

l gJ, gP, gS, gK;
vvvl best;
l best_days;

void backtrack(l j, l p, l s, vvvl& used, vvl& jp, vvl& js, vvl& ps, l days) {
  if (s == gS) { p++; s = 0; }
  if (p == gP) { j++; p = 0; }
  if (j == gJ) {
    if (days <= best_days) return;
    best_days = days;
    best = used;
    return;
  }
  if ((jp[j][p] < gK) && (js[j][s] < gK) && (ps[p][s] < gK)) {
    used[j][p][s] = 1;
    jp[j][p]++;
    js[j][s]++;
    ps[p][s]++;
    backtrack(j, p, s + 1, used, jp, js, ps, days + 1);
    used[j][p][s] = 0;
    jp[j][p]--;
    js[j][s]--;
    ps[p][s]--;
  }
  backtrack(j, p, s + 1, used, jp, js, ps, days);
}

vector<tuple<l,l,l>> solve_brute(l J, l P, l S, l K) {
  best_days = 0;
  gJ = J; gP = P; gS = S; gK = K;
  vvvl m(J, vvl(P, vl(S, 0)));
  vvl jp(J, vl(P));
  vvl js(J, vl(S));
  vvl ps(P, vl(S));
  backtrack(0, 0, 0, m, jp, js, ps, 0);
  vector<tuple<l,l,l>> solution;
  for (l j = 0; j < J; j++)
  for (l p = 0; p < P; p++)
  for (l s = 0; s < S; s++) {
    if (best[j][p][s]) {
      solution.emplace_back(j + 1, p + 1, s + 1);
    }
  }
  return solution;
}

vector<tuple<l,l,l>> solve(l J, l P, l S, l K) {
  vector<tuple<l,l,l>> solution;
  for (l j = 0; j < J; j++)
  for (l p = 0; p < P; p++)
  for (l s = 0; s < S; s++)
  if ((j + p + s) % S < K) {
    solution.emplace_back(j + 1, p + 1, s + 1);
  }
  return solution;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);/*
  for (l J = 1; J <= 3; J++)
  for (l P = J; P <= 3; P++)
  for (l S = P; S <= 3; S++)
  for (l K = 1; K <= S + 1; K++) {
    auto a = solve_brute(J, P, S, K);
    auto b = solve(J, P, S, K);
    cout << J << " " << P << " " << S << " " << K << endl;
    if (a.size() != b.size()) {
      cout << a.size() << " != " << b.size() << endl;
      return 0;
    }
  }
  cout << "OK" << endl;
  return 0;*/
  l tcc; cin >> tcc;
  for (l tc = 1; tc <= tcc; tc++) {
    l J, P, S, K;
    cin >> J >> P >> S >> K;
    cout << "Case #" << tc << ": " << (J * P * min(S, K)) << endl;
      for (l j = 0; j < J; j++)
      for (l p = 0; p < P; p++)
      for (l s = 0; s < S; s++)
      if ((j + p + s) % S < K) {
        cout << (j + 1) << " " << (p + 1) << " " << (s + 1) << endl;
      }
  }
}
