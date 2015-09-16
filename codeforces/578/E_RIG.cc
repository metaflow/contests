#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

default_random_engine source(random_device{}());

l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b)(source);
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
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc = 100;
  for (l i = 0; i < tcc; i++) {
    l L = random_in_range(1, 4);
    l R = L + random_in_range(-1, 1);
    string s;
    for (l i = 0; i < L; i++) s += "L";
    for (l i = 0; i < R; i++) s += "R";
    for (l i = 0; i < s.size(); i++) swap(s[i], s[random_in_range(i, s.size() - 1)]);
    cout << s << endl;
  }
}
