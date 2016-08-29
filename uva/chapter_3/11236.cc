#include <iostream>

using namespace std;

using ull = unsigned long long;

int main() {
    for (int i = 1; i < 2000; i++) {
        for (int j = i; j < 2000 - i; j++) {
            for (int k = j; k < 2000 - i - j; k++) {
                ull b = i * j * k;
                b -= 1000000;
                ull a = (i + j + k) * 1000000;
                if (b <= 0 || a % b != 0 || a < b) continue;
                int x = a / b;
                if (x < k) break;
                if (i + j + k + x > 2000) continue;
                printf("%.2f %.2f %.2f %.2f\n", i * 1.0 / 100, j * 1.0 / 100, k * 1.0 / 100, x * 1.0 / 100);
            }
        }
    }
}
