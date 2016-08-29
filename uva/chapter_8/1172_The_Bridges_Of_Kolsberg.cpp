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

const int MAX = 1000;

int main() {
  int tcc = 10;
  printf("%d\n", tcc);
  for (int tc = 0; tc < tcc; tc++) {
    int n = random_in_range(1, MAX);
    vector<string> types;
    for (int i = 0; i < n; i++) types.emplace_back(random_string(10));
    n = random_in_range(0, MAX);
    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
      printf("%s %s %d\n",
        random_string(10).c_str(),
        types[random_in_range(0, types.size() - 1)].c_str(),
        random_in_range(0, 1000000));
    }
    n = random_in_range(0, MAX);
    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
      printf("%s %s %d\n",
        random_string(10).c_str(),
        types[random_in_range(0, types.size() - 1)].c_str(),
        random_in_range(0, 1000000));
    }
  }
}
