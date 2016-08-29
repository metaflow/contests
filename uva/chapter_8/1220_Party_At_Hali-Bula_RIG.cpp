#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

default_random_engine source(random_device{}());

int random_in_range(int a, int b) {
  return uniform_int_distribution<>(a, b)(source);
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
  int tcc = 10;
  for (int tc = 0; tc < tcc; tc++) {
    int n = random_in_range(1, 200);
    cout << n << endl;
    vector<string> names;
    vector<pair<string, string>> pairs;
    names.emplace_back(random_string(random_in_range(4, 100)));
    cout << names.back() << endl;
    for (int i = 1; i < n; i++) {
      string boss = names[random_in_range(0, names.size() - 1)];
      string employee = random_string(random_in_range(4, 100));
      pairs.emplace_back(employee, boss);
    }
    // problem does not imply that boss appeared already when we see employee
    for (size_t i = 0; i < pairs.size(); i++) {
      swap(pairs[i], pairs[random_in_range(i, pairs.size() - 1)]);
    }
    for (auto p : pairs) cout << p.first << " " << p.second << endl;
  }
  cout << 0 << endl;
}
