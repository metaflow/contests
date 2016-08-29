#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    int f;
    while (scanf("%d", &f), f != 0) {
        int r;
        scanf("%d", &r);
        vector<int> front, rear;
        while (f--) {
            int a;
            scanf("%d", &a);
            front.push_back(a);
        }
        while (r--) {
            int a;
            scanf("%d", &a);
            rear.push_back(a);
        }
        vector<double> ratios;
        for (auto a : front) {
            for (auto b : rear) {
                ratios.push_back((1.0d * b) / a);
            }
        }
        sort(ratios.begin(), ratios.end());
        double best = 0.0d;
        for (auto it = ratios.begin(); it + 1 != ratios.end(); it++) {
            best = max(best, *(it + 1) / *it);
        }
        printf("%.2f\n", best);
    }
    return 0;
}
