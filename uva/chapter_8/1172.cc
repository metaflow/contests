#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 1000;

unordered_map<string, int> types;
// vector<ii> n_bank, s_bank; // pair<type, value>
int n_bank_value[MAX], n_bank_type[MAX], s_bank_value[MAX], s_bank_type[MAX];

int s_bank_max[2 * MAX];
ii memo[MAX][MAX];
bool visited[MAX][MAX];

// best <value, number of bridges>
ii dp(int l, int r) {
  if (l < 0 || r < 0) return make_pair(0, 0);
  if (!visited[l][r]) {
    visited[l][r] = true;
    auto &t = memo[l][r];
    // don't take
    t = dp(l - 1, r);
    // or take
    int top = s_bank_max[n_bank_type[l]];
    if (top > -1) {
      int m = -1;
      top += n_bank_value[l];
      for (int i = r; i >= 0; i--) {
        if (n_bank_type[l] != s_bank_type[i]) continue;
        if (s_bank_value[i] <= m) continue;
        m = s_bank_value[i];
        auto v = dp(l - 1, i - 1);
        if (v.first + top < t.first) break;
        v.first += n_bank_value[l] + s_bank_value[i];
        v.second++;
        if (t.first < v.first ||
           (t.first == v.first && t.second > v.second)) t = v;
      }
    }

  }
  return memo[l][r];
}
/*
void read_city(vector<ii>& bank) {
  string name, type; int value;
  cin >> name >> type >> value;
  if (types.count(type) == 0) {
    int v = types.size();
    types[type] = v;
  }
  bank.emplace_back(types[type], value);
}
*/
int get_type(string s) {
  if (types.count(s) == 0) {
    int v = types.size();
    types[s] = v;
  }
  return types[s];
}

int main() {
  ios_base::sync_with_stdio(false);
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    types.clear();
    fill(&visited[0][0], &visited[MAX][0], false);
    fill_n(s_bank_max, 2 * MAX, -1);

    int l_count, r_count;
    cin >> l_count;
    string name, type; int value;
    for (int i = 0; i < l_count; i++) {
      cin >> name >> type >> value;
      n_bank_type[i] = get_type(type);
      n_bank_value[i] = value;
    }
    cin >> r_count;
    for (int i = 0; i < r_count; i++) {
      cin >> name >> type >> value;
      int t = get_type(type);
      s_bank_type[i] = t;
      s_bank_value[i] = value;
      s_bank_max[t] = max(s_bank_max[t], value);
    }
    auto best = dp(l_count - 1, r_count - 1);
    cout << best.first << " " << best.second << endl;
  }
}
