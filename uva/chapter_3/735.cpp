#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main () {
    int x;
    vector<int> s {0, 50};
    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= 3; j++) {
            int t = i * j;
            auto it = lower_bound(s.begin(), s.end(), t);
            if (it == s.end() || t != *it) {
                s.insert(it, t);
            }
        }
    }
    int size = s.size();
    vector<int> targets;
    vector<bool> present(200, false);
    while (scanf("%d", &x), x > 0) {
        targets.push_back(x);
        present[x] = true;
    }
    vector<int> c(targets.size(), 0);
    vector<int> p(targets.size(), 0);
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            for (int k = j; k < size; k++) {
                int t = s[i] + s[j] + s[k];
                if (!present[t]) continue;
                int permutations = 6;
                if (i == j && j == k) {
                    permutations = 1;
                } else if  (i == j || j == k) {
                    permutations = 3;
                }
                for (int m = 0; m < targets.size(); m++) {
                    if (targets[m] != t) continue;
                    c[m]++;
                    p[m] += permutations;
                }
            }
        }
    }
    for (int m = 0; m < targets.size(); m++) {
        if (c[m] == 0) {
            printf("THE SCORE OF %d CANNOT BE MADE WITH THREE DARTS.\n", targets[m]);
        } else {
            printf("NUMBER OF COMBINATIONS THAT SCORES %d IS %d.\n", targets[m], c[m]);
            printf("NUMBER OF PERMUTATIONS THAT SCORES %d IS %d.\n", targets[m], p[m]);
        }
        printf("**********************************************************************\n");
    }
    printf("END OF OUTPUT\n");
    return 0;
}
