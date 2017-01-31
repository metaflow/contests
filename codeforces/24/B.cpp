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

const l scores[] = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};
const l MAX_PLACES = 50;
struct player {
  l score = 0;
  l places[MAX_PLACES] = {0};
  string name;
};
l get_index(unordered_map<string,l>& name_index, vector<player>& players, const string name) {
  if (name_index.count(name) == 0) {
    name_index[name] = players.size();
    player p;
    p.name = name;
    players.emplace_back(p);
  }
  return name_index[name];
}
int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    unordered_map<string,l> name_index;
    vector<player> players;
    for (l race = 0; race < n; race++) {
      l m; cin >> m;
      for (l i = 0; i < m; i++) {
        string s; cin >> s;
        l p = get_index(name_index, players, s);
        if (i < 10) players[p].score += scores[i];
        players[p].places[i]++;
      }
    }
    auto by_place = [](const player& a, const player& b) {
      for (l i = 0; i < MAX_PLACES; i++)
        if (a.places[i] != b.places[i]) return a.places[i] < b.places[i];
      return true;
    };
    sort(players.begin(), players.end(), [&](const player& a, const player& b) {
        if (a.score != b.score) return a.score < b.score;
        return by_place(a, b);
      });
    cout << players.back().name << '\n';
    sort(players.begin(), players.end(), [&](const player& a, const player&b) {
        if (a.places[0] != b.places[0]) return a.places[0] < b.places[0];
        if (a.score != b.score) return a.score < b.score;
        return by_place(a, b);
      });
    cout << players.back().name << '\n';
  }
}
