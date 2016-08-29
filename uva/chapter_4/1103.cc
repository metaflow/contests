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
using ii = pair<int, int>;
const int MAX = 202;
const int MAX_AREAS = MAX * MAX;

int image[MAX][MAX];
int w, h;
bool touches[MAX_AREAS];
int areas[MAX_AREAS];

char names[] = {'W', 'A', 'K', 'J', 'S', 'D'};
int get_hex(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    return 10 + c - 'a';
}

void fill(int x, int y, int v) {
    fill_n(touches, MAX_AREAS, false);
    int c = image[x][y];
    stack<ii> s;
    s.push(make_pair(x, y));
    while (!s.empty()) {
        ii p = s.top();
        int a = p.first;
        int b = p.second;
        s.pop();
        if (a < 0 || b < 0 || a >= h || b >= w) continue;
        int &m = image[a][b];
        if (m >= 0) touches[m] = true;
        if (m == c) {
            m = v;
            s.push(make_pair(a - 1, b));
            s.push(make_pair(a + 1, b));
            s.push(make_pair(a, b - 1));
            s.push(make_pair(a, b + 1));
        }
    }
}

int main() {
    int tc = 0;
    while (cin >> h >> w, h) {
        ++tc;
        string s;
        fill(&image[0][0], &image[MAX][0], 0);
        fill_n(areas, MAX_AREAS, 0);
        for (int i = 0; i < h; ++i) {
            cin >> s;
            for  (int j = 0; j < w; ++j) {
                int v = get_hex(s[j]);
                for (int k = 0; k < 4; ++k) {
                    if ((v << k) & 0b1000) {
                        image[i + 1][j*4 + k + 1] = -1;
                    }
                }
            }
        }
        // explicit empty border around image
        w = 4 * w + 2;
        h += 2;
        int counter = 1;

        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (image[i][j] != -1) continue;
                fill(i, j, counter);
                counter++;
            }
        }

        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (image[i][j] != 0) continue;
                fill(i, j, -1);
                for (int i = 1; i < counter; ++i) {
                    if (touches[i]) areas[i]++;
                }
            }
        }
        string answer;
        for (int i = 1; i < counter; ++i) {
            answer += names[areas[i] - 1];
        }
        sort(answer.begin(), answer.end());
        printf("Case %d: %s\n", tc, answer.c_str());
    }
}
