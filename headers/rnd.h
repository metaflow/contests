#ifndef _RND_H
#define _RND_H
#include <bits/stdc++.h>

using namespace std;
class Random {
public:
  default_random_engine source;
  Random() {
    source.seed(chrono::system_clock::now().time_since_epoch().count());
  }
  // [a, b)
  long long next(long long a, long long b) {
    return uniform_int_distribution<long long>(a, b - 1)(source);
  }

  double next_double() {
    return uniform_real_distribution<double>(0, 1)(source);
  }

  bool next_bool() {
    return next(0, 2) == 1;
  }

  string next_string(int length) {
    string s = "";
    string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < length; i++) {
      s += an[next(0, an.size())];
    }
    return s;
  }

  string next_string(int length, string an) {
    string s = "";
    for (int i = 0; i < length; i++) {
      s += an[next(0, an.size())];
    }
    return s;
  }


  // return (size - 1) edges connecting nodes [0, n)
  vector<pair<int, int>> tree(int size) {
    vector<int> v(size);
    iota(v.begin(), v.end(), 0);
    shuffle(v.begin(), v.end(), source);
    vector<int> to(size);
    vector<pair<int, int>> edges;
    for (int i = 1; i < size; i++) edges.emplace_back(v[i], v[next(0, i)]);
    return edges;
  }
};
Random rnd;

#endif // _RND_H
