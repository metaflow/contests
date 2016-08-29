#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 201;
unordered_map<string, int> names;
int M[MAX][MAX + 1];
pair<int, bool> DP[MAX][2];

int index_of_name(string s) {
  if (names.count(s) == 0) {
    int v = names.size();
    names[s] = v;
  }
  return names[s];
}

void add(string a, string b) {
  int i = index_of_name(a);
  int j = index_of_name(b);
  M[j][0]++;
  M[j][M[j][0]] = i;
}

pair<int, bool> dp(int root, int take) {
  auto &r = DP[root][take];
  if (r.first == -1) {
    r.first = 0;
    r.second = true;
    if (take == 1) {
      r.first++;
      for (int i = 1; i <= M[root][0]; i++) {
        auto a = dp(M[root][i], 0);
        r.first += a.first;
        r.second = r.second && a.second;
      }
    } else {
      for (int i = 1; i <= M[root][0]; i++) {
        auto a = dp(M[root][i], 0);
        auto b = dp(M[root][i], 1);
        if (a.first == b.first) r.second = false;
        if (b.first > a.first) swap(a, b);
        r.first += a.first;
        r.second = r.second && a.second;
      }
    }
  }
  return r;
}

int main() {
  int n;
  while (cin >> n, n) {
    names.clear();
    fill(&M[0][0], &M[MAX][0], 0);
    int root = index_of_name("");
    string employee, boss;
    cin >> employee;
    add(employee, "");
    for (int i = 1; i < n; i++) {
      cin >> employee >> boss;
      add(employee, boss);
    }
    fill(&DP[0][0], &DP[MAX][0], make_pair(-1, false));
    auto answer = dp(root, 0);
    printf("%d %s\n", answer.first, answer.second ? "Yes" : "No");
  }
}
