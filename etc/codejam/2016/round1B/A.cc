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

vvl masks(10);
const l MAX = 30;

bool solve(vl& chars, vl& solution, int number) {
  if (number == 10) {
    for (auto c : chars) if (c) return false;
    return true;
  }
  l min_count = INF;
  for (l i = 0; i < MAX; i++) {
    if (masks[number][i]) min_count = min(min_count, chars[i] / masks[number][i]);
  }
  // cerr << number << " min " << min_count << endl;
  for (l i = min_count; i >= 0; i--) {
    for (l j = 0; j < MAX; j++) {
      chars[j] -= i * masks[number][j];
    }
    solution[number] = i;
    if (solve(chars, solution, number+1)) return true;
    for (l j = 0; j < MAX; j++) {
      chars[j] += i * masks[number][j];
    }
  }
  return false;
}

vl get_mask(string s) {
  vl result(30);
  for (auto c : s) result[c - 'A']++;
  return result;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc;
  cin >> tcc;
  masks[0] = get_mask("ZERO");
  masks[1] = get_mask("ONE");
  masks[2] = get_mask("TWO");
  masks[3] = get_mask("THREE");
  masks[4] = get_mask("FOUR");
  masks[5] = get_mask("FIVE");
  masks[6] = get_mask("SIX");
  masks[7] = get_mask("SEVEN");
  masks[8] = get_mask("EIGHT");
  masks[9] = get_mask("NINE");
  for (l tc = 0; tc < tcc; tc++) {
    cerr << "." << endl;
    cout << "Case #" << (tc + 1) << ": ";
    string s;
    cin >> s;
    vl C = get_mask(s);
    vl solution(10);
    solve(C, solution, 0);
    for (l i = 0; i < 10; i++) {
      for (l j = 0; j < solution[i]; j++) cout << i;
    }
    cout << endl;
  }
}
