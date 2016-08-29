#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int main() {
    int n, m, s;
    while (cin >> n >> m >> s, n) {
        vector<string> field(n);
        int x, y ,d;
        int count = 0;
        for (int i = 0; i < n; ++i) {
            cin >> field[i];
            for (int j = 0; j < m; ++j) {
                if (field[i][j] >= 'L' && field[i][j] <= 'S') {
                    x = i;
                    y = j;
                    switch (field[i][j]) {
                        case 'N': d = 0; break;
                        case 'S': d = 2; break;
                        case 'L': d = 1; break;
                        case 'O': d = 3; break;
                    }
                }
            }
        }
        string command;
        cin >> command;
        for (int i = 0; i < s; ++i) {
            switch (command[i]) {
                case 'D': d = (d + 1) % 4; break;
                case 'E': d = (d - 1 + 4) % 4; break;
                case 'F':
                    int _x = x + dx[d];
                    int _y = y + dy[d];
                    if (_x < 0 || _x >= n) continue;
                    if (_y < 0 || _y >= m) continue;
                    if (field[_x][_y] == '#') continue;
                    x = _x;
                    y = _y;
                    if (field[x][y] == '*') {
                        field[x][y] = '.';
                        count++;
                    }
            }
        }
        printf("%d\n", count);
    }
}

