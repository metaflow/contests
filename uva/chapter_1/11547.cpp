#include <cstdlib>
#include <stdio.h>

using namespace std;

int main() {
    int test_cases;
    scanf("%d", &test_cases);
    while (test_cases--) {
        int n;
        scanf("%d", &n);
        n = (n * 63 + 7492) * 5 - 498;
        n = (n % 100) / 10;
        printf("%d\n", abs(n));
    }
    return 0;
}
