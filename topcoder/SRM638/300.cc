#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using iii = tuple<int, int, int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 10;
class ShadowSculpture {
  bool v[MAX][MAX][MAX];
  int dx[6] = {1, 0, 0, -1, 0, 0};
  int dy[6] = {0, 1, 0, 0, -1, 0};
  int dz[6] = {0, 0, 1, 0, 0, -1};
public:
  string possible(vector <string> XY, vector <string> YZ, vector <string> ZX) {
    int n = XY.size();
    fill(&v[0][0][0], &v[MAX][0][0], true);
    for (int x = 0; x < n; x++) {
      for (int y = 0; y < n; y++) {
        if (XY[x][y] == 'N') {
          for (int z = 0; z < n; z++) v[x][y][z] = false;
        }
      }
    }
    for (int y = 0; y < n; y++) {
      for (int z = 0; z < n; z++) {
        if (YZ[y][z] == 'N') {
          for (int x = 0; x < n; x++) v[x][y][z] = false;
        }
      }
    }
    for (int z = 0; z < n; z++) {
      for (int x = 0; x < n; x++) {
        if (ZX[z][x] == 'N') {
          for (int y = 0; y < n; y++) v[x][y][z] = false;
        }
      }
    }

    int components = 0;
    for (int x = 0; x < n; x++) {
      for (int y = 0; y < n; y++) {
        for (int z = 0; z < n; z++) {
          if (!v[x][y][z]) continue;
          queue<iii> q;
          components++;
          q.emplace(x, y, z); v[x][y][z] = false;
          while (!q.empty()) {
            auto d = q.front(); q.pop();
            for (int i = 0; i < 6; i++) {
              int x_ = get<0>(d) + dx[i];
              int y_ = get<1>(d) + dy[i];
              int z_ = get<2>(d) + dz[i];
              if (x_ < 0 || x_ >= n ||
                  y_ < 0 || y_ >= n ||
                  z_ < 0 || z_ >= n) continue;
              if (!v[x_][y_][z_]) continue;
              v[x_][y_][z_] = false;
              q.emplace(x_, y_, z_);
            }
          }
        }
      }
    }

    return (components < 2 ? "Possible" : "Impossible");
  }
};

int main() {
  ShadowSculpture ss;
  cout << ss.possible({"YN","NN"}, {"YN","NN"}, {"YN","NN"}) << endl;

  {"YN","NY"}
{"YN","NY"}
{"YN","NY"}
Returns: "Impossible"
Here it is impossible to make a valid sculpture. Note that you can make all three projections look right by using exactly two cubes: (0,0,0) and (1,1,1). However, this sculpture is not 6-connected.
2)

    
{"YYY","YNY","YYY"}
{"YYY","YNY","YYY"}
{"YYY","YNY","YYY"}
Returns: "Possible"

3)

    
{"YYY","YNY","YYY"}
{"NYY","YNY","YYY"}
{"YYY","YNY","YYN"}
Returns: "Impossible"

4)

    
{"N"}
{"N"}
{"N"}
Returns: "Possible"
A sculpture that consists of no cubes is connected.
This problem statement is the exclusive and proprietary property of TopCoder, Inc. Any unauthorized use or reproduction of this information without the prior written consent of TopCoder, Inc. is strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved.
{"YYY","YNY","YYY"}
{"YYY","YNY","YYY"}
{"YYY","YNY","YYY"}
Returns: "Possible"

3)

    
{"YYY","YNY","YYY"}
{"NYY","YNY","YYY"}
{"YYY","YNY","YYN"}
Returns: "Impossible"

4)

    
{"N"}
{"N"}
{"N"}
Returns: "Possible"
}
