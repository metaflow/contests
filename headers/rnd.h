#ifndef _RND_H
#define _RND_H
#include <random>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <algorithm>

class Random {
public:
  std::default_random_engine source;
  Random() {
    source.seed(std::chrono::system_clock::now().time_since_epoch().count());
  }
  // [a, b)
  long long next(long long a, long long b) {
    return std::uniform_int_distribution<long long>(a, b - 1)(source);
  }

  double next_double() {
    return std::uniform_real_distribution<double>(0, 1)(source);
  }

  bool next_bool() {
    return next(0, 2) == 1;
  }

  std::string next_string(int length) {
    return next_string(
      length,
      "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
  }

  std::string next_string(int length, std::string an) {
    std::string s = "";
    for (int i = 0; i < length; i++) {
      s += an[next(0, an.size())];
    }
    return s;
  }


  // return (size - 1) edges connecting nodes [0, n)
  std::vector<std::pair<int, int>> tree(int size) {
    std::vector<int> v(size);
    iota(v.begin(), v.end(), 0);
    shuffle(v.begin(), v.end(), source);
    std::vector<int> to(size);
    std::vector<std::pair<int, int>> edges;
    for (int i = 1; i < size; i++) edges.emplace_back(v[i], v[next(0, i)]);
    return edges;
  }
};
Random rnd;

#endif // _RND_H
