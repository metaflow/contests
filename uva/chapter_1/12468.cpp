#include <algorithm>
#include <stdio.h>

using namespace std;

int main() {
    int a, b;
    while (scanf("%d%d", &a, &b), a != -1) {
        printf("%d\n", min((a - b + 100) % 100, (b - a + 100) % 100));
    }
    return 0;
}
