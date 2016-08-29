#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;

int main() {
    int m;
    while (scanf("%d\n", &m) == 1) {
        vector<pair<int, int> > o, t;
        for (int i = 0; i < m; i++) {
            string s;
            getline(cin, s);
            for (int j = 0; j < m; j++) {
                switch (s[j]) {
                    case '1': o.push_back(make_pair(i, j)); break;
                    case '3': t.push_back(make_pair(i, j)); break;
                }
            }
        }
        int r = 0;
        for (auto a : o) {
            int s = 2 * m;
            for (auto b : t) {
                s = min(s, abs(b.first - a.first) + abs(b.second - a.second));
            }
            r = max(r, s);
        }
        printf("%d\n", r);
    }
    return 0;
}
