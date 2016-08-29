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

const int MAX_SIZE = 100; // according to problem up to 1000000
const int MAX_WALLS = 100; // up to 1000

int main() {
  int tcc = 10;
  bool field[MAX_SIZE][MAX_SIZE];
  for (int tc = 0; tc < tcc; tc++) {
    fill(&field[0][0], &field[MAX_SIZE][0], false);
    int n = random_in_range(1, MAX_SIZE);
    int m = random_in_range(1, MAX_SIZE);
    int w = random_in_range(0, MAX_WALLS);
    for (int ii = 0; ii < w; ii++) {
      int x1 = random_in_range(0, n - 1);
      int x2 = random_in_range(0, n - 1);
      if (x1 > x2) swap(x1, x2);
      int y = random_in_range(0, m - 1);
      for (int xx = x1; xx <= x2; xx++) field[xx][y] = true;
    }
    vector<tuple<int, int, int>> walls; // x1, x2, y
    for (int yy = 0; yy < m; yy++) {
      int x = 0;
      while (x < n) {
        if (!field[x][yy]) { x++; continue; }
        int x1 = x;
        while (x + 1 < n && field[x + 1][yy]) x++;
        walls.emplace_back(x1, x, yy);
        x++;
      }
    }
    // TODO actually we end up with less then w walls
    // and walls never stick to each other horisontally
    printf("%d %d %lu\n", m, n, walls.size());
    for (auto ww : walls) {
      printf("%d %d %d %d\n", get<0>(ww), get<2>(ww), get<1>(ww), get<2>(ww));
    }
    // printf("\n"); // wrong format but for readability
  }
  printf("0 0 0 0\n");
}
