#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    while (n--) {
        int a, b, c;
        cin >> a >> b >> c;
        [&]() {
            for (int x = -100; x < 21; x++) if (x * x < c) {
                for (int y = x+1; y < 101; y++) if (x * x + y * y < c) {
                    for (int z = y+1; z < 101; z++) {
                        if (x + y + z == a
                            && x * y * z == b
                            && x * x + y * y + z * z == c) {
                            printf("%d %d %d\n", x, y, z);
                            return;
                        }
                    }
                }
            }
            printf("No solution.\n");
        }();
    }
    return 0;
}
